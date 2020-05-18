/***************************************************************************
*                              Majestic Labs  © 2020
*                               
*
* File: MS5607.c
* Workspace: micaOS
* Project: Drivers
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: N/A
* mcuType: Generic 
* partNumber:MS560702BA03-50
*
* Brief:
*   Driver file for the MS5607 Pressure Sensor
*
* 2020.05.12  - Document Created
********************************************************************************/
#include "MS5607.h"
#include "micaCommon.h"

/*******************************************************************************
* Function Name: MS5607_start()
****************************************************************************//**
* \brief
*   Starts the MS5607 Pressure sensor. 
*
* \param state [in/out]
* Pointer to the state struct
*
* \param i2c [in]
* Pointer to the i2c comms struct
*
* \param i2cAddr [in]
* Value of the device I2C Address
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t MS5607_start(MS5607_STATE_S *const state, COMMS_I2C_S *const i2c, uint8_t i2cAddr){
  /* Validate and assign */
  uint32_t error = COMMS_ERROR_NONE;
  state->_deviceAddr = i2cAddr;
  state->_i2c = i2c;
  error |= Comms_validateI2C(state->_i2c);
  if(!error) {
    /* Reset device */
    error |= MS5607_reset(state);
    
    /* Ensure read byte matches reset error */
    /* read the PROM */
    // error |= MS5607_read_ROM(state);
  }
  else {
    error |= COMMS_ERROR_START; 
  }

  return error;
}

/*******************************************************************************
* Function Name: MS5607_reset
****************************************************************************//**
* \brief
*   Send the Reset command to the Pressure sensor 
*
* \param state [in/out]
* Pointer to the state struct
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t MS5607_reset(MS5607_STATE_S *const state) {
  return MS5607_writeCmd(state, MS5607_CMD_RESET);
}

/*******************************************************************************
* Function Name: MS5607_read_ROM
****************************************************************************//**
* \brief
*   Reads all 6 parameters from the ROM 
*
* \param state [in/out]
* Pointer to the state struct
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t MS5607_read_ROM(MS5607_STATE_S *const state){
  /* Clear existing */
  uint8_t idx;
  for(idx = ZERO; idx < MS5607_COEFFS_LEN; idx++) {
    state->_coeffs[idx]=ZERO;
  }
  /* Ensure Comms exists */ 
  uint32_t error = Comms_validateI2C(state->_i2c);
  if(error){
    /* Store the comms error reported */
    state->error = error;
    error = COMMS_ERROR_I2C;
  /* Proceed with write */
  } else {
    /* Read each Coefficient */
    uint8_t C;
    for(C=ZERO; C < MS5607_COEFFS_LEN; C++) {
      uint8_t readArray[TWO];
      uint8_t cAddr = MS5607_ADDR_PROM + (C * TWO);
      uint32_t i2cError = state->_i2c->readArray(state->_deviceAddr, cAddr, readArray, TWO);

      /* Error check */
      error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
      if (!error) {
        uint16_t MSDB = readArray[ZERO];
        uint16_t LSDB = readArray[ONE];
        state->_coeffs[C] = (MSDB << SHIFT_BYTE_ONE) |  LSDB;
      } else {
        state->error = i2cError;
        break;
      }
    }
  }
  return error;
}


/*******************************************************************************
* Function Name: MS5607_writeCmd
****************************************************************************//**
* \brief
*   Write a register over the MS5607 I2C bus
*
* \param state [in/out]
* Pointer to the state struct
*
* \param cmd [in]
*   Address of the register to write to
*
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t MS5607_writeCmd(MS5607_STATE_S *const state, uint8_t cmd){
  /* Ensure Comms exists */
  uint32_t error = Comms_validateI2C(state->_i2c);
  if(error){
    /* Store the comms error reported */
    state->error = error;
    error = COMMS_ERROR_I2C;
  /* Proceed with write */
  } 
  else {
    uint32_t i2cError = state->_i2c->writeCmd(state->_deviceAddr, cmd);
    /* Place output error in the state struct */
    error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;
}

/* [] END OF FILE */
