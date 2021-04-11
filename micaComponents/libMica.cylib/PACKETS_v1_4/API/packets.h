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
    #include <stdint.h>
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
    #define `$INSTANCE_NAME`_LEN_MAX_PAYLOAD     (512) /**< Maximum length of the payload */
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
    #define `$INSTANCE_NAME`_FLAG_SHIFT_ACK             (0u) /**< This packet is acknowledging the previous command */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_NO_ACK          (1u) /**< The target device is not required to ACK the command */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_CMD     (2u) /**< The passed command was invalid */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_STATE   (3u) /**< The device was in an invalid state to execute the command */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_ARGS    (4u) /**< The arguments passed in with the command were not valid*/
    #define `$INSTANCE_NAME`_FLAG_SHIFT_MEMORY          (5u) /**< Ran out of memory */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_ILLEGAL_OPERATION (6u) /**< Illegal operation occurred */
    #define `$INSTANCE_NAME`_FLAG_SHIFT_UNKNOWN_ERR     (15u) /**< An unknown error occurred */
    
    #define `$INSTANCE_NAME`_FLAG_NONE                  (0x00) /** < No flags to be sent */
    #define `$INSTANCE_NAME`_FLAG_ACK                   (1u << `$INSTANCE_NAME`_FLAG_SHIFT_ACK) /**< This packet is acknowledging the previous command */
    #define `$INSTANCE_NAME`_FLAG_NO_ACK                (1u << `$INSTANCE_NAME`_FLAG_SHIFT_NO_ACK) /**< The target device is not required to ACK the command  */
    #define `$INSTANCE_NAME`_FLAG_INVALID_CMD           (1u << `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_CMD) /**< The passed command was invalid  */
    #define `$INSTANCE_NAME`_FLAG_INVALID_STATE         (1u << `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_STATE) /**< The device was in an invalid state to execute the command  */
    #define `$INSTANCE_NAME`_FLAG_INVALID_ARGS          (1u << `$INSTANCE_NAME`_FLAG_SHIFT_INVALID_ARGS) /**< The arguments passed in with the command were not valid  */
    #define `$INSTANCE_NAME`_FLAG_MEMORY                (1u << `$INSTANCE_NAME`_FLAG_SHIFT_MEMORY) /**< Ran out of memory  */
    #define `$INSTANCE_NAME`_FLAG_ILLEGAL_OPERATION     (1u << `$INSTANCE_NAME`_FLAG_SHIFT_ILLEGAL_OPERATION) /**< Illegal operation occurred  */
    #define `$INSTANCE_NAME`_FLAG_UNKNOWN_ERR           (1u << `$INSTANCE_NAME`_FLAG_SHIFT_UNKNOWN_ERR) /**< An unknown error occurred  */
    
    
    

   
    
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
    
    /* **** CONTROL COMMANDS **** */
    #define `$INSTANCE_NAME`_CMD_ID                     (0x00) /**< Request the ID of a device */
    #define `$INSTANCE_NAME`_CMD_MODE                   (0x01) /**< Change the operating mode (active app) */
    #define `$INSTANCE_NAME`_CMD_SCAN_START             (0x02) /**< Start a BLE Scan */
    #define `$INSTANCE_NAME`_CMD_SCAN_STOP              (0x03) /**< Stop a BLE Scan */
    #define `$INSTANCE_NAME`_CMD_CONNECT                (0x04) /**< Connect to a remote device */
    #define `$INSTANCE_NAME`_CMD_DISCONNECT             (0x05) /**< Disconnect from a remote device */
    #define `$INSTANCE_NAME`_CMD_CONNECT_CANCEL         (0x06) /**< Cancels a Pending connection */
    #define `$INSTANCE_NAME`_CMD_RELAY_ENTER            (0x07) /**< Enter Relay mode */
    #define `$INSTANCE_NAME`_CMD_RELAY_EXIT             (0x08) /**< Exit Relay mode */
    #define `$INSTANCE_NAME`_CMD_NAME                   (0x09) /**< Change the name of the device */
    #define `$INSTANCE_NAME`_CMD_RESET                  (0x0A) /**< Perform a software reset of the device */
    #define `$INSTANCE_NAME`_CMD_CHAR_WRITE             (0x0B) /**< Write to a BLE characteristic */
    #define `$INSTANCE_NAME`_CMD_CHAR_READ              (0x0C) /**< Read from a BLE characteristic */
    
    #define `$INSTANCE_NAME`_MODE_NORMAL                (0x00) /**< ID of normal mode */
    #define `$INSTANCE_NAME`_MODE_BOOTLOAD              (0x00) /**< ID of bootload mode */
    
    
    
    /* **** ACTUATION COMMANDS **** */
    
    /* **** SENSING COMMANDS **** */
    #define `$INSTANCE_NAME`_CMD_SENSORS_START          (0x40) /**< Start the desired sensors */
    #define `$INSTANCE_NAME`_CMD_SENSORS_STOP           (0x41) /**< Stop the desired sensors */
    
    /* **** ENERGY COMMANDS **** */
    
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
    
    /* **** CONTROL RESPONSES **** */
    #define `$INSTANCE_NAME`_RSP_DEVICE_FOUND           (0x80) /**< A remote device was found*/
    #define `$INSTANCE_NAME`_RSP_SCAN_STOPPED           (0x81) /**< The current scan was stopped */
    #define `$INSTANCE_NAME`_RSP_CONNECTED              (0x82) /**< Successfully connected to the remote device*/
    #define `$INSTANCE_NAME`_RSP_DISCONNECTED           (0x83) /**< The BLE device was successfully disconnected */
    #define `$INSTANCE_NAME`_RSP_CONNECTION_LOST        (0x84) /**< The BLE connection was lost */
    #define `$INSTANCE_NAME`_RSP_RELAY_EXIT             (0x85) /**< The device was forced out of relay mode */
    #define `$INSTANCE_NAME`_RSP_READ                   (0x86) /**< Data returned from a read operation */
    #define `$INSTANCE_NAME`_RSP_NOTIFY                 (0x87) /**< Data returned from a notify operation */
    #define `$INSTANCE_NAME`_RSP_LOG                    (0x88) /**< Log data */
    #define `$INSTANCE_NAME`_RSP_MODE                   (0x89) /**< The device entered a new mode */
    
    
    /* **** ACTUATION RESPONSES **** */
    /* **** SENSING RESPONSES **** */
    #define `$INSTANCE_NAME`_RSP_DATA                   (0xC0) /**< Data reported by the sensors */
    #define `$INSTANCE_NAME`_RSP_SENSORS_STOPPED        (0xC1) /**< The running sensors were halted */
    
    /* **** ENERGY RESPONSES **** */
    
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
        void (*txPutArray)(uint8_t *src, uint16_t len);     /**< Place byte into send buffer */
        uint32_t (*rxGetBytesPending)(void);                  /**< Report number of bytes available to read */
        uint32_t (*txGetQueueSize)(void);                     /**< Get available size of the send buffer */
        uint32_t (*ackCallback)(`$INSTANCE_NAME`_PACKET_S* ackPacket);     /**< Function to call when a packet was acknowledged */
        uint32_t (*cmdCallback)(`$INSTANCE_NAME`_PACKET_S* cmdPacket, `$INSTANCE_NAME`_PACKET_S* rspPacket);     /**< Function that gets called when a command was received */
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
    uint32_t `$INSTANCE_NAME`_handleCmdPacket(`$INSTANCE_NAME`_BUFFER_FULL_S* packet);
    
    uint32_t `$INSTANCE_NAME`_getModuleFromCmd(uint8_t cmd, uint8_t *module);
    uint16_t `$INSTANCE_NAME`_computeChecksum16(uint8_t* data, uint16_t length);
    void `$INSTANCE_NAME`_printPacket(`$INSTANCE_NAME`_PACKET_S* packet, void (*printFn)(char *pszFmt, ...));

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */

