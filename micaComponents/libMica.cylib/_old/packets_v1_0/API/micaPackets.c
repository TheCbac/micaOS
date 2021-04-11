/***************************************************************************//**
* \file micaPackets.c
* \version 1.0.0
*
* \brief
* Source files for parsing MICA Packets
* \authors Craig Cheney
* \date 2017.11.02 CC - Document Created
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
#include "`$INSTANCE_NAME`_micaPackets.h"
#include "`$INSTANCE_NAME`_micaConstants.h"
//#include "micaLeds.h"
//#include "micaUtility.h"
//#include "micaBle.h"
/* Store the state variable */
volatile MICA_PACKET_STATE_T packetBufferState = STATE_WAIT_FOR_START;
volatile uint16_t bufferCount = ZERO;
volatile uint16_t payloadLen = ZERO;
///* Pointer to the transport layer function */
//void (*transportFunction)(uint32 ch) = NULL;

/*******************************************************************************
* Function Name: mica_setPacketTransport()
****************************************************************************//**
* \brief
*  Sets the transport function to be used when sending response packets
*
* \param func
* Pointer to the function to call when sending data 
*
*
* \return
*  None
*
*******************************************************************************/
void mica_setPacketTransport(void (* func)(uint32 ch)){
    transportFunction = func;
}

/*******************************************************************************
* Function Name: mica_processPacketByte()
****************************************************************************//**
* \brief
*  Stores a byte of data received in a buffer to be processed once the packet
*  is complete 
*
* \param dataByte
* The data byte to be processed 
*
* \param packetBuffer
* The data array to store the buffer in. Must be of at least size MICA_PACKET_LEN_MAX_PACKET 
*
* \return
*  A boolean indicating if the packet is complete
*
*******************************************************************************/
bool mica_processPacketByte(uint8_t dataByte, uint8_t* packetBuffer) {
    /* Return Value */
    bool packetComplete = false; 
    /* Act according to the state of the packet buffer */
    switch (packetBufferState) {
        /* Waiting for start, ensure that the data byte is valid */
        case STATE_WAIT_FOR_START: {
            /* Ensure start byte is valid */
            if (dataByte == MICA_PACKET_SYM_START) {
                /* Reset the count */
                bufferCount = ZERO;
                /* Store the byte */
                packetBuffer[bufferCount++] = dataByte;
                /* Advance to the next state */
                packetBufferState = STATE_RECEIVE_HEADER;
            }
            break;
        }
        /* Waiting for the header */
        case STATE_RECEIVE_HEADER: {
            /* Store the data */
            packetBuffer[bufferCount++] = dataByte;
            /* Check to see if more data is required */
            if (bufferCount == MICA_PACKET_LEN_HEADER) {
                /* Get the payload length */
                payloadLen = (packetBuffer[MICA_PACKET_INDEX_LEN_MSB] << BITS_ONE_BYTE) | packetBuffer[MICA_PACKET_INDEX_LEN_LSB];
                /* Ensure payload len is valid */
                if (payloadLen > MICA_PACKET_LEN_MAX_PAYLOAD) {
                    /* Error - Move back to start state */
                    packetBufferState = STATE_WAIT_FOR_START;
                } else if (payloadLen == ZERO) {
                    /* Skip payload collection */
                    packetBufferState = STATE_RECEIVE_FOOTER;
                } else {
                    /* Advance to the next state */
                    packetBufferState = STATE_RECEIVE_PAYLOAD;
                }
            }
            break;
        }
        /* Receiving Payload info */
        case STATE_RECEIVE_PAYLOAD: {
            /* Store the data  */
            packetBuffer[bufferCount++] = dataByte;
            /* See if all data has been captured */
            if (bufferCount == (MICA_PACKET_LEN_HEADER +  payloadLen)){
                packetBufferState = STATE_RECEIVE_FOOTER;   
            }
            break;
        }
        /* Wait for the footer */
        case STATE_RECEIVE_FOOTER: {
            /* Store the data */
            packetBuffer[bufferCount++] = dataByte;
            /*If all data has been captured */
            if (bufferCount == (MICA_PACKET_LEN_HEADER + payloadLen + MICA_PACKET_LEN_FOOTER)) {
                /*  Ensure stop symbol is valid */
                if (dataByte == MICA_PACKET_SYM_END) {
                    /* Packet is complete */   
                    packetComplete = true;
                }
                /* Advance to original state */
                packetBufferState = STATE_WAIT_FOR_START;
            }
            break;
        }
    }
    /* Return the packet state */
    return packetComplete;
}


/*******************************************************************************
* Function Name: mica_parsePacket()
****************************************************************************//**
* \brief
*  Parses a data packet from the received data.
*
* \param dataBuffer
* Pointer to the received data
*
* \param packet
* Pointer to a packet structure to place the infomation in
*
* \return
* The error code of the result packet parsing
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   PACKET_SUCCESS                          | The packet was successfully parsed.
*   PACKET_ERR_FORMAT                       | The packet was in the incorrect format.
*   PACKET_ERR_MODULE                       | An unknown module was requested.
*   PACKET_ERR_LENGTH                       | The packet payload length was outside the allowed value.
*   PACKET_ERR_CHECKSUM                     | The calculated checksum did not match the reported checksum.
*******************************************************************************/
MICA_PACKET_ERROR_T mica_parsePacket(uint8_t* dataBuffer, MICA_PACKET_T* packet) {
    /* Ensure start of packet symbol */
    if (dataBuffer[MICA_PACKET_INDEX_START] != MICA_PACKET_LEN_SYM_START) {
        return PACKET_ERR_FORMAT;
    }
    /* Get the Module */
    packet->moduleId = dataBuffer[MICA_PACKET_INDEX_MODULE_ID];
    if (packet->moduleId > MICA_PACKET_ID_MODULE_MAX) {
     return PACKET_ERR_MODULE;
    }
    /* Get the Command - Cannot tell if valid at this point */
    packet->cmd = dataBuffer[MICA_PACKET_INDEX_CMD];
    /* Get the payload length */
    packet->length = (dataBuffer[MICA_PACKET_INDEX_LEN_MSB] << BITS_ONE_BYTE) | dataBuffer[MICA_PACKET_INDEX_LEN_LSB];
    if (packet->length > MICA_PACKET_LEN_MAX_PAYLOAD) {
        return PACKET_ERR_LENGTH;  
    }
    /* Set the payload pointer */
    packet->payload = &dataBuffer[MICA_PACKET_INDEX_PAYLOAD];
    /* Validate checksum */
    uint16_t calculatedChecksum = mica_computeChecksum16(dataBuffer, MICA_PACKET_LEN_HEADER + packet->length);
    uint8_t* packetEndPtr = &dataBuffer[MICA_PACKET_LEN_HEADER + packet->length];
    uint8 checkSumMsb = *packetEndPtr++;
    uint8 checkSumLsb = *packetEndPtr++;
    uint16_t reportedChecksum = (checkSumMsb << BITS_ONE_BYTE) | checkSumLsb;
    if( calculatedChecksum != reportedChecksum) {
        return PACKET_ERR_CHECKSUM;
    }
    /* Check end of packet symbol */
    uint8 endSymbol = *packetEndPtr;
    if (endSymbol != MICA_PACKET_SYM_END) {
        return PACKET_ERR_FORMAT;
    }
    /* Successful packet */
    return PACKET_SUCCESS;
} 
//
///*******************************************************************************
//* Function Name: mica_processCommand()
//****************************************************************************//**
//* \brief
//*  Routes the command to the correct function based on the module ID;
//*
//* \param packet
//* Pointer to the packet to processed
//*
//* \param response
//* Pointer to the response packet to be populated by the command
//*
//*
//* \return
//* The result of the command
//* The possible error codes are:
//*
//*  Errors codes                             | Description
//*   ------------                            | -----------
//*   PACKET_SUCCESS                          | The packet was successfully parsed.
//*******************************************************************************/
//void mica_processCommand(MICA_PACKET_T* packet,  MICA_RESPONSE_T* response) {
//    /* Set the module ID */
//    response->moduleId = packet->moduleId;
//    /* handle the packet according to module */
//    switch(packet->moduleId) {
//        /* Energy Commands */
//        case MICA_PACKET_ID_MODULE_ENERGY:{
//            /* Process the Control Command */
//            break;   
//        }
//        /* Actuation Commands */
//        case MICA_PACKET_ID_MODULE_ACTUATION:{
//            /* Process the Control Command */
//            break;   
//        }
//        /* Power Commands */
//        case MICA_PACKET_ID_MODULE_POWER:{
//            /* Process the Control Command */
//            break;   
//        }
//        /* Sensing Commands */
//        case MICA_PACKET_ID_MODULE_SENSING:{
//            /* Process the Control Command */
//            break;   
//        }
//        /* Communication Commands */
//        case MICA_PACKET_ID_MODULE_COMM:{
//            /* Process the Control Command */
//            mica_processCommCmd(packet, response);
//            break;   
//        }
//        /* Control Commands */
//        case MICA_PACKET_ID_MODULE_CONTROL:{
//            /* Process the Control Command */
//            mica_processControlCmd(packet, response);
//            break;   
//        } 
//        /* Unknown module was addressed */
//        default: {
//            response->status = PACKET_ERR_MODULE;
//        }
//    }
//}
//
///*******************************************************************************
//* Function Name: mica_processCommCmd()
//****************************************************************************//**
//* \brief
//*  Processes a command sent to the communications module
//*
//* \param packet
//* Pointer to the packet to be processed
//*
//* \param response
//* Pointer to the response packet
//*
//* \return
//* The result of the command
//* The possible error codes are:
//*
//*  Errors codes                             | Description
//*   ------------                            | -----------
//*   PACKET_SUCCESS                          | The packet was successfully parsed.
//*******************************************************************************/
//void mica_processCommCmd(MICA_PACKET_T* packet, MICA_RESPONSE_T* response) {
//    /* Default to no data returned */
//    response->length = ZERO;
//    /* handle the command */
//    switch(packet->cmd) {
//        /* Start or stop the scan */
//#if (CYBLE_GAP_ROLE_CENTRAL)
//        case MICA_PACKET_CMD_COMM_SCAN: {
//            /* Check the length */
//            if(packet->length != MICA_PACKET_CMD_COMM_SCAN_LEN) {
//                response->status = PACKET_ERR_LENGTH;
//                return;
//            }
//            /* Start or stop the BLE scan */
//            bool nextScanState = packet->payload[MICA_PACKET_CMD_COMM_SCAN_STATE_INDEX];
//            uint8 curState = CyBle_GetState();
//            /* Only valid state to progress */
//            if((nextScanState && curState == CYBLE_STATE_DISCONNECTED) || (!nextScanState && curState == CYBLE_STATE_SCANNING)) {
//                /* Start the scan */
//                micaBle_startStopScan(nextScanState);
//                /* Indicate sucess */
//                response->status = PACKET_SUCCESS;
//            } else {
//                /* Invalid state */   
//                response->status = PACKET_ERR_STATE;
//            }
//
//            break;
//        }
//        /* Connect to a device */
//        case MICA_PACKET_CMD_COMM_CONN: {
//            /* Check the length */
//            if(packet->length != MICA_PACKET_CMD_COMM_CONN_LEN) {
//                response->status = PACKET_ERR_LENGTH;
//                return;
//            }
//            /* Extract the parameters */
//            uint8 type = packet->payload[MICA_PACKET_CMD_COMM_CONN_TYPE_INDEX];
//            uint8 *addr = &packet->payload[MICA_PACKET_CMD_COMM_CONN_ADDR_INDEX];
//            /* Initiate the connection request */
//            response->status = micaBle_Connect(type, addr);
//            break;
//        }
//        /* Disconnect from a device */
//        case MICA_PACKET_CMD_COMM_DCON: {
//            /* Check the length */
//            if(packet->length != MICA_PACKET_CMD_COMM_CONN_LEN) {
//                response->status = PACKET_ERR_LENGTH;
//                return;
//            }
//            /* Extract the parameters */
//            uint8 type = packet->payload[MICA_PACKET_CMD_COMM_CONN_TYPE_INDEX];
//            uint8 *addr = &packet->payload[MICA_PACKET_CMD_COMM_CONN_ADDR_INDEX];
//            /* Initiate the connection request */
//            response->status = micaBle_Disconnect(type, addr);
//            break;
//        }
//#endif /* (CYBLE_GAP_ROLE_CENTRAL) */
//        /* Unknown command */
//        default: {
//            response->status = PACKET_ERR_CMD;
//            break;
//        }
//    }
//}
//
///*******************************************************************************
//* Function Name: mica_processControlCmd()
//****************************************************************************//**
//* \brief
//*  Processes a command sent to the control module
//*
//* \param packet
//* Pointer to the packet to be processed
//*
//* \param response
//* Pointer to the response packet
//*
//* \return
//* The result of the command
//* The possible error codes are:
//*
//*  Errors codes                             | Description
//*   ------------                            | -----------
//*   PACKET_SUCCESS                          | The packet was successfully parsed.
//*******************************************************************************/
//void mica_processControlCmd(MICA_PACKET_T* packet, MICA_RESPONSE_T* response) {
//    /* Default to no data returned */
//    response->length = ZERO;
//    /* handle the command */
//    switch(packet->cmd) {
//        /* Set the state of the LEDs */
//        case MICA_PACKET_CMD_CTRL_LED: {
//            /* Ensure packet is correct length */
//            if (packet->length != MICA_PACKET_CMD_CTRL_LED_LEN) {
//                response->status = PACKET_ERR_LENGTH;
//                return;
//            }
//            uint8_t i = ZERO;
//            uint8_t* payload = packet->payload;
//            micaLedEnable(payload[i++]);
//            /* Write the leds */
//            uint8_t R = payload[i++];
//            uint8_t G = payload[i++];
//            uint8_t B = payload[i++];
//            micaLedWrite(R, G, B);
//        
//
//            response->status = PACKET_SUCCESS;
//            break;
//        }
//        /* Enter Bootloader mode */
//        case MICA_PACKET_CMD_CTRL_BOOT: {
//            if (packet->length != MICA_PACKET_CMD_CTRL_BOOT_LEN) {
//                response->status = PACKET_ERR_LENGTH;
//                return;
//            }
//            /* SPECIAL CASE - Need to send response before the command is executed */
//            response->status = PACKET_SUCCESS;
//            mica_sendResponsePacket(response);
//            /* Delay to ensure that the Packet was sent */
//            micaUtility_delayMs(MICA_UTILITY_RESET_DELAY);
//            /* Reset the app in bootloader mode - this will never return */
//            micaUtility_enterBootloader(); 
//            break;
//        }
//        /* Reset the device */
//        case MICA_PACKET_CMD_CTRL_RST: {
//            if (packet->length != MICA_PACKET_CMD_CTRL_BOOT_LEN) {
//                response->status = PACKET_ERR_LENGTH;
//                return;
//            }
//            /* SPECIAL CASE - Need to send response before the command is executed */
//            response->status = PACKET_SUCCESS;
//            mica_sendResponsePacket(response);
//            /* Delay to ensure that the Packet was sent */
//            micaUtility_delayMs(MICA_UTILITY_RESET_DELAY);
//            /* Reset the device */
//            micaUtility_resetDevice();
//            break;
//        }
//        /* Unknown command */
//        default: {
//            response->status = PACKET_ERR_CMD;
//            break;
//        }
//    }
//}

/*******************************************************************************
* Function Name: mica_sendResponsePacket()
****************************************************************************//**
* \brief
*  Processes a command sent to the control module
*
* \param response
* Pointer to the response packet to 
*
* \return
* A boolean on whether the command was sent or not
*
*******************************************************************************/
bool mica_sendResponsePacket(MICA_RESPONSE_T* response) {
    bool sent = false;
    /* Send the byte if the transport function is defined */
    if(transportFunction != NULL) {
        uint8_t respPacket[MICA_PACKET_RESP_LEN_MAX_PACKET];
        uint16_t i = ZERO;
        
        /* Header */
        respPacket[i++] = MICA_PACKET_SYM_START;
        respPacket[i++] = response->moduleId;
        respPacket[i++] = response->status;
        respPacket[i++] = (response->length >> BITS_ONE_BYTE) & MASK_BYTE;
        respPacket[i++] = (response->length) & MASK_BYTE;
        /* Payload */
        uint16_t j;
        for(j = ZERO; j < response->length; j++) {
            respPacket[i++] = response->payload[j];
        }
        /* Footer */
        uint16_t checksum = mica_computeChecksum16(respPacket, MICA_PACKET_RESP_LEN_HEADER + response->length);
        respPacket[i++] = (checksum >> BITS_ONE_BYTE) & MASK_BYTE;
        respPacket[i++] = (checksum) & MASK_BYTE;
        respPacket[i++] = MICA_PACKET_SYM_END;
        /* Send out */
        for(i = ZERO; i < (MICA_PACKET_RESP_LEN_OVERHEAD + response->length); i++){
            transportFunction(respPacket[i]);
        }
        sent = true;
    }
    return sent;
}

/*******************************************************************************
* Function Name: mica_computeChecksum16()
****************************************************************************//**
* \brief
*  Calculates the 16 bit, two's complement, checksum from an array of data
*
* \param data
* Array which contains the data
*
* \param length
* The length of the data to interate over
*
* \return
* The value of the checksum in two's complement form
*
*******************************************************************************/
uint16_t mica_computeChecksum16(uint8_t* data, uint16_t length){
    /* Local variables */
    uint8_t idx;
    uint16_t sum = ZERO;
    /* Iterate over the values */
    for( idx = ZERO; idx < length; idx++ ){
        sum += data[idx];
    }
    /* Return the sum in two's complement */
    return (1 + ~sum);
}

/* [] END OF FILE */
