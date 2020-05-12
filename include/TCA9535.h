/***************************************************************************
*                              MICA  © 2020
*                               
*
* File: TCA9535.h
* Workspace: MICA OS
* Project: MICA OS
* Version: 1.0.0
* Authors: C. Cheney
*
* Brief:
*   Header for TCA9535.c
*
* 2020.04.29  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef TCA9535_H
  #define TCA9535_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
  /***************************************
  * Macro Definitions
  ***************************************/
  
  #define TCA9535_ADDR_INPUT        (0x00) /**< Address of the Input Port */
  #define TCA9535_ADDR_OUTPUT       (0x02) /**< Address of the OUTPUT Port */
  #define TCA9535_ADDR_INVERT       (0x04) /**< Address of the Polarity Inversion Port */
  #define TCA9535_ADDR_CONFIG       (0x06) /**< Address of the CONFIG Port */

  #define TCA9535_INVERT_PORT       (0xFFFF) /* Invert the polarity of a port */
  #define TCA9535_CONFIG_INPUT      (0xFFFF) /* Set a port to be an input */
  #define TCA9535_CONFIG_OUTPUT     (0x0000) /* Set a port to be an Output */
  #define TCA9535_OUTPUT_DEFAULT    (0xFFFF) /* Default output value */
  #define TCA9535_TEST_VAL          (0xAAAA) /* Test value for connectivity */

  #define TCA9535_MODE_OUTPUT       (0x0000) /* Set both ports for output */
  #define TCA9535_MODE_INPUT        (0xFFFF) /* Set both ports for input */

  #define TCA9535_ACTIVE_HIGH       (0x0000)   /* All ports active high */
  #define TCA9535_ACTIVE_LOW        (0xFFFF)   /* All ports active low */
  
  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
    COMMS_I2C_S *i2c;     /**< Pointer to the I2C comms struct */      
    uint32_t error;         /**< Functions that exit with an error use this to transmit info out */
    uint8_t deviceAddr;     /**< Address of the device to communicate with */
  } TCA9535_STATE_S;
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t TCA9535_writeReg(TCA9535_STATE_S* state, uint8_t regAddr, uint16_t val);
  uint32_t TCA9535_readReg(TCA9535_STATE_S* state, uint8_t regAddr, uint16_t* val);
  uint32_t TCA9535_start(TCA9535_STATE_S* state, COMMS_I2C_S* i2c, uint8_t i2cAddr);
  uint32_t TCA9535_setMode(TCA9535_STATE_S * state, uint16_t mode);
  uint32_t TCA9535_setPolarity(TCA9535_STATE_S * state, uint16_t polarity);
  uint32_t TCA9535_write(TCA9535_STATE_S * state, uint16_t val);
  uint32_t TCA9535_read(TCA9535_STATE_S * state, uint16_t * val);




#endif /* TCA9535_H */
/* [] END OF FILE */
