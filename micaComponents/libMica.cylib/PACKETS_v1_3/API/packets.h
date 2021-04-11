/***************************************************************************
*                                       MICA
* File: packets.h
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
    #define `$INSTANCE_NAME`_VERSION             (0x0104)/**< Version of the packet protocol, MSB -> Major, LSB -> Minor */
    
    /* **** FRAME DEFINITIONS **** */
    #define `$INSTANCE_NAME`_LEN_SYM_START       (1u) /**< Length of the Start of Packet Symbol */
    #define `$INSTANCE_NAME`_LEN_PAYLOAD_LEN     (2u) /**< Length of the Payload Length */
    #define `$INSTANCE_NAME`_LEN_FLAGS           (2u) /**< Length of the flags  */
    #define `$INSTANCE_NAME`_LEN_CMD             (1u) /**< Length of the Command */
    #define `$INSTANCE_NAME`_LEN_CHECKSUM        (2u) /**< Length of the checksum */
    #define `$INSTANCE_NAME`_LEN_SYM_END         (1u) /**< Length of the End of Packet Symbol */
    #define `$INSTANCE_NAME`_LEN_HEADER          (`$INSTANCE_NAME`_LEN_SYM_START + `$INSTANCE_NAME`_LEN_PAYLOAD_LEN  + `$INSTANCE_NAME`_LEN_CMD) /**< Length of the packet overhead, for checksum validation */
    #define `$INSTANCE_NAME`_LEN_FOOTER          (`$INSTANCE_NAME`_LEN_FLAGS + `$INSTANCE_NAME`_LEN_CHECKSUM + `$INSTANCE_NAME`_LEN_SYM_END) /**< Length of the footer */
    #define `$INSTANCE_NAME`_LEN_OVERHEAD        (`$INSTANCE_NAME`_LEN_HEADER + `$INSTANCE_NAME`_LEN_FOOTER) /**< Total length of the packet overhead */
    #define `$INSTANCE_NAME`_LEN_MAX_PAYLOAD     (256) /**< Maximum length of the payload */
    #define `$INSTANCE_NAME`_LEN_MAX_PACKET      (`$INSTANCE_NAME`_LEN_OVERHEAD + `$INSTANCE_NAME`_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */

    #define `$INSTANCE_NAME`_LEN_PAYLOAD_128     (0x80u)
    #define `$INSTANCE_NAME`_LEN_PACKET_128      (`$INSTANCE_NAME`_LEN_OVERHEAD  + `$INSTANCE_NAME`_LEN_PAYLOAD_128 )

    #define `$INSTANCE_NAME`_INDEX_START         (0u) /**< Index of the start of packet symbol*/
    #define `$INSTANCE_NAME`_INDEX_CMD           (1u) /**< Index of the command to issue */
    #define `$INSTANCE_NAME`_INDEX_LEN_MSB       (2u) /**< Index of the Payload length MSB */
    #define `$INSTANCE_NAME`_INDEX_LEN_LSB       (3u) /**< Index of the Payload length LSB */
    #define `$INSTANCE_NAME`_INDEX_PAYLOAD       (4u) /**< Index of the packet Payload */

    /* **** SYMBOL DEFINITIONS **** */
    #define `$INSTANCE_NAME`_SYM_START           (0x01u) /**< Start of Packet Symbol. All packets must begin with this symbol */
    #define `$INSTANCE_NAME`_SYM_END             (0xAAu) /**< End of Packet Symbol. All packets must end with this symbol */
    
    /* **** MODULE IDS **** */
    #define `$INSTANCE_NAME`_ID_MODULE_CONTROL   (0u)    /**< ID of the Control Module */
    #define `$INSTANCE_NAME`_ID_MODULE_ACTUATION (1u)    /**< ID of the Actuation Module */
    #define `$INSTANCE_NAME`_ID_MODULE_SENSING   (2u)    /**< ID of the Sensing Module */
    #define `$INSTANCE_NAME`_ID_MODULE_ENERGY    (3u)    /**< ID of the Energy Module */
    #define `$INSTANCE_NAME`_ID_MODULE_MAX       (3u)    /**< Maximum value allowed */
    
    /* **** PROCESSING ERROR FLAGS **** */
    #define `$INSTANCE_NAME`_ERR_SUCCESS        (0x00u)     /**< Returned Success */
    #define `$INSTANCE_NAME`_ERR_MEMORY         (1u << `$INSTANCE_NAME`_ERR_SHIFT_MEMORY )     /**< Failed to allocate memory*/
    #define `$INSTANCE_NAME`_ERR_START_SYM      (1u << `$INSTANCE_NAME`_ERR_SHIFT_START_SYM)   /**< Incorrect start symbol was received */
    #define `$INSTANCE_NAME`_ERR_END_SYM        (1u << `$INSTANCE_NAME`_ERR_SHIFT_END_SYM)      /**< Incorrect end symbol was received */
    #define `$INSTANCE_NAME`_ERR_LENGTH         (1u << `$INSTANCE_NAME`_ERR_SHIFT_LENGTH)   /**< The amount of data available is outside the expected range. */
    #define `$INSTANCE_NAME`_ERR_FORMAT         (1u << `$INSTANCE_NAME`_ERR_SHIFT_FORMAT)    /**< The packet is not in the correct format */
    #define `$INSTANCE_NAME`_ERR_INCOMPLETE     (1u << `$INSTANCE_NAME`_ERR_SHIFT_INCOMPLETE)    /**< The packet cannot be processed as it is incomplete */
//    #define `$INSTANCE_NAME`_ERR_MODULE         (1u << `$INSTANCE_NAME`_ERR_SHIFT_MODULE)    /**< An invalid module was specified */
    #define `$INSTANCE_NAME`_ERR_DATA           (1u << `$INSTANCE_NAME`_ERR_SHIFT_DATA)    /**< The data is not of the proper form  */
    #define `$INSTANCE_NAME`_ERR_CMD            (1u << `$INSTANCE_NAME`_ERR_SHIFT_CMD)    /**< The command is not recognized */
    #define `$INSTANCE_NAME`_ERR_CHECKSUM       (1u << `$INSTANCE_NAME`_ERR_SHIFT_CHECKSUM)    /**< The packet checksum does not match the expected value */
    #define `$INSTANCE_NAME`_ERR_STATE          (1u << `$INSTANCE_NAME`_ERR_SHIFT_STATE)     /**< Device was in the incorrect state to execute the command */
    #define `$INSTANCE_NAME`_ERR_DEVICE         (1u << `$INSTANCE_NAME`_ERR_SHIFT_DEVICE)     /**< An Unknown device was addressed */
    #define `$INSTANCE_NAME`_ERR_CALLBACK       (1u << `$INSTANCE_NAME`_ERR_SHIFT_CALLBACK)     /**< An invalid callback was attempted */
    #define `$INSTANCE_NAME`_ERR_UNKNOWN        (1u << `$INSTANCE_NAME`_ERR_SHIFT_UNKNOWN)     /**< An unknown error occurred - End of error space */


    #define `$INSTANCE_NAME`_ERR_SHIFT_MEMORY         (0u)    /**< Failed to allocate memory */
    #define `$INSTANCE_NAME`_ERR_SHIFT_START_SYM      (1u)     /**< Incorrect start symbol was received */
    #define `$INSTANCE_NAME`_ERR_SHIFT_END_SYM        (2u)     /**< Incorrect end symbol was received */
    #define `$INSTANCE_NAME`_ERR_SHIFT_LENGTH         (3u)     /**< The amount of data available is outside the expected range. */
    #define `$INSTANCE_NAME`_ERR_SHIFT_FORMAT         (4u)     /**< The packet is not in the correct format */
    #define `$INSTANCE_NAME`_ERR_SHIFT_INCOMPLETE     (5u)     /**< The packet cannot be processed as it is incomplete */
//    #define `$INSTANCE_NAME`_ERR_SHIFT_MODULE         (6u)     /**< An invalid module was specified */
    #define `$INSTANCE_NAME`_ERR_SHIFT_DATA           (7u)     /**< The data is not of the proper form  */
    #define `$INSTANCE_NAME`_ERR_SHIFT_CMD            (8u)     /**< The command is not recognized */
    #define `$INSTANCE_NAME`_ERR_SHIFT_CHECKSUM       (9u)     /**< The packet checksum does not match the expected value */
    #define `$INSTANCE_NAME`_ERR_SHIFT_STATE          (10u)     /**< Device was in the incorrect state to execute the command */
    #define `$INSTANCE_NAME`_ERR_SHIFT_DEVICE         (11u)     /**< An Unknown device was addressed */
    #define `$INSTANCE_NAME`_ERR_SHIFT_CALLBACK       (12u)     /**< An invalid callback was attempted */
    #define `$INSTANCE_NAME`_ERR_SHIFT_UNKNOWN        (31u)     /**< An unknown error occurred - End of error space */

    /* **** PACKET FLAGS **** */
    #define `$INSTANCE_NAME`_FLAG_ACK                   (1u << `$INSTANCE_NAME`_FLAG_SHIFT_ACK) /**< This packet is acknowledging the previous command */
    #define `$INSTANCE_NAME`_FLAG_NO_ACK                (1u << `$INSTANCE_NAME`_FLAG_SHIFT_NO_ACK) /**< The target device is not required to ACK the command  */
    #define `$INSTANCE_NAME`_FLAG_INVALID_CMD           (1u << `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_CMD) /**< The passed command was invalid  */
   
    
    #define `$INSTANCE_NAME`_FLAG_SHIFT_ACK             (0u) /**< This packet is acknowledging the previous command */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_NO_ACK          (1u) /**< The target device is not required to ACK the command */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_CMD     (2u) /**< The passed command was invalid */
   
    
    /* **** COMMAND SPACE **** */
    #define `$INSTANCE_NAME`_CMD_MIN                    (0x00) /**< Start of the host command space */
    #define `$INSTANCE_NAME`_CMD_MAX                    (0x7F) /**< End of the host command space */
    #define `$INSTANCE_NAME`_CMD_CONTROL_MIN            (0x00) /**< Start of the host control command space */
    #define `$INSTANCE_NAME`_CMD_CONTROL_MAX            (0x1F) /**< End of the host control command space */
    #define `$INSTANCE_NAME`_CMD_ACTUATION_MIN          (0x20) /**< Start of the host actuation command space */
    #define `$INSTANCE_NAME`_CMD_ACTUATION_MAX          (0x3F) /**< End of the host actuation command space */
    #define `$INSTANCE_NAME`_CMD_SENSING_MIN            (0x40) /**< Start of the host sensing command space */
    #define `$INSTANCE_NAME`_CMD_SENSING_MAX            (0x5F) /**< End of the host sensing command space */
    #define `$INSTANCE_NAME`_CMD_ENERGY_MIN             (0x60) /**< Start of the host energy command space */
    #define `$INSTANCE_NAME`_CMD_ENERGY_MAX             (0x7F) /**< End of the host energy command space */
    
    #define `$INSTANCE_NAME`_CMD_ID                     (0x00) /**< Request the ID of a device */
    
    /* **** RESPONSE SPACE **** */
    #define `$INSTANCE_NAME`_RSP_MIN                    (0x80) /**< Start of the response command space */
    #define `$INSTANCE_NAME`_RSP_MAX                    (0xFF) /**< End of the response command space */
    #define `$INSTANCE_NAME`_RSP_CONTROL_MIN            (0x80) /**< Start of the host control command space */
    #define `$INSTANCE_NAME`_RSP_CONTROL_MAX            (0x9F) /**< End of the host control command space */
    #define `$INSTANCE_NAME`_RSP_ACTUATION_MIN          (0xA0) /**< Start of the host actuation command space */
    #define `$INSTANCE_NAME`_RSP_ACTUATION_MAX          (0xBF) /**< End of the host actuation command space */
    #define `$INSTANCE_NAME`_RSP_SENSING_MIN            (0xC0) /**< Start of the host sensing command space */
    #define `$INSTANCE_NAME`_RSP_SENSING_MAX            (0xDF) /**< End of the host sensing command space */
    #define `$INSTANCE_NAME`_RSP_ENERGY_MIN             (0xE0) /**< Start of the host energy command space */
    #define `$INSTANCE_NAME`_RSP_ENERGY_MAX             (0xFF) /**< End of the host energy command space */
    
    #define `$INSTANCE_NAME`_RSP_BIT_SHIFT              (7u)   /**< Shift of the bit that indicates the packet contains a response */
    #define `$INSTANCE_NAME`_RSP_BIT                    (1u << `$INSTANCE_NAME`_RSP_BIT_SHIFT) /**< Bit that indicates the packet contains a response */
    
   
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
        uint16_t flags;         /**< Flags to include e.g. "ACK requested" */
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

    /* Communication structure  for RX/TX and callbacks */
    typedef struct {
        uint8_t (*rxReadByte)(void);   /**< Receive bytes from a communication port */
        void (*txPutArray)(uint8* src, uint16_t len);     /**< Place byte into send buffer */
        uint32_t (*rxGetBytesPending)(void);                  /**< Report number of bytes available to read */
        uint32_t (*txGetQueueSize)(void);                     /**< Get available size of the send buffer */
        uint32_t (*ackCallback)(`$INSTANCE_NAME`_PACKET_S* ackPacket);     /**< Function to call when a packet was acknowledged */
        uint32_t (*cmdCallback)(`$INSTANCE_NAME`_PACKET_S* cmdPacket);     /**< Function that gets called when a command was received */
    } `$INSTANCE_NAME`_COMMUNICATION_S;

    /* Struct containing both a send and receive buffer */
    typedef struct {
        `$INSTANCE_NAME`_BUFFER_SEND_S send;
        `$INSTANCE_NAME`_BUFFER_RECEIVE_S receive;   
        `$INSTANCE_NAME`_COMMUNICATION_S comms;           
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
    uint32_t `$INSTANCE_NAME`_processRxByte(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer); 
    uint32_t `$INSTANCE_NAME`_processRxQueue(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer);  
    uint32_t `$INSTANCE_NAME`_parsePacket(`$INSTANCE_NAME`_BUFFER_FULL_S* buffer);

    uint32_t `$INSTANCE_NAME`_acknowledgePacket(`$INSTANCE_NAME`_BUFFER_FULL_S* packet, uint32_t (*validateFn)(`$INSTANCE_NAME`_PACKET_S* rxPacket, `$INSTANCE_NAME`_PACKET_S* txPacket) );
    
    uint32_t `$INSTANCE_NAME`_getModuleFromCmd(uint8_t cmd, uint8_t *module);
    uint16_t `$INSTANCE_NAME`_computeChecksum16(uint8_t* data, uint16_t length);
    void `$INSTANCE_NAME`_printPacket(`$INSTANCE_NAME`_PACKET_S* packet, void (*printFn)(char *pszFmt, ...));
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */

