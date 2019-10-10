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
#include "INA226.h"
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
    /* Place output error in the state struct */
    error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
    if (error) {
      state->error = i2cError;
    }
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
*  Pointer to the INA226 State structure
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
  /* Reset the device */
  if(!error){
    error |= INA226_reset(state);
  }
  /* Configuration register */
  if(!error) {
    uint16_t config = 0;
    /* AVG - 16 averages, continuous monitoring */
    config |= INA_CONFIG_AVG_16;
    /* VBUSTCT - 1.1 ms */
    config |= INA_CONFIG_VBUSCT_1100;
    /* VSHCT - 1.1 ms */
    config |= INA_CONFIG_VSHCT_1100;
    /* MODE - Shunt & Bus continuous */
    config |= INA_CONFIG_MODE_CONT_SH_BUS;
    /* RES - Add reserved bit back in  */
    config |= INA_CONFIG_MASK_RES1;
    /* Write out value */
    error |= INA226_writeReg(state, INA226_ADDR_CONFIG, config);
  }
  /* Calibartion register */
  if(!error){
    /* Calculate the Current LSB */
    state->_currentLsb = state->maxCurrent / INA_CURRENT_LSB_SCALE;
    /* Calculate the calibration constant */
    state->_calibration = INA_CAL_SCALE / (state->_currentLsb * state->rShunt);
    /* Write out the calibration register */
    error |= INA226_writeReg(state, INA226_ADDR_CALIBRATION, (uint16_t) state->_calibration );

  }
  return error;
}

/*******************************************************************************
* Function Name: INA226_readVoltage_Bus()
****************************************************************************//**
* \brief
*  Reads the bus voltage present
*
* \param [in/out] state
*  Pointer to the INA226 State structure
*
* \param val [out]
*  Voltage in units of Volts 
*
* \return
*  Error code of the procedure
*******************************************************************************/
uint32_t INA226_readVoltage_Bus(INA226_STATE_S* state, float* val){
  uint16_t regVal = 0;
  uint32_t error = INA226_readReg(state, INA226_ADDR_BUS, &regVal);
  /* Convert to Volts */
  if(!error){
    regVal &= INA_VBUS_MASK;
    *val = regVal * INA_VBUS_LSB;
  }
  return error;
}

/*******************************************************************************
* Function Name: INA226_readVoltage_Shunt()
****************************************************************************//**
* \brief
*  Reads the shunt voltage present
*
* \param [in/out] state
*  Pointer to the INA226 State structure
*
* \param val [out]
*  Voltage in units of Volts 
*
* \return
*  Error code of the procedure
*******************************************************************************/
uint32_t INA226_readVoltage_Shunt(INA226_STATE_S* state, float* val){
  uint16_t regVal = 0;
  float vShunt = 0;
  float sign = 1;
  uint32_t error = INA226_readReg(state, INA226_ADDR_SHUNT, &regVal);
  /* Convert to Volts */
  if(!error){
    /* Check if negative */
    if(regVal & INA_SIGN_BIT){
      sign = -1;
      /* Mask off the sign bit */
      regVal &= (~INA_SIGN_BIT);
      /* Convert from Two's complement to Binary */
      regVal -= 1;
      regVal = ~regVal;
    }
    /* Convert to Volts */
    vShunt = INA_VSHUNT_LSB * regVal;
    *val = sign * vShunt;
  }
  return error;
}


/*******************************************************************************
* Function Name: INA226_readCurrent()
****************************************************************************//**
* \brief
*  Reads the current register and converts to units of Amps
*
* \param [in/out] state
*  Pointer to the INA226 State structure
*
* \param val [out]
*  Current in units of A
*
* \return
*  Error code of the procedure
*******************************************************************************/
uint32_t INA226_readCurrent(INA226_STATE_S* state, float* val){
  uint16_t regVal = 0;
  uint32_t error = INA226_readReg(state, INA226_ADDR_CURRENT, &regVal);
  /* Convert to Amps */
  if(!error){
    *val = regVal * state->_currentLsb;
  }
  return error;
}

/*******************************************************************************
* Function Name: INA226_readPower()
****************************************************************************//**
* \brief
*  Reads the power register and converts to units of Wants
*
* \param [in/out] state
*  Pointer to the INA226 State structure
*
* \param val [out]
*  Power in units of [W]
*
* \return
*  Error code of the procedure
*******************************************************************************/
uint32_t INA226_readPower(INA226_STATE_S* state, float* val){
  uint16_t regVal = 0;
  uint32_t error = INA226_readReg(state, INA226_ADDR_POWER, &regVal);
  /* Convert to Amps */
  if(!error){
    *val = regVal * state->_currentLsb * INA_POWER_SCALE;
  }
  return error;
}

/* [] END OF FILE */
