/***************************************************************************
*                              Majestic Labs  © 2020
*                               
*
* File: honeywellPressure.h
* Workspace: micaOS
* Project: micaOS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Header for honeywellPressure.c
*
* 2020.05.18  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef honeywellPressure_H
  #define honeywellPressure_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
  
  /***************************************
  * Macro Definitions
  ***************************************/
  #define HONEYWELL_ADDR      (0x28) /* Default device address  */
  
  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
    uint32_t error;         /**< Functions that exit with an error use this to transmit info out */
    int32_t temp;         /* Calculated temperature */
    int32_t pressure;     /* Calculated pressure */
    COMMS_I2C_S *_i2c;     /**< Pointer to the I2C comms struct */      
    uint8_t _deviceAddr;     /**< Address of the device to communicate with */
  } HONEYWELL_STATE_S;
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t honeywell_Start(HONEYWELL_STATE_S *const state, COMMS_I2C_S *const i2c, uint8_t i2cAddr);
  uint32_t honeywell_readPressure(HONEYWELL_STATE_S *const state);
  uint32_t honeywell_readPresTemp(HONEYWELL_STATE_S *const state);
  uint32_t honeywell_readPresTempFull(HONEYWELL_STATE_S *const state);



#endif /* honeywellPressure_H */
/* [] END OF FILE */
