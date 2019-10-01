/***************************************************************************
*                                 GardenByte  © 2019
*
* File: Arduino_i2c.h
* Workspace: ledDriver_TLC591
* Project: testScripts
* Version: v1.0.0
* Authors: C. Cheney
* 
* PCB: Mainboard v1.0.0
*
* Brief:
*   Wrapper class that provides a generic I2C interface for Arduino,
*   using the Wire library.
*
* 2019.04.22  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef ARDUINO_I2C_H
    #define ARDUINO_I2C_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include "micaComms.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define I2C_ARDUINO_LEN_ARRAY      (32) /**< Maximum length of an array in the Wire library */
    /***************************************
    * Enumerated Types
    ***************************************/

    
    /***************************************
    * Structures
    ***************************************/

    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t i2cArduino_start(COMMS_I2C_S *i2c);
    uint32_t i2cArduino_write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val);
    uint32_t i2cArduino_writeCmd(uint8_t deviceAddr, uint8_t cmd);
    uint32_t i2cArduino_writeArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len);
    uint32_t i2cArduino_read(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result);
    uint32_t i2cArduino_readArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */

#endif /* ARDUINO_I2C_H */
/* [] END OF FILE */
