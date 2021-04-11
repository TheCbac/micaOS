/***************************************************************************
*                                       MICA
* File: OTA_Updates.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for executing Over the Air Updates (OTA)
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.01 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include "cytypes.h"
    #include "CyLib.h"
    #include "`$OTA_BLE_NAME`.h"
    
    /* Debugging include file */
    #if `$DEBUG_OTA` /* DEBUG_OTA */
        #include "`$DEBUG_PRINT_INCLUDE`.h"
    #endif /* DEBUG_OTA */
    
    /***************************************
    * Enumerations
    ***************************************/
    `#declare_enum OTA_TYPES_T`
    /***************************************
    * Macro Definitions
    ***************************************/

    /* Offset for flags */
    #define `$INSTANCE_NAME`_OFFSET_FLAG_STACK      (10u)
    #define `$INSTANCE_NAME`_OFFSET_FLAG_APP        (20u)
    /* Base addresses */
    #define `$INSTANCE_NAME`_BASE_ADDR_STACK        (CYDEV_FLASH_BASE + (CYDEV_FLASH_SIZE - ((uint32)CYDEV_FLS_ROW_SIZE)))
    #define `$INSTANCE_NAME`_BASE_ADDR_APP          (CYDEV_FLASH_BASE + (CYDEV_FLASH_SIZE - ((uint32)CYDEV_FLS_ROW_SIZE * 2u)))
    /* Bootloading MetaData */
    #define `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_1               (0x01u)
    #define `$INSTANCE_NAME`_MD_SIZEOF                       (64u)
    #define `$INSTANCE_NAME`_MD_BASE_ADDR(appId)    (CYDEV_FLASH_BASE + (CYDEV_FLASH_SIZE - ((uint32)(appId) * CYDEV_FLS_ROW_SIZE) - \
                                                                        `$INSTANCE_NAME`_MD_SIZEOF))
    #define `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_OFFSET(appId)   (`$INSTANCE_NAME`_MD_BASE_ADDR(appId) + 16u)
    /* Flags */
    #define `$INSTANCE_NAME`_FLAG_SET               (0u)
    #define `$INSTANCE_NAME`_FLAG_CLEAR             (1u)
    #define `$INSTANCE_NAME`_FLAG_UPDATE_STACK      (`$INSTANCE_NAME`_BASE_ADDR_STACK + `$INSTANCE_NAME`_OFFSET_FLAG_STACK)
    #define `$INSTANCE_NAME`_FLAG_UPDATE_APP        (`$INSTANCE_NAME`_BASE_ADDR_APP   + `$INSTANCE_NAME`_OFFSET_FLAG_APP)
    /* Macro to get the flag status */
    #define `$INSTANCE_NAME`_GET_FLAG_UPDATE_STACK  ( (uint32) CY_GET_XTND_REG8( (volatile uint8 *)`$INSTANCE_NAME`_FLAG_UPDATE_STACK) )
    #define `$INSTANCE_NAME`_GET_FLAG_UPDATE_APP    ( (uint32) CY_GET_XTND_REG8( (volatile uint8 *)`$INSTANCE_NAME`_FLAG_UPDATE_APP) )
    /* Bonding status */
    #define `$INSTANCE_NAME`_BONDING_ENABLED        ((CYBLE_GAP_ROLE_PERIPHERAL || CYBLE_GAP_ROLE_CENTRAL) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
    /* Progam IDs */
    #define `$INSTANCE_NAME`_ID_PROGRAM_STACK       (0u)
    #define `$INSTANCE_NAME`_ID_PROGRAM_APP         (1u)
    /* Timeout definitions */
    #define `$INSTANCE_NAME`_TIMEOUT_50_MS          (5u)
    
    /* Enable or disable the debugging functionality */
    #if `$DEBUG_OTA`
        #define `$INSTANCE_NAME`_DBG_PRINT(a)       do { `$DEBUG_PRINT_FUNCTION`(a); } while (0)
    #else
        #define `$INSTANCE_NAME`_DBG_PRINT(a)       do { (void)0; } while (0)
    #endif  /* DEBUG_OTA */
    /***************************************
    * Function declarations 
    ***************************************/
    
    /* OTA_TYPE */
    #if (`$OTA_TYPE` == `$INSTANCE_NAME`__STACK_PROJECT)
        void `$INSTANCE_NAME`_BootUserApp(void);
        void `$INSTANCE_NAME`_AfterStackImageUpdate(void);
        
    #elif (`$OTA_TYPE` == `$INSTANCE_NAME`__APP_PROJECT)
        void `$INSTANCE_NAME`_InitializeCodeSharing(void);
        void `$INSTANCE_NAME`_AfterAppImageUpdate(void);
        void `$INSTANCE_NAME`_EnterBootloadMode(void);
    #endif/* OTA_TYPE */

    
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
