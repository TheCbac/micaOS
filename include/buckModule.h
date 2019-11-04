/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: buckModule.h
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* PCB: buckModule 5.0.2
* PSoC: 
*
* Brief:
*   Header for buckModule_v5.c
*
* 2019.10.28  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef BUCK_MODULE_H
  #define BUCK_MODULE_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
  #include "micaTiming.h"
  /***************************************
  * Macro Definitions
  ***************************************/

  #define BUCK_ADDR_MODE              (0x00)  /* Mode of the device */
  #define BUCK_ADDR_DUTY              (0x01)  /* Open loop duty cycle */
  #define BUCK_ADDR_VREF              (0x02)  /* Target Voltage for voltage control */
  #define BUCK_ADDR_IREF              (0x03)  /* Current Reference*/
  #define BUCK_ADDR_MAXV              (0x04)  /* Max Voltage allowed by the device  */
  #define BUCK_ADDR_MAXI              (0x05)  /* Max current allowed by the device*/
  #define BUCK_ADDR_MAXP              (0x06)  /* Max power allowed by the device*/
  #define BUCK_ADDR_MEASV             (0x07)  /* Measured output voltage*/
  #define BUCK_ADDR_MEASI             (0x08)  /* Measured output current*/
  #define BUCK_ADDR_MEASP             (0x09)  /* measured output power*/
  #define BUCK_ADDR_SENSE             (0x0A)  /* Returns voltage, current and power in single call */
  #define BUCK_ADDR_ID                (0xFD)  /* Device ID Register */
  #define BUCK_ADDR_FIRM              (0xFE)  /* Device ID Register */
  #define BUCK_ADDR_RESET             (0xFF)  /* Software reset*/
  
  #define BUCK_ID_VAL                 (0xCB)  /* Device ID Value */
  #define BUCK_MODE_VAL               (0x00) /* Default MODE */
    
  /***************************************
  * Enumerated Types
  ***************************************/
  typedef enum {
    BUCK_MODE_OFF = 0x00,           /* Disabled */
    BUCK_MODE_VOLTAGE,      /* Constant Voltage */
    BUCK_MODE_CURRENT,      /* Constant Current */
    BUCK_MODE_DUTY          /* Open loop duty cycle */
  } BUCK_MODE_T;
  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
    COMMS_I2C_S *i2c;
    uint8_t deviceAddr;
    BUCK_MODE_T mode;
    uint8_t duty;            /* Open loop reference  */
    float refV;              /* Target control point of voltage control */
    float refI;              /* Target control point of current control */
    
    float maxV;             /* Maximum voltage */
    float maxI;             /* Max current */
    float maxP;             /* Max Power */
    float measV;            /* Measure Voltage */
    float measI;            /* Measured Current */
    float measP;            /* Measured Power */
    uint32_t error;
    TIMING_S* timing;        /* Time structure for delays */
  } BUCK_STATE_S;
    
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t buck_writeReg(BUCK_STATE_S* state, uint8_t addr, uint8_t val);
  uint32_t buck_writeCmd(BUCK_STATE_S* state, uint8_t cmd);
  uint32_t buck_readReg(BUCK_STATE_S* state, uint8_t addr, uint8_t *val);
  uint32_t buck_writeArray(BUCK_STATE_S* state, uint8_t addr, uint8_t *val, uint8_t len);
  uint32_t buck_readArray(BUCK_STATE_S* state, uint8_t addr, uint8_t *val, uint8_t len);

  uint32_t buck_start(BUCK_STATE_S* state);
  uint32_t buck_setMode(BUCK_STATE_S* state, BUCK_MODE_T mode);
  uint32_t buck_getMode(BUCK_STATE_S* state);

  uint32_t buck_setDuty(BUCK_STATE_S* state, uint8_t duty);
  uint32_t buck_setRefV(BUCK_STATE_S* state, float refV);
  uint32_t buck_setRefI(BUCK_STATE_S* state, float refI);

  uint32_t buck_getDuty(BUCK_STATE_S* state);
  uint32_t buck_getRefV(BUCK_STATE_S* state);
  uint32_t buck_getRefI(BUCK_STATE_S* state);


  uint32_t buck_getSense(BUCK_STATE_S* state);
  uint32_t buck_getCurrent(BUCK_STATE_S* state);
  uint32_t buck_getVoltage(BUCK_STATE_S* state);

  uint32_t buck_reset(BUCK_STATE_S* state);

  #define buck_disable(state) buck_setMode(state, BUCK_MODE_OFF)


    
#endif /* BUCK_MODULE_H */
/* [] END OF FILE */
