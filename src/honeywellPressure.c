/***************************************************************************
*                              Majestic Labs  © 2020
*                               
*
* File: honeywellPressure.c
* Workspace: micaOS
* Project: micaOS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB:  
* mcuType: Generic 
* partNumber:HSCMRRN001PD2A3
*
* Brief:
*   Driver File for Honeywell Pressure sensors
*
* 2020.05.18  - Document Created
********************************************************************************/
#include "honeywellPressure.h"
#include "micaCommon.h"


/*******************************************************************************
* Function Name: honeywell_Start()
****************************************************************************//**
* \brief
*   Read a register over the TCA9535 I2C bus
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
uint32_t honeywell_Start(HONEYWELL_STATE_S *const state, COMMS_I2C_S *const i2c, uint8_t i2cAddr){
  uint32_t error = COMMS_ERROR_NONE;
  state->_deviceAddr = i2cAddr;
  state->_i2c = i2c;
  error |= Comms_validateI2C(state->_i2c);
  if(error) {
    error |= COMMS_ERROR_START; 
  }

  return error;
}

/*******************************************************************************
* Function Name: honeywell_readPressure
****************************************************************************//**
* \brief
*   Reads the Pressure data from the sensor
*
* \param state [in/out]
* Pointer to the state struct
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t honeywell_readPressure(HONEYWELL_STATE_S *const state){
  /* Ensure Comms exists */
  uint32_t error = Comms_validateI2C(state->_i2c);
  if(error){
    /* Store the comms error reported */
    state->error = error;
    error = COMMS_ERROR_I2C;
  /* Proceed with write */
  } else {
    uint8_t readArray[TWO];
    uint32_t i2cError = state->_i2c->readCmd(state->_deviceAddr, readArray, TWO);
    /* Write out */
    uint16_t MSDB = readArray[ZERO];
    uint16_t LSDB = readArray[ONE];
    state->pressure = (MSDB << SHIFT_BYTE_ONE) |  LSDB ;
    error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: honeywell_readPresTemp
****************************************************************************//**
* \brief
*   Reads the Pressure data and the one byte temp data
*
* \param state [in/out]
* Pointer to the state struct
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t honeywell_readPresTemp(HONEYWELL_STATE_S *const state){
  uint32_t error = Comms_validateI2C(state->_i2c);
  return error;

}

/*******************************************************************************
* Function Name: honeywell_readPresTempFull
****************************************************************************//**
* \brief
*   Reads the Pressure data and the two byte temperature
*
* \param state [in/out]
* Pointer to the state struct
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t honeywell_readPresTempFull(HONEYWELL_STATE_S *const state){
  uint32_t error = Comms_validateI2C(state->_i2c);
  return error;
}

/* [] END OF FILE */
