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
* Function Name: buck_writeCmd()
****************************************************************************//**
* \brief
*   Writes to a command (single byte) to the Buck Module 
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param cmd [in]
*   Address of the register
*  
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_writeCmd(BUCK_STATE_S* state, uint8_t cmd) {
  /* Ensure state exists */
  uint32_t error = Comms_validateI2C(state->i2c);
  if(error){
    state->error = error;
    error = COMMS_ERROR_I2C;
  } else {
    uint32_t i2cError = state->i2c->writeCmd(state->deviceAddr, cmd);
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
  /* Reset the device */
  error |= buck_reset(state);
  /* Wait for reset */
  state->timing->delayMs(10);
  if(!error) {
      /* Read ID value */
      uint8_t readVal = 0;
      error |= buck_readReg(state, BUCK_ADDR_ID, &readVal);
      if(!error) {
        if(readVal != BUCK_ID_VAL){
          error = COMMS_ERROR_START;
          state->error = readVal;
        }
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
* Function Name: buck_getMode()
****************************************************************************//**
* \brief
*   Gets the device state
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getMode(BUCK_STATE_S* state){
  uint32_t error = COMMS_ERROR_NONE;
    uint8_t mode;
  error |= buck_readReg(state, BUCK_ADDR_MODE, &mode);
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
* Function Name: buck_setRefV()
****************************************************************************//**
* \brief
*   Sets the reference voltage
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param refV [in]
*   Reference in Volts
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setRefV(BUCK_STATE_S* state, float refV) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  float2Byte(refV, fBytes);
  error |= buck_writeArray(state, BUCK_ADDR_VREF, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    state->refV = refV;
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_setRefI()
****************************************************************************//**
* \brief
*   Sets the reference current
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param refV [in]
*   Reference in Volts
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setRefI(BUCK_STATE_S* state, float refI) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  float2Byte(refI, fBytes);
  error |= buck_writeArray(state, BUCK_ADDR_IREF, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    state->refI = refI;
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getDuty()
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
* Function Name: buck_getRefV()
****************************************************************************//**
* \brief
*   Gets the reference voltage
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param refV [in]
*   Reference in Volts
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getRefV(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_VREF, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->refV);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getRefI()
****************************************************************************//**
* \brief
*   Gets the reference current
*
* \param state [in/out]
*   Pointer to the state struct
*
* \param refV [in]
*   Reference in Volts
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getRefI(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_IREF, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->refI);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getSense()
****************************************************************************//**
* \brief
*   Get the voltage, current and power in a single call
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getSense(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[3*BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_SENSE, fBytes, 3*BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->measV);
    byte2Float(&fBytes[4], &state->measI);
    byte2Float(&fBytes[8], &state->measP);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getCurrent()
****************************************************************************//**
* \brief
*   Get the current measured by the device
*
* \param state [in/out]
*   Pointer to the state struct
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

/*******************************************************************************
* Function Name: buck_getVoltage()
****************************************************************************//**
* \brief
*   Get the current measured by the device
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getVoltage(BUCK_STATE_S* state){
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_MEASV, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->measV);
  }
  return error;
}



/*******************************************************************************
* Function Name: buck_setMaxV()
****************************************************************************//**
* \brief
*   Set the voltage limit
*
* \param maxV [in]
* Voltage limit [V]
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setMaxV(BUCK_STATE_S* state, float maxV) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  float2Byte(maxV, fBytes);
  error |= buck_writeArray(state, BUCK_ADDR_MAXV, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    state->maxV= maxV;
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_setMaxI()
****************************************************************************//**
* \brief
*   Set the Current limit
*
* \param maxI [in]
* Current limit [A]
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setMaxI(BUCK_STATE_S* state, float maxI) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  float2Byte(maxI, fBytes);
  error |= buck_writeArray(state, BUCK_ADDR_MAXI, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    state->maxI= maxI;
  }
  return error;
}


/*******************************************************************************
* Function Name: buck_setMaxP()
****************************************************************************//**
* \brief
*   Set the Power limit
*
* \param maxP [in]
* Power limit [W]
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_setMaxP(BUCK_STATE_S* state, float maxP) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  float2Byte(maxP, fBytes);
  error |= buck_writeArray(state, BUCK_ADDR_MAXP, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    state->maxP= maxP;
  }
  return error;
}


/*******************************************************************************
* Function Name: buck_getMaxV()
****************************************************************************//**
* \brief
*   Get the Voltage max on the device
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getMaxV(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_MAXV, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->maxV);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getMaxI()
****************************************************************************//**
* \brief
*   Get the Current max on the device
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getMaxI(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_MAXI, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->maxI);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getMaxV()
****************************************************************************//**
* \brief
*   Get the power max on the device
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getMaxP(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t fBytes[BYTES_PER_FLOAT];
  error |= buck_readArray(state, BUCK_ADDR_MAXP, fBytes, BYTES_PER_FLOAT);
  if(!error) {
    byte2Float(fBytes, &state->maxP);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_getError()
****************************************************************************//**
* \brief
*   Get the Error on the device
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_getError(BUCK_STATE_S* state) {
  uint32_t error = COMMS_ERROR_NONE;
  uint8_t bytes[BYTES_PER_UINT32];
  error |= buck_readArray(state, BUCK_ADDR_ERROR, bytes, BYTES_PER_UINT32);
  if(!error) {
    ByteToUint32(bytes, &state->error);
  }
  return error;
}

/*******************************************************************************
* Function Name: buck_reset()
****************************************************************************//**
* \brief
*   Initiate a software reset
*
* \param state [in/out]
*   Pointer to the state struct
* 
* \return
*   Error code of the operation
*******************************************************************************/
uint32_t buck_reset(BUCK_STATE_S* state){
  uint32_t error = COMMS_ERROR_NONE;
  error = buck_writeCmd(state, BUCK_ADDR_RESET);
  return error;
}

/* [] END OF FILE */
