/***************************************************************************
*                                       MICA
* File: packets.h
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
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdbool.h>
    #include "cytypes.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_LEN_SYM_START       (1u) /**< Length of the Start of Packet Symbol */
    #define `$INSTANCE_NAME`_LEN_MODULE_ID       (1u) /**< Length of the Module ID */
    #define `$INSTANCE_NAME`_LEN_PAYLOAD_LEN     (2u) /**< Length of the Payload Length */
    #define `$INSTANCE_NAME`_LEN_FLAGS           (4u) /**< Length of the flags  */
    #define `$INSTANCE_NAME`_LEN_CMD             (1u) /**< Length of the Command */
    #define `$INSTANCE_NAME`_LEN_CHECKSUM        (2u) /**< Length of the checksum */
    #define `$INSTANCE_NAME`_LEN_SYM_END         (1u) /**< Length of the End of Packet Symbol */
    #define `$INSTANCE_NAME`_LEN_HEADER          (`$INSTANCE_NAME`_LEN_SYM_START + `$INSTANCE_NAME`_LEN_MODULE_ID + `$INSTANCE_NAME`_LEN_PAYLOAD_LEN  + `$INSTANCE_NAME`_LEN_CMD) /**< Length of the packet overhead, for checksum validation */
    #define `$INSTANCE_NAME`_LEN_FOOTER          (`$INSTANCE_NAME`_LEN_FLAGS + `$INSTANCE_NAME`_LEN_CHECKSUM + `$INSTANCE_NAME`_LEN_SYM_END) /**< Length of the footer */
    #define `$INSTANCE_NAME`_LEN_OVERHEAD        (`$INSTANCE_NAME`_LEN_HEADER + `$INSTANCE_NAME`_LEN_FOOTER) /**< Total length of the packet overhead */
    #define `$INSTANCE_NAME`_LEN_MAX_PAYLOAD     (256) /**< Maximum length of the payload */
    #define `$INSTANCE_NAME`_LEN_MAX_PACKET      (`$INSTANCE_NAME`_LEN_OVERHEAD + `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */

    #define `$INSTANCE_NAME`_LEN_BLOCK_PAYLOAD  (0x80u)
    #define `$INSTANCE_NAME`_LEN_BLOCK_PACKET   (`$INSTANCE_NAME`_LEN_OVERHEAD  + `$INSTANCE_NAME`_LEN_BLOCK_PAYLOAD )

    #define `$INSTANCE_NAME`_INDEX_START         (0u) /**< Index of the start of packet symbol*/
    #define `$INSTANCE_NAME`_INDEX_MODULE_ID     (1u) /**< Index of the module to talk to in the packet */
    #define `$INSTANCE_NAME`_INDEX_CMD           (2u) /**< Index of the command to issue */
    #define `$INSTANCE_NAME`_INDEX_LEN_MSB       (3u) /**< Index of the Payload length MSB */
    #define `$INSTANCE_NAME`_INDEX_LEN_LSB       (4u) /**< Index of the Payload length LSB */
    #define `$INSTANCE_NAME`_INDEX_PAYLOAD       (5u) /**< Index of the packet Payload */

    #define `$INSTANCE_NAME`_SYM_START           (0x01u) /**< Start of Packet Symbol. All packets must begin with this symbol */
    #define `$INSTANCE_NAME`_SYM_END             (0xAAu) /**< End of Packet Symbol. All packets must end with this symbol */

    #define `$INSTANCE_NAME`_ID_MODULE_ENERGY    (0u)    /**< ID of the Energy Module */
    #define `$INSTANCE_NAME`_ID_MODULE_ACTUATION (1u)    /**< ID of the Actuation Module */
    #define `$INSTANCE_NAME`_ID_MODULE_POWER     (2u)    /**< ID of the Power Module */
    #define `$INSTANCE_NAME`_ID_MODULE_SENSING   (3u)    /**< ID of the Sensing Module */
    #define `$INSTANCE_NAME`_ID_MODULE_COMM      (4u)    /**< ID of the Communications Module */
    #define `$INSTANCE_NAME`_ID_MODULE_CONTROL   (5u)    /**< ID of the Contorl Module */
    #define `$INSTANCE_NAME`_ID_MODULE_MAX       (5u)    /**< Maximum value allowed */
     /* **** RESPONSES **** */
    #define `$INSTANCE_NAME`_RESP_INDEX_START    (0u) /**< Index of the start of response symbol*/
    #define `$INSTANCE_NAME`_RESP_INDEX_MODULE_ID (1u) /**< Index module that is responding*/
    #define `$INSTANCE_NAME`_RESP_INDEX_STATUS   (2u) /**< Index of the response status*/
    #define `$INSTANCE_NAME`_RESP_INDEX_LEN_MSB  (3u) /**< Index of the response payload length MSB */
    #define `$INSTANCE_NAME`_RESP_INDEX_LEN_LSB  (4u) /**< Index of the response payload length LSB*/
    #define `$INSTANCE_NAME`_RESP_INDEX_PAYLOAD  (5u) /**< Index of the response payload */

    #define `$INSTANCE_NAME`_RESP_LEN_SYM_START   (1u) /**< Length of the response Start of Packet Symbol */
    #define `$INSTANCE_NAME`_RESP_LEN_MODULE_ID   (1u) /**< Length of the module ID */        
    #define `$INSTANCE_NAME`_RESP_LEN_STATUS      (1u) /**< Length of the response Status */        
    #define `$INSTANCE_NAME`_RESP_LEN_PAYLOAD_LEN (2u) /**< Length of the response Payload Length */
    #define `$INSTANCE_NAME`_RESP_LEN_CHECKSUM    (2u) /**< Length of the response checksum */
    #define `$INSTANCE_NAME`_RESP_LEN_SYM_END     (1u) /**< Length of the response End of Packet Symbol */
    

    #define `$INSTANCE_NAME`_RESP_LEN_HEADER     (`$INSTANCE_NAME`_RESP_LEN_SYM_START + `$INSTANCE_NAME`_RESP_LEN_MODULE_ID + `$INSTANCE_NAME`_RESP_LEN_STATUS + `$INSTANCE_NAME`_RESP_LEN_PAYLOAD_LEN) /**< Length of the response packet header */
    #define `$INSTANCE_NAME`_RESP_LEN_FOOTER     (`$INSTANCE_NAME`_RESP_LEN_CHECKSUM + `$INSTANCE_NAME`_RESP_LEN_SYM_END) /**< Length of the response footer */
    #define `$INSTANCE_NAME`_RESP_LEN_OVERHEAD   (`$INSTANCE_NAME`_RESP_LEN_HEADER + `$INSTANCE_NAME`_RESP_LEN_FOOTER) /**< Length of the response overhead */   
    #define `$INSTANCE_NAME`_RESP_LEN_MAX_PAYLOAD (100) /**< Maximum length of the payload */     
    #define `$INSTANCE_NAME`_RESP_LEN_MAX_PACKET (`$INSTANCE_NAME`_RESP_LEN_OVERHEAD + `$INSTANCE_NAME`_RESP_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */
    /* **** COMMANDS **** */
    #define `$INSTANCE_NAME`_RESP_SUCCESS        (0x00) /**< Successfully executed the previous command */
    #define `$INSTANCE_NAME`_RESP_ASYNC          (0x80) /**< All response code that are greater than or equal to this are not responses but rather async data */
    
    #define `$INSTANCE_NAME`_ERR_SUCCESS        (0x00u)     /**< Returned Success */
    #define `$INSTANCE_NAME`_ERR_MEMORY         (1u << `$INSTANCE_NAME`_ERR_SHIFT_MEMORY )     /**< Failed to allocate memory*/
    #define `$INSTANCE_NAME`_ERR_START_SYM      (1u << `$INSTANCE_NAME`_ERR_SHIFT_START_SYM)   /**< Incorrect start symbol was received */
    #define `$INSTANCE_NAME`_ERR_END_SYM        (1u << `$INSTANCE_NAME`_ERR_SHIFT_END_SYM)      /**< Incorrect end symbol was received */
    #define `$INSTANCE_NAME`_ERR_LENGTH         (1u << `$INSTANCE_NAME`_ERR_SHIFT_LENGTH)   /**< The amount of data available is outside the expected range. */
    #define `$INSTANCE_NAME`_ERR_FORMAT         (1u << `$INSTANCE_NAME`_ERR_SHIFT_FORMAT)    /**< The packet is not in the correct format */
    #define `$INSTANCE_NAME`_ERR_INCOMPLETE     (1u << `$INSTANCE_NAME`_ERR_SHIFT_INCOMPLETE)    /**< The packet cannot be processed as it is incomplete */
    #define `$INSTANCE_NAME`_ERR_MODULE         (1u << `$INSTANCE_NAME`_ERR_SHIFT_MODULE)    /**< An invalid module was specified */
    #define `$INSTANCE_NAME`_ERR_DATA           (1u << `$INSTANCE_NAME`_ERR_SHIFT_DATA)    /**< The data is not of the proper form  */
    #define `$INSTANCE_NAME`_ERR_CMD            (1u << `$INSTANCE_NAME`_ERR_SHIFT_CMD)    /**< The command is not recognized */
    #define `$INSTANCE_NAME`_ERR_CHECKSUM       (1u << `$INSTANCE_NAME`_ERR_SHIFT_CHECKSUM)    /**< The packet checksum does not match the expected value */
    #define `$INSTANCE_NAME`_ERR_STATE          (1u << `$INSTANCE_NAME`_ERR_SHIFT_STATE)     /**< Device was in the incorrect state to execute the command */
    #define `$INSTANCE_NAME`_ERR_DEVICE         (1u << `$INSTANCE_NAME`_ERR_SHIFT_DEVICE)     /**< An Unknown device was addressed */

    #define `$INSTANCE_NAME`_ERR_SHIFT_MEMORY         (0u)    /**< Failed to allocate memory */
    #define `$INSTANCE_NAME`_ERR_SHIFT_START_SYM      (1u)     /**< Incorrect start symbol was received */
    #define `$INSTANCE_NAME`_ERR_SHIFT_END_SYM        (2u)     /**< Incorrect end symbol was received */
    #define `$INSTANCE_NAME`_ERR_SHIFT_LENGTH         (3u)     /**< The amount of data available is outside the expected range. */
    #define `$INSTANCE_NAME`_ERR_SHIFT_FORMAT         (4u)     /**< The packet is not in the correct format */
    #define `$INSTANCE_NAME`_ERR_SHIFT_INCOMPLETE     (5u)     /**< The packet cannot be processed as it is incomplete */
    #define `$INSTANCE_NAME`_ERR_SHIFT_MODULE         (6u)     /**< An invalid module was specified */
    #define `$INSTANCE_NAME`_ERR_SHIFT_DATA           (7u)     /**< The data is not of the proper form  */
    #define `$INSTANCE_NAME`_ERR_SHIFT_CMD            (8u)     /**< The command is not recognized */
    #define `$INSTANCE_NAME`_ERR_SHIFT_CHECKSUM       (9u)     /**< The packet checksum does not match the expected value */
    #define `$INSTANCE_NAME`_ERR_SHIFT_STATE          (10u)     /**< Device was in the incorrect state to execute the command */
    #define `$INSTANCE_NAME`_ERR_SHIFT_DEVICE         (11u)     /**< An Unknown device was addressed */
    
    #define `$INSTANCE_NAME`_ERR__UNKNOWN             (31u)     /**< An unknown error occurred - End of error space */
    /* Async data */
    #define `$INSTANCE_NAME`_ASYNC_REPORT_ADV   (0x80u)     /**< Report an advertisement packet - Start of async space */
    #define `$INSTANCE_NAME`_ASYNC_REPORT_CONN  (0x81u)     /**< Report a connection success  */
    #define `$INSTANCE_NAME`_ASYNC_REPORT_DCON  (0x82u)     /**< Report a disconnection  */

    /* FLAGS */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_RESP            (0u) /**< A response is requested from the packet */
    
    #define `$INSTANCE_NAME`_FLAG_RESP                  (1u << `$INSTANCE_NAME`_FLAG_SHIFT_RESP) /**< A response is requested from the packet */
    

    /***************************************
    * Enumerated Types
    ***************************************/
    /* Possible states for receive buffer */
    typedef enum {
        `$INSTANCE_NAME`_BUFFER_RECEIVE_WAIT_FOR_START, /**< Waiting for the start byte to be received */
        `$INSTANCE_NAME`_BUFFER_RECEIVE_HEADER,         /**< Receiving the header Module ID, command, Payload length */
        `$INSTANCE_NAME`_BUFFER_RECEIVE_PAYLOAD,        /**< Receiving N bytes of payload data */
        `$INSTANCE_NAME`_BUFFER_RECEIVE_FOOTER,         /**< Receiving Checksum and end of packet */
        `$INSTANCE_NAME`_BUFFER_RECEIVE_COMPLETE        /**< Packet has finished being assembled  */
    } `$INSTANCE_NAME`_BUFFER_STATE_RECEIVE_T;
    
        /* Possible states for send buffer */
    typedef enum {
        `$INSTANCE_NAME`_BUFFER_SEND_WAIT,              /**< Waiting for the buffer to be ready to send */
        `$INSTANCE_NAME`_BUFFER_SEND_READY,             /**< Buffer is ready to be sent */
        `$INSTANCE_NAME`_BUFFER_SEND_QUEUEING,          /**< Move the buffer to the FIFO UART TX buffer*/
        `$INSTANCE_NAME`_BUFFER_SEND_COMPLETE,          /**< buffer has be sent*/
    } `$INSTANCE_NAME`_BUFFER_STATE_SEND_T;
    
    /* State of packet */
    typedef enum {
        `$INSTANCE_NAME`_PACKET_UNHANDLED,          /**< Packet has not been handled in any way */
        `$INSTANCE_NAME`_PACKET_ACK,                /**< Packet has been acknowledged*/
    } `$INSTANCE_NAME`_PACKET_STATE_T;
    /***************************************
    * Structures
    ***************************************/
    /* Process buffer struct */
    typedef struct {
        uint8_t *buffer;                            /**< Pointer to the buffer */
        uint16_t bufferLen;                         /**< Length of the buffer */
        uint16_t bufferIndex;                       /**< Index of the current value */
        uint32_t timeCount;                         /**< Time count of the last buffer action */
    } `$INSTANCE_NAME`_BUFFER_PROCESS_S;


    /* Packet buffer struct */
    typedef struct {
        uint8_t moduleId;       /**< ID of the module commanded */
        uint8_t cmd;            /**< Command issued */
        uint8_t *payload;       /**< Pointer to the data */
        uint16_t payloadMax;   /**< Size of the payload array */
        uint16_t payloadLen;    /**< Length of the payload in the buffer*/
        uint32_t flags;         /**< Flags to include e.g. "ACK requested" */
        uint32_t error;          /**< Error code of packet*/
    } `$INSTANCE_NAME`_PACKET_S;

    /* Buffer struct for send and receive */
    typedef struct {
        `$INSTANCE_NAME`_PACKET_S packet;        /**< Receives data from the process buffer and passes to app */
        `$INSTANCE_NAME`_BUFFER_PROCESS_S processBuffer;    /**< Send Buffer Structure */
        `$INSTANCE_NAME`_BUFFER_STATE_SEND_T bufferState;         /**< State of the send buffer */
    } `$INSTANCE_NAME`_BUFFER_SEND_S;

    /* Buffer struct for send and receive */
    typedef struct {
        `$INSTANCE_NAME`_PACKET_S packet;      /**< Receives data from the process buffer and passes to app */
        `$INSTANCE_NAME`_BUFFER_PROCESS_S processBuffer;     /**< Receive Buffer Structure */
        `$INSTANCE_NAME`_BUFFER_STATE_RECEIVE_T bufferState;       /**< State of the receive buffer */
    } `$INSTANCE_NAME`_BUFFER_RECEIVE_S;

/* Struct containing both a send and receive buffer */
    typedef struct {
        `$INSTANCE_NAME`_BUFFER_SEND_S send;
        `$INSTANCE_NAME`_BUFFER_RECEIVE_S receive;
    } `$INSTANCE_NAME`_BUFFER_FULL_S;


    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t `$INSTANCE_NAME`_initialize(`$INSTANCE_NAME`_BUFFER_FULL_S *packetBuffer);
    uint32_t `$INSTANCE_NAME`_generateBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S *packetBuffer, uint16_t bufferSize);
    uint32_t `$INSTANCE_NAME`_destoryBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S *buffer);
    void `$INSTANCE_NAME`_flushRxBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer);
    void `$INSTANCE_NAME`_flushTxBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer);
    void `$INSTANCE_NAME`_flushBuffers(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer);


    uint32_t `$INSTANCE_NAME`_constructPacket(`$INSTANCE_NAME`_BUFFER_FULL_S *buffer);
    uint32_t `$INSTANCE_NAME`_sendPacket(`$INSTANCE_NAME`_BUFFER_FULL_S *buffer);

    uint32_t `$INSTANCE_NAME`_processRxByte(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer, uint8_t byte);
    uint32_t `$INSTANCE_NAME`_parsePacket(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer);

    uint16_t `$INSTANCE_NAME`_computeChecksum16(uint8_t* data, uint16_t length);
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */

