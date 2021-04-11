/***************************************************************************
*                                       MICA
* File: I2C_API.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v2.0
* Author: Craig Cheney
*
* Brief:
*   Header for the MICA I2C API
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.05.03 CC - Transitioned to I2C component v4 (timeout)
*   2018.03.14 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"    
    #include "micaCommon.h"
    
    #define `$INSTANCE_NAME`_SCB_STATUS     (`$isScb`)
    
    #if (`$INSTANCE_NAME`_SCB_STATUS)
        #include "`$i2cInstanceName`_I2C.h"
    #else
        #include "`$i2cInstanceName`.h"
    #endif /* End `isScb` */ 
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_ERR_OK         (0u) /**< Operation succedded */
    #define `$INSTANCE_NAME`_ERR_READ       (1u) /**< An error occured during the read */
    
    #define `$INSTANCE_NAME`_MASK_READ_ERR  (0x80000000) /**< Mask for determining if an error occured during the read operation. MSB of uint32_t */
    
    #define `$i2cInstanceName`_TIMEOUT_WRITE        (MICA_DELAY_MS_SEC_QUARTER) /* Delay for writting time out */
    #define `$i2cInstanceName`_TIMEOUT_READ        (MICA_DELAY_MS_SEC_QUARTER) /* Delay for reading time out */
    
    
    /* Function like macros */
    #define `$INSTANCE_NAME`_Start()    `$i2cInstanceName`_Start()    
    #define `$INSTANCE_NAME`_Stop()     `$i2cInstanceName`_Stop()  
    
    /***************************************
    * Structs
    ***************************************/ 

    
    /***************************************
    * Function Prototypes
    ***************************************/    
    uint32_t `$INSTANCE_NAME`_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val);      /**< Write a value to a register*/
    uint32_t `$INSTANCE_NAME`_WriteCmd(uint8_t deviceAddr, uint8_t cmd);      /**< Write a command with no data */
    uint32_t `$INSTANCE_NAME`_WriteArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len);      /**< Write multiple arrays */
    uint32_t `$INSTANCE_NAME`_Read(uint8_t deviceAddr, uint8_t regAddr, uint8_t * readVal); /**< Read a value from a register */
    uint32_t `$INSTANCE_NAME`_ReadArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */
   
    
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */

