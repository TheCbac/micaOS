/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: ina226.c
* Workspace: micaOS
* Project: micaOS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: N/A N/A
* mcuType: Generic
* partNumber:INA226
*
* Brief:
*   Driver from INA226 Power monitor
*
* 2019.10.03  - Document Created
********************************************************************************/
#include "ina226.h"
#include "micaCommon.h"

/*******************************************************************************
* Function Name: INA226_writeReg()
****************************************************************************//**
* \brief
*   Write a register over the INA226 I2C bus
*
* \param state [in/out]
* Pointer to the state struct
*
* \param regAddr [in]
*   Address of the register to write to
*
* \param val [in]
*   value to write to the register
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t INA226_writeReg(INA226_STATE_S* state, uint8_t regAddr, uint16_t val){
  /* Ensure Comms exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    /* Store the comms error reported */
    state->error = error;
    error = COMMS_ERROR_I2C;
  /* Proceed with write */
  } 
  else {
    uint8_t msdb = (val >> SHIFT_BYTE_ONE);
    uint8_t lsdb = (val & MASK_BYTE_ONE);
    uint8_t sendArray[2] = {msdb, lsdb};
    uint32_t i2cError = state->i2c->writeArray(state->deviceAddr, regAddr, sendArray, 2);
    // /* Place output error in the state struct */
    // error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
    // if (error) {
    //   state->error = i2cError;
    // }
  }
  return error;
}

/*******************************************************************************
* Function Name: INA226_readReg()
****************************************************************************//**
* \brief
*   Read a register over the INA226 I2C bus
*
* \param state [in/out]
* Pointer to the state struct
*
* \param regAddr [in]
*   Address of the register to write to
*
* \param val [out]
*   Pointer where to place the result
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t INA226_readReg(INA226_STATE_S* state, uint8_t regAddr, uint16_t* val){
  /* Ensure Comms exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    /* Store the comms error reported */
    state->error = error;
    error = COMMS_ERROR_I2C;
  /* Proceed with write */
  } else {
    uint8_t readArray[TWO];
    uint32_t i2cError = state->i2c->readArray(state->deviceAddr, regAddr, readArray, TWO);
    /* Write out */
    uint16_t MSDB = readArray[ZERO];
    uint16_t LSDB = readArray[ONE];
    *val = (MSDB << SHIFT_BYTE_ONE) |  LSDB ;
    error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: INA226_reset()
****************************************************************************//**
* \brief
*   Initiates a software reset
*
* \param state [in/out]
* Pointer to the state struct
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t INA226_reset(INA226_STATE_S* state) {
  return INA226_writeReg(state, INA226_ADDR_CONFIG, INA_CONFIG_MASK_RST);
}

/*******************************************************************************
* Function Name: INA226_start()
****************************************************************************//**
* \brief
*  Enables operation of the device and checks for connectivity
*
* \param [in/out] state
*  Pointer to the DAC5578 State structure
*
* \return
*  Error code of the procedure
*******************************************************************************/
uint32_t INA226_start(INA226_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  /* Read ID value */
  uint16_t readVal = 0;
  error |= INA226_readReg(state, INA226_ADDR_ID_MFG, &readVal);
  if(!error) {
    if(readVal != INA_ID_MFG_VAL){
      error = COMMS_ERROR_START;
      state->error = readVal;
    }
  }


  // if(!error){
  //   /* Reset the device */
  //   error |= INA226_reset(state);
  // }
  // }
  // /* Configure device */
  // if(!error) {
  //   /* 16 averages, continuous monitoring */
  //   uint16_t config = INA_CONFIG_AVG_16 | INA_CONFIG_MODE_CONT_SH_BUS;
  //   error |= INA226_writeReg(state, INA226_ADDR_CONFIG, config);

  // }
  return error;
}

/* [] END OF FILE */
