/***************************************************************************
*                                       MICA
* File: Sflash.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for interacting with the Supervisory flash
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.03 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "CyFlash.h"
    #include "cytypes.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_BASE_ADDR       (CY_SFLASH_USERBASE) /**< Base location in memory of the SFLASH for 256k devices  */
    #define `$INSTANCE_NAME`_SIZE_ROW        (CY_SFLASH_SIZEOF_USERROW) /**< The size in bytes of the SFlash row  */

    #define `$INSTANCE_NAME`_NUM_ROWS        (4u)    /**< Number of rows available for user data  */
    #define `$INSTANCE_NAME`_INDEX_ROW_NAME  (1u)    /**< Row index that contains the BLE Device Name  */
    
    #define `$INSTANCE_NAME`_NAME_LEN        (26u)   /**< Length of the name data */
    #define `$INSTANCE_NAME`_NAME_ROW        (1u)    /**< Row that contains the name data */  
    #define `$INSTANCE_NAME`_NAME_OFFSET     (0u)    /**< Offset in the row of the name data */  
    
    #define `$INSTANCE_NAME`_ERR_OK          (0u)   /**< Operation was successful */
    #define `$INSTANCE_NAME`_ERR_INDEX_RANGE (1u)   /**< Value passed in was outside the valid range */
    /***************************************
    * Function declarations 
    ***************************************/
    uint32 `$INSTANCE_NAME`_ReadRow(uint8 rowNum, uint8* dataBuffer);
    uint32 `$INSTANCE_NAME`_WriteRow(uint8 rowNum, const uint8* rowData);
    uint32 `$INSTANCE_NAME`_ReadLocalName(char* nameArray);
    uint32 `$INSTANCE_NAME`_WriteLocalName(uint8 len, char* nameArray);
    
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
