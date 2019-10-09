/***************************************************************************
*                                 MICA  © 2019
*
* File: PSoC_i2c.h
* Workspace: micaOS
* Version: v2.0.0
* Authors: C. Cheney
*
* Brief:
*   Wrapper class that provides a generic I2C interface for PSoC
*
* 2019.10.08  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef PSOC_I2C_H
    #define PSOC_I2C_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include "micaComms.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    
    #define I2C_PSOC_MASK_READ_ERR  (0x80000000) /**< Mask for determining if an error occured during the read operation. MSB of uint32_t */
    
    #define I2C_PSOC_TIMEOUT_WRITE        (MICA_DELAY_MS_SEC_QUARTER) /* Delay for writting time out */
    #define I2C_PSOC_TIMEOUT_READ        (MICA_DELAY_MS_SEC_QUARTER) /* Delay for reading time out */
    /***************************************
    * Enumerated Types
    ***************************************/

    
    /***************************************
    * Structures
    ***************************************/

    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t i2cPsoc_start(COMMS_I2C_S *i2c);
    uint32_t i2cPsoc_write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val);
    uint32_t i2cPsoc_writeCmd(uint8_t deviceAddr, uint8_t cmd);
    uint32_t i2cPsoc_writeArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len);
    uint32_t i2cPsoc_read(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result);
    uint32_t i2cPsoc_readArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */

#endif /* PSOC_I2C_H */
/* [] END OF FILE */
