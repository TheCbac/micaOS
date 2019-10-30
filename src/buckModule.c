/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: buckModule.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* 
* PCB: buckModule v5.0.2
* mcuType: Generic
* partNumber:N/A
*
* Brief:
*   Controlling the MICA buck module
*
* 2019.10.28  - Document Created
********************************************************************************/
#include "buckModule.h"

/*******************************************************************************
* Function Name: buck_writeReg()
****************************************************************************//**
* \brief
*   Writes to a register on the Buck Module 
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param addr [in]
*   Address of the register
*
* \param val [in]
*   Value of the register 
*  
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t  buck_writeReg(BUCK_STATE_S* state, uint8_t addr, uint8_t val) {
  /* Ensure state exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    state->error = error;
    error = COMMS_ERROR_I2C;
  } else {
    uint32_t i2cError = state->i2c->write(state->deviceAddr, addr, val);
    /* Place output error in the state struct */
    error |= i2cError ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_readReg()
****************************************************************************//**
* \brief
*   Reads a register on the Buck Module 
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param addr [in]
*   Address of the register
*
* \param val [out]
*   Value of the register 
*  
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t  buck_readReg(BUCK_STATE_S* state, uint8_t addr, uint8_t *val){
    /* Ensure state exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    state->error = error;
    error = COMMS_ERROR_I2C;
  } else {
    uint32_t i2cError = state->i2c->read(state->deviceAddr, addr, val);
    /* Place output error in the state struct */
    error |= i2cError ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_writeArray()
****************************************************************************//**
* \brief
*   Reads a register on the Buck Module 
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param addr [in]
*   Address of the register
*
* \param val [in]
*   Pointer to the array of the register 
*
* \param len [in]
*   Number of elements to write
*  
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t  buck_writeArray(BUCK_STATE_S* state, uint8_t addr, uint8_t *val, uint8_t len){
  /* Ensure state exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    state->error = error;
    error = COMMS_ERROR_I2C;
  } else {
    uint32_t i2cError = state->i2c->writeArray(state->deviceAddr, addr, val, len);
    /* Place output error in the state struct */
    error |= i2cError ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;

}

/*******************************************************************************
* Function Name: buck_readArray()
****************************************************************************//**
* \brief
*   Reads a register on the Buck Module 
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param addr [in]
*   Address of the register
*
* \param val [out]
*   Pointer to the array of the register 
*
* \param len [in]
*   Number of elements to write
*  
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t  buck_readArray(BUCK_STATE_S* state, uint8_t addr, uint8_t *val, uint8_t len){
  /* Ensure state exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    state->error = error;
    error = COMMS_ERROR_I2C;
  } else {
    uint32_t i2cError = state->i2c->readArray(state->deviceAddr, addr, val, len);
    /* Place output error in the state struct */
    error |= i2cError ? COMMS_ERROR_READ_ARRAY : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_start()
****************************************************************************//**
* \brief
*   Checks for responsiveness from the device
*
* \param state [in/out]
*   Pointer to the state struct
*
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_start(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  /* Read ID value */
  uint8_t readVal = 0;
  error |= buck_readReg(state, BUCK_ADDR_ID, &readVal);
  if(!error) {
    if(readVal != BUCK_ID_VAL){
      error = COMMS_ERROR_START;
      state->error = readVal;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_setMode()
****************************************************************************//**
* \brief
*   Sets the device state
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param mode [in]
*   Next mode to go into
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setMode(BUCK_STATE_S* state, BUCK_MODE_T mode) {
  uint32_t error = COMMS_ERROR_NONE;
  error |= buck_writeReg(state, BUCK_ADDR_MODE, mode);
  if(!error) {
    state->mode = mode;
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_setDuty()
****************************************************************************//**
* \brief
*   Sets the device open loop duty cycle
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param mode [in]
*   Next mode to go into
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setDuty(BUCK_STATE_S* state, uint8_t duty) {
  uint32_t error = COMMS_ERROR_NONE;
  error |= buck_writeReg(state, BUCK_ADDR_DUTY, duty);
  if(!error) {
    state->duty = duty;
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_setDuty()
****************************************************************************//**
* \brief
*   Sets the device open loop duty cycle
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param mode [in]
*   Next mode to go into
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getDuty(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t duty;
  error |= buck_readReg(state, BUCK_ADDR_DUTY, &duty);
  if(!error) {
    state->duty = duty;
  }
  return error;
}


/*******************************************************************************
* Function Name: buck_setDuty()
****************************************************************************//**
* \brief
*   Sets the device open loop duty cycle
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param mode [in]
*   Next mode to go into
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getCurrent(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_MEASI, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->measI);
  }
  return error;
}


/* [] END OF FILE */
