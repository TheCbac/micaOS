/***************************************************************************//**
* \file micaPackets.h
* \version 1.0.0
*
* \brief
* Provides the definitions for MICA Packets
* \authors Craig Cheney
* \date 2017.11.02 CC - Document Created
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/

/**
* \defgroup group_packets Packets
* \{
* Definitions for binary communication between MICA devices
*/

#ifndef `$INSTANCE_NAME`_MICA_PACKETS_H
#define `$INSTANCE_NAME`_MICA_PACKETS_H
    /***************************************
    * Included files
    ***************************************/
    #include "cytypes.h"
    #include <stdbool.h>
    /***************************************
    * Macro definitions 
    ***************************************/
    /**
    * \defgroup group_packets_constants Constants 
    * \{
    * Unchanging values about the MICA Packets
    */
        #define MICA_PACKET_LEN_SYM_START       (1u) /**< Length of the Start of Packet Symbol */
        #define MICA_PACKET_LEN_MODULE_ID       (1u) /**< Length of the Module ID */
        #define MICA_PACKET_LEN_PAYLOAD_LEN     (2u) /**< Length of the Payload Length */
        #define MICA_PACKET_LEN_CMD             (1u) /**< Length of the Command */
        #define MICA_PACKET_LEN_CHECKSUM        (2u) /**< Length of the checksum */
        #define MICA_PACKET_LEN_SYM_END         (1u) /**< Length of the End of Packet Symbol */
        #define MICA_PACKET_LEN_HEADER          (MICA_PACKET_LEN_SYM_START + MICA_PACKET_LEN_MODULE_ID + MICA_PACKET_LEN_PAYLOAD_LEN  + MICA_PACKET_LEN_CMD) /**< Length of the packet overhead, for checksum validation */
        #define MICA_PACKET_LEN_FOOTER          (MICA_PACKET_LEN_CHECKSUM + MICA_PACKET_LEN_SYM_END) /**< Length of the footer */
        #define MICA_PACKET_LEN_OVERHEAD        (MICA_PACKET_LEN_HEADER + MICA_PACKET_LEN_FOOTER) /**< Total length of the packet overhead */
        #define MICA_PACKET_LEN_MAX_PAYLOAD     (1000) /**< Maximum length of the payload */
        #define MICA_PACKET_LEN_MAX_PACKET      (MICA_PACKET_LEN_OVERHEAD + MICA_PACKET_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */

        #define MICA_PACKET_INDEX_START         (0u) /**< Index of the start of packet symbol*/
        #define MICA_PACKET_INDEX_MODULE_ID     (1u) /**< Index of the module to talk to in the packet */
        #define MICA_PACKET_INDEX_CMD           (2u) /**< Index of the command to issue */
        #define MICA_PACKET_INDEX_LEN_MSB       (3u) /**< Index of the Payload length MSB */
        #define MICA_PACKET_INDEX_LEN_LSB       (4u) /**< Index of the Payload length LSB */
        #define MICA_PACKET_INDEX_PAYLOAD       (5u) /**< Index of the packet Payload */

        #define MICA_PACKET_SYM_START           (0x01u) /**< Start of Packet Symbol. All packets must begin with this symbol */
        #define MICA_PACKET_SYM_END             (0xAAu) /**< End of Packet Symbol. All packets must end with this symbol */

        #define MICA_PACKET_ID_MODULE_ENERGY    (0u)    /**< ID of the Energy Module */
        #define MICA_PACKET_ID_MODULE_ACTUATION (1u)    /**< ID of the Actuation Module */
        #define MICA_PACKET_ID_MODULE_POWER     (2u)    /**< ID of the Power Module */
        #define MICA_PACKET_ID_MODULE_SENSING   (3u)    /**< ID of the Sensing Module */
        #define MICA_PACKET_ID_MODULE_COMM      (4u)    /**< ID of the Communications Module */
        #define MICA_PACKET_ID_MODULE_CONTROL   (5u)    /**< ID of the Contorl Module */
        #define MICA_PACKET_ID_MODULE_MAX       (5u)    /**< Maximum value allowed */

        /* **** RESPONSES **** */
        #define MICA_PACKET_RESP_INDEX_START    (0u) /**< Index of the start of response symbol*/
        #define MICA_PACKET_RESP_INDEX_MODULE_ID (1u) /**< Index module that is responding*/
        #define MICA_PACKET_RESP_INDEX_STATUS   (2u) /**< Index of the response status*/
        #define MICA_PACKET_RESP_INDEX_LEN_MSB  (3u) /**< Index of the response payload length MSB */
        #define MICA_PACKET_RESP_INDEX_LEN_LSB  (4u) /**< Index of the response payload length LSB*/
        #define MICA_PACKET_RESP_INDEX_PAYLOAD  (5u) /**< Index of the response payload */

        #define MICA_PACKET_RESP_LEN_SYM_START   (1u) /**< Length of the response Start of Packet Symbol */
        #define MICA_PACKET_RESP_LEN_MODULE_ID   (1u) /**< Length of the module ID */        
        #define MICA_PACKET_RESP_LEN_STATUS      (1u) /**< Length of the response Status */        
        #define MICA_PACKET_RESP_LEN_PAYLOAD_LEN (2u) /**< Length of the response Payload Length */
        #define MICA_PACKET_RESP_LEN_CHECKSUM    (2u) /**< Length of the response checksum */
        #define MICA_PACKET_RESP_LEN_SYM_END     (1u) /**< Length of the response End of Packet Symbol */
        
    
        #define MICA_PACKET_RESP_LEN_HEADER     (MICA_PACKET_RESP_LEN_SYM_START + MICA_PACKET_RESP_LEN_MODULE_ID + MICA_PACKET_RESP_LEN_STATUS + MICA_PACKET_RESP_LEN_PAYLOAD_LEN) /**< Length of the response packet header */
        #define MICA_PACKET_RESP_LEN_FOOTER     (MICA_PACKET_RESP_LEN_CHECKSUM + MICA_PACKET_RESP_LEN_SYM_END) /**< Length of the response footer */
        #define MICA_PACKET_RESP_LEN_OVERHEAD   (MICA_PACKET_RESP_LEN_HEADER + MICA_PACKET_RESP_LEN_FOOTER) /**< Length of the response overhead */   
        #define MICA_PACKET_RESP_LEN_MAX_PAYLOAD (100) /**< Maximum length of the payload */     
        #define MICA_PACKET_RESP_LEN_MAX_PACKET (MICA_PACKET_RESP_LEN_OVERHEAD + MICA_PACKET_RESP_LEN_MAX_PAYLOAD) /**< Maximum length of the entire packet */
   
        /* **** COMMANDS **** */
        #define MICA_PACKET_RESP_SUCCESS        (0x00) /**< Successfully executed the previous command */
        #define MICA_PACKET_RESP_ASYNC          (0x80) /**< All response code >= this are not responses but rather async data */

        #define MICA_PACKET_CMD_CTRL_LED        (1u) /**< LED command - Set state of LEDs */
        #define MICA_PACKET_CMD_CTRL_DIO        (2u) /**< DIO command - Set the digital ports */
        #define MICA_PACKET_CMD_CTRL_AIO        (3u) /**< AIO command - Set the analog ports */
        #define MICA_PACKET_CMD_CTRL_BOOT       (4u) /**< BOOT command - Enter bootloader state */
        #define MICA_PACKET_CMD_CTRL_NAME       (5u) /**< NAME command - Set the name of the device */
        #define MICA_PACKET_CMD_CTRL_RST        (6u) /**< RST command - Reset the device */   
        #define MICA_PACKET_CMD_CTRL_LED_LEN    (4u) /**< Length of the LED command payload <Enable, R, G, B> */
        #define MICA_PACKET_CMD_CTRL_BOOT_LEN   (0u) /**< Length of the Boot command payload */

        #define MICA_PACKET_CMD_COMM_SCAN       (1u) /**< SCAN command - Set scan state of BLE */
        #define MICA_PACKET_CMD_COMM_CONN       (2u) /**< CONNECT command - Connect to a peer device */
        #define MICA_PACKET_CMD_COMM_DCON       (3u) /**< DISCONNECT command - Disconnect from a device*/
        #define MICA_PACKET_CMD_COMM_WRITE      (4u) /**< WRITE command - Write a characteristic over BLE */


        #define MICA_PACKET_CMD_COMM_READ       (5u) /**< READ command - Read a characteristic over BLE */

        #define MICA_PACKET_CMD_COMM_SCAN_LEN   (1u) /**< Length of the SCAN command payload (0 - stop, 1 - start) */
        #define MICA_PACKET_CMD_COMM_SCAN_STATE_INDEX (0u) /**< Index of the byte to start or stop */
        #define MICA_PACKET_CMD_COMM_CONN_LEN   (7u) /**< Length of the CONNECT command payload */
        #define MICA_PACKET_CMD_COMM_CONN_TYPE_INDEX (0u)  /**< Index of the CONNECT command address type */
        #define MICA_PACKET_CMD_COMM_CONN_ADDR_INDEX (1u)  /**< index of the CONNECT command address */
        #define MICA_PACKET_CMD_COMM_DCON_LEN   (6u) /**< Length of the DISCONNECT command payload */
        
    /* \} group_packets_constants */

    /***************************************
    * Enumerated Types
    ***************************************/
    /**
    * \defgroup group_packet_types Packet Status Types
    * \{
    * Possible packet status
    */
        typedef enum {
            PACKET_SUCCESS = 0x00u, /**< Returned Success */
            PACKET_ERR_FORMAT,      /**< The packet is not in the correct format */
            PACKET_ERR_MODULE,      /**< An invalid module was specified */
            PACKET_ERR_LENGTH,      /**< The amount of data available is outside the expected range. */
            PACKET_ERR_DATA,        /**< The data is not of the proper form  */
            PACKET_ERR_CMD,         /**< The command is not recognized */
            PACKET_ERR_CHECKSUM,    /**< The packet checksum does not match the expected value */
            PACKET_ERR_STATE,        /**< Device was in the incorrect state to execute the command */
            PACKET_ERR_DEVICE,      /**< An Unknown device was addressed */
            PACKET_ERR_UNKNOWN = 0x7F,      /**< An unknown error occurred */
            PACKET_ASYNC_REPORT_ADV = MICA_PACKET_RESP_ASYNC,       /**< Report an advertisement packet */
            PACKET_ASYNC_REPORT_CONN,    /**< Report a connection success  */
            PACKET_ASYNC_REPORT_DCON    /**< Report a disconnection  */
            
        } MICA_PACKET_ERROR_T;  

        typedef enum {
            STATE_WAIT_FOR_START,   /**< Waiting for the start byte to be received */
            STATE_RECEIVE_HEADER,   /**< Receiving the header Module ID, command, Payload length */
            STATE_RECEIVE_PAYLOAD,  /**< Receiving N bytes of payload data */
            STATE_RECEIVE_FOOTER    /**< Receiving Checksum and end of packet */
        } MICA_PACKET_STATE_T;
    /* \} group_packet_types*/  

    /***************************************
    * Structures
    ***************************************/
    /**
    * \defgroup group_packet_struct Structures
    * \{
    * Possible structures for libMICA
    */
        typedef struct {
            uint8_t moduleId;       /**< ID of the module commanded */
            uint8_t cmd;            /**< Command issued */
            uint16_t length;        /**< Length of the data received */
            uint8_t* payload;       /**< Pointer to the data */
        } MICA_PACKET_T;
                
        typedef struct {
            uint8_t moduleId;       /**< ID of the module commanded */
            MICA_PACKET_ERROR_T status; /**< Status Code of the response packet */
            uint16_t length;            /**< Length of the response payload */
            uint8_t* payload;           /**< Pointer to the payload */
        } MICA_RESPONSE_T;
    /* \} group_packet_struct*/

    /***************************************
    * Function declarations 
    ***************************************/
    /**
    * \defgroup group_packet_functions Public Functions
    * \{
    * Public functions for parsing packets
    */
        uint16_t mica_computeChecksum16(uint8_t* data, uint16_t length);
        MICA_PACKET_ERROR_T mica_parsePacket(uint8_t* dataBuffer, MICA_PACKET_T* packet);
        bool mica_processPacketByte(uint8_t dataByte, uint8_t* packetBuffer);
        void mica_processCommand(MICA_PACKET_T* packet,  MICA_RESPONSE_T* response);
        bool mica_sendResponsePacket(MICA_RESPONSE_T* response);
        void mica_processControlCmd(MICA_PACKET_T* packet, MICA_RESPONSE_T* response);
        void mica_processCommCmd(MICA_PACKET_T* packet, MICA_RESPONSE_T* response);
        void mica_setPacketTransport(void (* func)(uint32 ch));
        
    
    /* \} group_packet_functions */

#endif /* `$INSTANCE_NAME`_MICA_PACKETS_H */

/* \} group_packets */

/* [] END OF FILE */
