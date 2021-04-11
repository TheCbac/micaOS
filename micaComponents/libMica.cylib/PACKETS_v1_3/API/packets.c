/***************************************************************************
*                                       MICA
* File: packets.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.4
* Author: Craig Cheney
*
* Brief:
*   Binary packet specification for MICA
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.09.17 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"
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
    /* Set everything to zero */
    memset(packetBuffer, ZERO, sizeof(`$INSTANCE_NAME`_BUFFER_FULL_S ));
    /* Reset the state */ 
    packetBuffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
    /* Reset the tx state */
    packetBuffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;
    return `$INSTANCE_NAME`_ERR_SUCCESS;
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
    uint8_t* txPayload = packetBuffer->send.packet.payload;
    
    /* Make sure that buffers have not already been allocated */
    if(rxBuffer->buffer != NULL || txBuffer->buffer != NULL || rxPayload != NULL || txPayload != NULL){
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
        packetBuffer->receive.bufferState = `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START;
        
        /*  Create the txPayload */
        uint8* txPayloadAdr = (uint8 *) calloc(ONE, bufferSize);
        if(txPayloadAdr == NULL){
            error |= `$INSTANCE_NAME`_ERR_MEMORY; 
            goto `$INSTANCE_NAME`_clean4;
        }
        packetBuffer->send.packet.payload = txPayloadAdr;
        packetBuffer->send.packet.payloadMax = bufferSize;
        packetBuffer->send.bufferState = `$INSTANCE_NAME`_BUFFER_SEND_WAIT;

        /* Clean up on error */
        if(error) {  
`$INSTANCE_NAME`_clean4:
            free(txPayloadAdr);      
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
    /* Free the send payload buffer is it exists */
    if(buffer->send.packet.payload != NULL) { 
        free(buffer->send.packet.payload);   
        buffer->send.packet.payload = NULL;
        buffer->send.packet.payloadMax = ZERO;
        buffer->send.packet.payloadLen = ZERO;
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
    /* Ensure valid txFunction */
    if(buffer->comms.txPutArray == NULL){
        error |= `$INSTANCE_NAME`_ERR_CALLBACK;
    }
    if(!error) {
        /* Write out the function */
        // `$txFunction`(txBuffer->buffer, txBuffer->bufferIndex );
        // @TODO: check available buffer size first
        buffer->comms.txPutArray(txBuffer->buffer, txBuffer->bufferIndex );
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
uint32_t `$INSTANCE_NAME`_processRxByte(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer) {
     uint32_t error = `$INSTANCE_NAME`_ERR_SUCCESS;
     /* Ensure RX Function exists */
     if(buffer->comms.rxReadByte == NULL || buffer->comms.rxGetBytesPending == NULL){
         error |= `$INSTANCE_NAME`_ERR_CALLBACK;
     }
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
    /* Ensure error free and data is available */
    if(!error && buffer->comms.rxGetBytesPending()) {
        /* Get the data */
        uint8_t byte = buffer->comms.rxReadByte();
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
* Function Name: `$INSTANCE_NAME`_processRxQueue()
****************************************************************************//**
* \brief
*  Processes all of the pending data in the RX queue
*
* \param buffer
* The packet buffer to call
*
* \return
*  A number indicating the error code
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_SUCCESS            | On Successful init
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_processRxQueue(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer){
    /* Get the number of pending bytes */
    uint32_t pendingBytes = buffer->comms.rxGetBytesPending();
    uint32_t i;
    uint32_t err = `$INSTANCE_NAME`_ERR_SUCCESS;
    /* Procces each byte */
    for(i = ZERO; i< pendingBytes; i++){
        err |= `$INSTANCE_NAME`_processRxByte(buffer);
        /* If the packet is complete Start Action on it*/
        if(buffer->receive.bufferState == `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE){
            /* Parse the packet */
            err |= `$INSTANCE_NAME`_parsePacket(buffer);
            if(!err){
                if(buffer->comms.ackCallback != NULL && buffer->comms.ackCallback != NULL){
                    /* Local Reference */
                    `$INSTANCE_NAME`_PACKET_S *rxPacket = &(buffer->receive.packet);
                    /* Is the packet an ACK or CMD packet */
                    if(rxPacket->flags & `$INSTANCE_NAME`_FLAG_ACK){
                        /* Call the ack callback */
                       err |= buffer->comms.ackCallback(rxPacket);
                    } else {
                        /* Call the cmd callback */
                       err |= buffer->comms.cmdCallback(rxPacket);
                    }
                } else {
                    err |= `$INSTANCE_NAME`_ERR_CALLBACK;
                }
            }
        }
    }
    return err;
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

    /* Get the Command - Cannot tell if valid at this point */
    uint8_t cmd =  rxBuffer->buffer[`$INSTANCE_NAME`_INDEX_CMD];
    packet->cmd = cmd;
    /* Populate the module */
    error |= `$INSTANCE_NAME`_getModuleFromCmd(cmd, &(packet->moduleId));
    
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
        uint8 flags1 = *footerPtr++;
        uint8 flags0 = *footerPtr++;
        packet->flags = (uint32_t) ((flags1 << BITS_ONE_BYTE) | flags0);
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
* Function Name: `$INSTANCE_NAME`_acknowledgePacket()
****************************************************************************//**
* \brief
*  Respond to a received packet
*
* \param rxPacket [in]
*  Pointer to the received packet
*
* \param validateFn [in]
*  Pointer to the device specific validation function
* 
* \return
*  Returns the error of associated with 
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_acknowledgePacket(`$INSTANCE_NAME`_BUFFER_FULL_S* packet, uint32_t (*validateFn)(`$INSTANCE_NAME`_PACKET_S* rxPacket, `$INSTANCE_NAME`_PACKET_S* txPacket) ){
    `$INSTANCE_NAME`_PACKET_S* rxPacket = &(packet->receive.packet);
    `$INSTANCE_NAME`_PACKET_S* txPacket = &(packet->send.packet);
    /* Set the default settings */
    txPacket->moduleId = rxPacket->moduleId;
    txPacket->cmd = rxPacket->cmd;
    txPacket->flags = packets_FLAG_ACK;
    /* Validate the command */
    uint32_t validateErr = validateFn(rxPacket, txPacket);
    uint32_t responseErr = packets_ERR_SUCCESS;
    /* Command is valid */
    if(validateErr ==`$INSTANCE_NAME`_ERR_SUCCESS){
        /* Respond if the NO ACK flag is not set */
        if( !(packet->receive.packet.flags & `$INSTANCE_NAME`_FLAG_NO_ACK)){
            /* Send the response packet */
            responseErr = `$INSTANCE_NAME`_sendPacket(packet);
        }
    /* An error occured during validation */
    } else {
        responseErr = validateErr;
    }
    return responseErr;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getModuleFromCmd()
****************************************************************************//**
* \brief
*  Returns the module id from the CMD
*
* \param cmd [in]
* The host or response command
*
* \param module [out]
* Pointer on where to place the output
*
* \return
* Error of the operation
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_getModuleFromCmd(uint8_t cmd, uint8_t *module) {
    uint8 id;
    /* Mask the Response flag */
    cmd &= (~`$INSTANCE_NAME`_RSP_BIT);
    /* Check the memory space */
    if (cmd >= `$INSTANCE_NAME`_CMD_CONTROL_MIN && cmd <= `$INSTANCE_NAME`_CMD_CONTROL_MAX) {
        id = `$INSTANCE_NAME`_ID_MODULE_CONTROL;
    } else if (cmd >= `$INSTANCE_NAME`_CMD_ACTUATION_MIN && cmd <= `$INSTANCE_NAME`_CMD_ACTUATION_MAX){
        id = `$INSTANCE_NAME`_ID_MODULE_ACTUATION;   
    } else if (cmd >= `$INSTANCE_NAME`_CMD_SENSING_MIN && cmd <= `$INSTANCE_NAME`_CMD_SENSING_MAX){
        id = `$INSTANCE_NAME`_ID_MODULE_SENSING;   
    }  else if (cmd >= `$INSTANCE_NAME`_CMD_ENERGY_MIN && cmd <= `$INSTANCE_NAME`_CMD_ENERGY_MAX){
        id = `$INSTANCE_NAME`_ID_MODULE_ENERGY;   
    } else {
        return `$INSTANCE_NAME`_ERR_UNKNOWN;
    }
    /* Set the module value out */
    *module = id;
    /* Return success */
    return `$INSTANCE_NAME`_ERR_SUCCESS;
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

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_printPacket()
****************************************************************************//**
* \brief
*  Prints the content of a packet
*
* \param packet [in]
*  Packet to display
* 
* \param fn [in]
*   Print function to use to display results
* 
* \return
*  None
*******************************************************************************/
  void `$INSTANCE_NAME`_printPacket(`$INSTANCE_NAME`_PACKET_S* packet, void (*printFn)(char *pszFmt, ...)){
    printFn("\r\nModule Id: %d\r\n", packet->moduleId);
    printFn("Command: %x\r\n", packet->cmd);
    uint16_t len = packet->payloadLen; 
    printFn("payload Len: %d\r\n", len);
    printFn("Payload:[ ", packet->cmd);
    uint16_t i;
    for(i = ZERO; i<len; i++){
        printFn("0x%x ",packet->payload[i]);
    }
    printFn("]\r\n");
    printFn("Flags: 0x%x\r\n\r\n", packet->flags);
}

/* [] END OF FILE */
