/***************************************************************************
*                                       MICA
* File: I2C_API.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for the MICA I2C API
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.14 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"    
    
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_ERR_OK         (0u) /**< Operation succedded */
    #define `$INSTANCE_NAME`_ERR_READ       (1u) /**< An error occured during the read */
    
    #define `$INSTANCE_NAME`_MASK_READ_ERR  (0x80000000) /**< Mask for determining if an error occured during the read operation. MSB of uint32 */
    /***************************************
    * Function Prototypes
    ***************************************/
    /* Leave these to the base component for now */
//    uint32 `$INSTANCE_NAME`_Start(void);    /**< Start the I2C Component*/
//    uint32 `$INSTANCE_NAME`_Stop(void);     /**< Stop the I2C Componen*/
//    uint32 `$INSTANCE_NAME`_Sleep(void);    /**< Put the I2C component to sleep*/
//    uint32 `$INSTANCE_NAME`_Wakeup(void);   /**< Wake up the I2C component*/
    
    uint32 `$INSTANCE_NAME`_Write(uint8 deviceAddr, uint8 regAddr, uint8 val);      /**< Write a value to a register*/
    uint32 `$INSTANCE_NAME`_Read(uint8 deviceAddr, uint8 regAddr, uint8 * readVal); /**< Read a value from a register */

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */

