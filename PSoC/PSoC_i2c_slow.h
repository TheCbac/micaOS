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
#ifndef I2C_PSOC_SLOW_H
    #define I2C_PSOC_SLOW_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include "micaComms.h"
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
    uint32_t i2cPsocSlow_start(COMMS_I2C_S *i2c);
    uint32_t i2cPsocSlow_write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val);
    uint32_t i2cPsocSlow_writeCmd(uint8_t deviceAddr, uint8_t cmd);
    uint32_t i2cPsocSlow_writeArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len);
    uint32_t i2cPsocSlow_read(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result);
    uint32_t i2cPsocSlow_readArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */

#endif /* I2C_PSOC_SLOW_H */
/* [] END OF FILE */
