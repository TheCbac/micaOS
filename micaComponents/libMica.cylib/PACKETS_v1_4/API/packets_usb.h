/***************************************************************************
*                                 MICA  © 2018
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`_usb.h
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
*
* Brief:
*   Header for usbPackets.c
*
* 2018.11.19  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef `$INSTANCE_NAME`_USB_H
    #define `$INSTANCE_NAME`_USB_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include "micaCommon.h"
    #include "`$INSTANCE_NAME`.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    
    /***************************************
    * Enumerated Types
    ***************************************/

    /***************************************
    * Structures
    ***************************************/

    /***************************************
    * Function declarations 
    ***************************************/
    `$INSTANCE_NAME`_COMMUNICATION_S `$INSTANCE_NAME`_usbComms;     /**< Communciation structure for the USB manager */
    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t `$INSTANCE_NAME`_usb_init(uint16_t len);
    uint32_t `$INSTANCE_NAME`_usb_processIncoming(void);
    uint32_t `$INSTANCE_NAME`_usb_sendPacket(uint8_t cmd, uint16_t payloadLen, uint8_t *payload, uint16_t flags);
    uint32_t `$INSTANCE_NAME`_usb_log(char *msg, ...);
    
#endif /* `$INSTANCE_NAME`_USB_H */
/* [] END OF FILE */
