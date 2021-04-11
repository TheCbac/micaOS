/***************************************************************************
*                                       MICA
* File: packets.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.3
* Author: Craig Cheney
*
* Brief:
*   Binary packet specification for MICA
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.04.19 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"
#include "`$uartIncludeFile`.h"
#include <stdlib.h>


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_initialize()
****************************************************************************//**
* \brief
*  Initializes the packet structure to default values
*
* \param buffer
*   Pointer to the packet to be initialized. 
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_initialize(`$INSTANCE_NAME`_BUFFER_FULL_S *packetBuffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /*  Receive Local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* rxBuffer = &(packetBuffer->send.processBuffer);
    `$INSTANCE_NAME`_PACKET_S* rxPacket = &(packetBuffer->send.packet);
    /* Set send process buffer to zero */
    rxBuffer->buffer = NULL;
    rxBuffer->bufferLen = ZERO;
    rxBuffer->timeCount = ZERO;
    rxBuffer->bufferIndex = ZERO;
    /* Set packet values */
    rxPacket->moduleId = ZERO;
    rxPacket->cmd = ZERO;
    rxPacket->payload = NULL;
    rxPacket->payloadLen = ZERO;
    rxPacket->payloadMax = ZERO;
    rxPacket->flags = ZERO;
    rxPacket->error = ZERO;

    /* Reset the state */
    packetBuffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;

    /*  Receive Local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* txBuffer = &(packetBuffer->receive.processBuffer);
    `$INSTANCE_NAME`_PACKET_S* txPacket = &(packetBuffer->receive.packet);
    /* Set receive process buffer to zero */
    txBuffer->buffer = NULL;
    txBuffer->bufferLen = ZERO;
    txBuffer->timeCount = ZERO;
    txBuffer->bufferIndex = ZERO;
    /* Set the packet values */
    txPacket->moduleId = ZERO;
    txPacket->cmd = ZERO;
    txPacket->payload = NULL;
    txPacket->payloadLen = ZERO;
    txPacket->payloadMax = ZERO;
    txPacket->flags = ZERO;
    txPacket->error = ZERO;
    /* Reset the tx state */
    packetBuffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;

    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_generateBuffers()
****************************************************************************//**
* \brief
*  Allocates memory for a new packet buffer
*
* \param buffer
*   Pointer to the packet to be initialized. 
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_generateBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S *packetBuffer, uint16_t bufferSize) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Local References */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* rxBuffer = &(packetBuffer->receive.processBuffer);
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* txBuffer = &(packetBuffer->send.processBuffer);
    uint8_t* rxPayload = packetBuffer->receive.packet.payload;
    
    /* Make sure that buffers have not already been allocated */
    if(rxBuffer->buffer != NULL || txBuffer->buffer != NULL || rxPayload != NULL){
        error |= `$INSTANCE_NAME`_ERR_STATE;
    }

    if(!error) {
        /* Create receive process buffer */
        uint8* processRxBufferAdr = (uint8 *) calloc(ONE, bufferSize);
        if(processRxBufferAdr == NULL){
            error |= `$INSTANCE_NAME`_ERR_MEMORY; 
            /* Do not try to allocate again */
            goto `$INSTANCE_NAME`_clean1;
        }
        packetBuffer->receive.processBuffer.buffer = processRxBufferAdr;
        packetBuffer->receive.processBuffer.bufferLen = bufferSize;

        /* Create Send process buffer */
        uint8* processTxBufferAdr = (uint8 *) calloc(ONE, bufferSize);
        if(processTxBufferAdr == NULL){
            error |= `$INSTANCE_NAME`_ERR_MEMORY; 
            goto `$INSTANCE_NAME`_clean2;
        }
        packetBuffer->send.processBuffer.buffer = processTxBufferAdr;
        packetBuffer->send.processBuffer.bufferLen = bufferSize;
        
        /*  Create the rxPayload */
        uint8* rxPayloadAdr = (uint8 *) calloc(ONE, bufferSize);
        if(rxPayloadAdr == NULL){
            error |= `$INSTANCE_NAME`_ERR_MEMORY; 
            goto `$INSTANCE_NAME`_clean3;
        }
        packetBuffer->receive.packet.payload = rxPayloadAdr;
        packetBuffer->receive.packet.payloadMax = bufferSize;
        
        /* Set initial values to zero */
        packetBuffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
        packetBuffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
        packetBuffer->send.packet.payloadMax = ZERO;

        /* Clean up on error */
        if(error) {  
`$INSTANCE_NAME`_clean3:
            free(rxPayloadAdr);
`$INSTANCE_NAME`_clean2:
            free(processTxBufferAdr);
`$INSTANCE_NAME`_clean1:
            free(processRxBufferAdr);
        }
    }
    /* return error flags */
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_destoryBuffers()
****************************************************************************//**
* \brief
*  Deallocates memory from a packet
*
* \param buffer
*   Pointer to the packet to be initialized. 
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_destoryBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S *buffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Free the Send process buffer is it exists */
    if(buffer->send.processBuffer.buffer != NULL){ 
        free(buffer->send.processBuffer.buffer);   
        buffer->send.processBuffer.buffer = NULL;
        buffer->send.processBuffer.bufferLen = ZERO;
        buffer->send.processBuffer.bufferIndex = ZERO;
        buffer->send.processBuffer.timeCount = ZERO;
    } else {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Free the receive process buffer is it exists */
    if(buffer->receive.processBuffer.buffer != NULL){ 
        free(buffer->receive.processBuffer.buffer);   
        buffer->receive.processBuffer.buffer = NULL;
        buffer->receive.processBuffer.bufferLen = ZERO;
        buffer->receive.processBuffer.bufferIndex = ZERO;
        buffer->receive.processBuffer.timeCount = ZERO;
    } else {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Free the receive payload buffer is it exists */
    if(buffer->receive.packet.payload != NULL) { 
        free(buffer->receive.packet.payload);   
        buffer->receive.packet.payload = NULL;
        buffer->receive.packet.payloadMax = ZERO;
        buffer->receive.packet.payloadLen = ZERO;
    } else {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Return error */
    return error;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_flushRxBuffers()
****************************************************************************//**
* \brief
*  Flush the RX and TX process buffer
*
* \param buffer
*  Pointer to the full buffers
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
void `$INSTANCE_NAME`_flushRxBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer){
    /* Reset RX buffers */
    buffer->receive.processBuffer.bufferIndex = ZERO;
    buffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;   
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_flushTxBuffers()
****************************************************************************//**
* \brief
*  Flush the RX and TX process buffer
*
* \param buffer
*  Pointer to the full buffers
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
void `$INSTANCE_NAME`_flushTxBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer){
     /* Reset TX buffers */
    buffer->send.processBuffer.bufferIndex = ZERO;
    buffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_flushBuffers()
****************************************************************************//**
* \brief
*  Flush the RX and TX process buffer
*
* \param buffer
*  Pointer to the full buffers
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
void `$INSTANCE_NAME`_flushBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer){
    `$INSTANCE_NAME`_flushTxBuffers(buffer);
    `$INSTANCE_NAME`_flushRxBuffers(buffer);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_constructPacket()
****************************************************************************//**
* \brief
*  Pack the data in the TX packet to the TX processBuffer
*
* \param packet
*  Pointer to the packet to pack
*
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_constructPacket(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* txBuffer = &(buffer->send.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_SEND_T* bufferState = &(buffer->send.bufferState);
    `$INSTANCE_NAME`_PACKET_S* packet = &(buffer->send.packet);
    
    /* *** Validate packet *** */
    /* Module ID */
    if(packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
        error |= `$INSTANCE_NAME`_ERR_MODULE;
    }
    /* LEN less than max */
    if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
        error |= `$INSTANCE_NAME`_ERR_LENGTH;
    }
    /* LEN less than process buffer max */
    if ( (packet->payloadLen + `$INSTANCE_NAME`_LEN_OVERHEAD) > txBuffer->bufferLen) {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }
    /* Send buffer must not be busy */
    if(*bufferState != `$INSTANCE_NAME`_BUFFER_SEND_WAIT) {
       error |= `$INSTANCE_NAME`_ERR_STATE;
    }
    /* Assemble the packet if no error */
    if(!error) {
        /* Reset the buffer count */
        txBuffer->bufferIndex = ZERO;
        /* Header */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = `$INSTANCE_NAME`_SYM_START;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = packet->moduleId;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = packet->cmd;
        /* Payload length MSB */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (packet->payloadLen >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
        /* Payload length MSB */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (packet->payloadLen) & MASK_BYTE_ONE;
        /* Payload */
        uint16_t j;
        for(j = ZERO; j < packet->payloadLen; j++) {
            txBuffer->buffer[(txBuffer->bufferIndex)++] = packet->payload[j];
        }
        /* Footer */
        /* Flags Bytes 3-0 */
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (uint8_t) ((packet->flags) >> BITS_THREE_BYTES);
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (uint8_t) ((packet->flags) >> BITS_TWO_BYTES);
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (uint8_t) ((packet->flags) >> BITS_ONE_BYTE);
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (uint8_t)  (packet->flags);
        /* Calculate checksum */
        uint16_t checksum = `$INSTANCE_NAME`_computeChecksum16(txBuffer->buffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen + `$INSTANCE_NAME`_LEN_FLAGS);
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (checksum >> BITS_ONE_BYTE) & MASK_BYTE_ONE;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = (checksum) & MASK_BYTE_ONE;
        txBuffer->buffer[(txBuffer->bufferIndex)++] = `$INSTANCE_NAME`_SYM_END;
        /* Advance to Ready to send */
        *bufferState =  `$INSTANCE_NAME`_BUFFER_SEND_READY;
    }
    /* Return error code */
    return error;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_sendPacket()
****************************************************************************//**
* \brief
*   Constructs and then sends of the data stored in the TX process buffer 
*
* \param packet
*  Pointer to the packet to send of out the rx buffer
*
* \return
* A error code with the result of packing
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_sendPacket(`$INSTANCE_NAME`_BUFFER_FULL_S *buffer){
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Construct the tx packet */
    error |= `$INSTANCE_NAME`_constructPacket(buffer);
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* txBuffer = &(buffer->send.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_SEND_T* bufferState = &(buffer->send.bufferState);
    /* Send buffer must not be busy */
    if(*bufferState != `$INSTANCE_NAME`_BUFFER_SEND_READY) {
       error |= `$INSTANCE_NAME`_ERR_STATE;
    }
    if(!error) {
        /* Write out the function */
        `$txFunction`(txBuffer->buffer, txBuffer->bufferLen );
        /* Move back to the original state */
        *bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
        /* Flush the TX buffer */
        `$INSTANCE_NAME`_flushTxBuffers(buffer);   
    }
    return error;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_processRxByte()
****************************************************************************//**
* \brief
*  Processes the lastest received byt . 
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_processRxByte(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer, uint8_t byte) {
     uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* rxBuffer = &(buffer->receive.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_RECEIVE_T* bufferState = &(buffer->receive.bufferState);
    uint16_t* payloadLen = &(buffer->receive.packet.payloadLen);

    /* Ensure that buffers are valid and there is room */
    if( 
        (rxBuffer->bufferLen == ZERO) ||
        (rxBuffer->buffer == NULL) ||
        (rxBuffer->bufferIndex >= rxBuffer->bufferLen) 
    ) {
        error |= `$INSTANCE_NAME`_ERR_MEMORY;
    }

    if(!error) {
        /* Act according to the state of the packet buffer */
        switch (buffer->receive.bufferState) {
            /* Waiting for start, ensure that the data byte is valid */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START: {
                if(byte != `$INSTANCE_NAME`_SYM_START ){
                    error |= `$INSTANCE_NAME`_ERR_START_SYM;
                    break;
                }
                /* Reset the count */
                rxBuffer->bufferIndex = ZERO;
                /* Store the byte */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /* Advance to the next state */
                *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_HEADER;
                break;
            }
            /* Waiting for the header */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_HEADER: {
                /* Store the byte */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /* Check to see if more data is required */
                if (rxBuffer->bufferIndex == `$INSTANCE_NAME`_LEN_HEADER) {
                    /* Store the payload length */
                    *payloadLen = (rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
                    if (*payloadLen == ZERO) {
                        /* Skip payload collection */
                        *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER;
                    } else {
                        /* Advance to the next state */
                        *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_PAYLOAD;
                    }
                }
                break;
            }
            /* Receiving Payload info */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_PAYLOAD: {
                /* Store the data  */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /* See if all data has been captured */
                if (rxBuffer->bufferIndex == (`$INSTANCE_NAME`_LEN_HEADER +  *payloadLen)){
                    /* Advance to next state */
                    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER;   
                /* Data out of range */
                } else if (rxBuffer->bufferIndex > (`$INSTANCE_NAME`_LEN_HEADER +  *payloadLen)){
                    /* Reset count */
                    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
                    error |= `$INSTANCE_NAME`_ERR_LENGTH;
                }
                break;
            }
            /* Wait for the footer */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER: {
                /* Store the data */
                rxBuffer->buffer[(rxBuffer->bufferIndex)++] = byte;
                /*If all data has been captured */
                uint16_t fullPacketLength = `$INSTANCE_NAME`_LEN_HEADER + *payloadLen + `$INSTANCE_NAME`_LEN_FOOTER;
                if (rxBuffer->bufferIndex == fullPacketLength) {
                    /* Packet is complete */   
                    *bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE;
                }
                break;
            }
            /* Packet is complete, but has not been handled, throw error */
            case `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE: {
                    error |= `$INSTANCE_NAME`_ERR_STATE;
                break;
            }
        }
    } 
     /* Return the packet state */
     return error;
}

/*******************************************************************************
* Function Name:`$INSTANCE_NAME`_parsePacket()
****************************************************************************//**
* \brief
*  Parses a data packet from the received data.
*
* \param packet
* Pointer to a packet structure to place the infomation in
*
* \return
* The error code of the result packet parsing
* The possible error codes are:
*
*  Errors codes                         | Description
*   ------------                        | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS        | The packet was successfully parsed.
*   `$INSTANCE_NAME`_ERR_FORMAT         | The packet was in the incorrect format.
*   `$INSTANCE_NAME`_ERR_MODULE         | An unknown module was requested.
*   `$INSTANCE_NAME`_ERR_LENGTH         | The packet payload length was outside the allowed value.
*   `$INSTANCE_NAME`_ERR_CHECKSUM       | The calculated checksum did not match the reported checksum.
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_parsePacket(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer) {
    uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Create local references */
    `$INSTANCE_NAME`_BUFFER_PROCESS_S* rxBuffer = &(buffer->receive.processBuffer);
    `$INSTANCE_NAME`_BUFFER_STATE_RECEIVE_T* bufferState = &(buffer->receive.bufferState);
    `$INSTANCE_NAME`_PACKET_S* packet = &(buffer->receive.packet);
    
    /* Ensure packet is complete */
    if (*bufferState != `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE){
        return `$INSTANCE_NAME`_ERR_INCOMPLETE;    
    }
    /* Ensure start of packet symbol */
    uint8 startByte = rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_START];
    if (startByte != `$INSTANCE_NAME`_SYM_START) {
        error |= `$INSTANCE_NAME`_ERR_START_SYM;
    }
    /* Get the Module */
    packet->moduleId = rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_MODULE_ID];
    if (packet->moduleId > `$INSTANCE_NAME`_ID_MODULE_MAX) {
        error |= `$INSTANCE_NAME`_ERR_MODULE;
    }
    /* Get the Command - Cannot tell if valid at this point */
    packet->cmd = rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_CMD];
    /* Get the payload length */
    packet->payloadLen = (rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_MSB] << BITS_ONE_BYTE) | rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_LEN_LSB];
    if (packet->payloadLen > `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) {
        error |= `$INSTANCE_NAME`_ERR_LENGTH;  
    }
    
    /* Ensure Payload array is allocated */
    if(packet->payload == NULL){
        error |= `$INSTANCE_NAME`_ERR_MEMORY;   
    }
    if(!error){
        /* Transfer the payload to the new buffer */
        memmove(packet->payload, &(rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_PAYLOAD]), packet->payloadLen); 

        /* Start of the footer */
        uint8_t* footerPtr = &(rxBuffer->buffer[`$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen]);
        /* Get the flags */
        uint8 flags3 = *footerPtr++;
        uint8 flags2 = *footerPtr++;
        uint8 flags1 = *footerPtr++;
        uint8 flags0 = *footerPtr++;
        packet->flags = (uint32_t) ((flags3 << BITS_THREE_BYTES) | (flags2 << BITS_TWO_BYTES) | (flags1 << BITS_ONE_BYTE) | flags0);
        /* Validate checksum */
        uint16_t calculatedChecksum = `$INSTANCE_NAME`_computeChecksum16(rxBuffer->buffer, `$INSTANCE_NAME`_LEN_HEADER + packet->payloadLen + `$INSTANCE_NAME`_LEN_FLAGS);
        uint8 checkSumMsb = *footerPtr++;
        uint8 checkSumLsb = *footerPtr++;
        uint16_t reportedChecksum = (checkSumMsb << BITS_ONE_BYTE) | checkSumLsb;
        if( calculatedChecksum != reportedChecksum) {
            error |= `$INSTANCE_NAME`_ERR_CHECKSUM;
        }
        /* Check end of packet symbol */
        uint8 endSymbol = *footerPtr;
        if (endSymbol != `$INSTANCE_NAME`_SYM_END) {
            error|= `$INSTANCE_NAME`_ERR_END_SYM;
        }
        /* Flush the buffer */
        `$INSTANCE_NAME`_flushRxBuffers(buffer);
        /* Return the error code */
    }
    return error;
} 

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_computeChecksum16()
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
uint16_t `$INSTANCE_NAME`_computeChecksum16(uint8_t* data, uint16_t length){
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
