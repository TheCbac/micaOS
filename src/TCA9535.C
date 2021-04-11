/***************************************************************************
*                              MICA  © 2020
*                               
*
* File: TCA9535.c
* Workspace: MICA OS
* Project: MICA OS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: N/A N/A
* mcuType: Generic
* partNumber:TCA9535
*
* Brief:
*   16 Bit I2C Port Expander
*
* 2020.04.29  - Document Created
* 2020.12.07    <sek> comments
* 2020.12.10    <sek> added _init structure member
********************************************************************************/
#include "TCA9535.h"
#include "micaCommon.h"

/***************************************
*           Structures
***************************************/

const TCA9535_STATE_S TCA9535_STATE_DEFAULT_S = 
{
    .i2c = NULL,
    .error = COMMS_ERROR_NONE,
    .deviceAddr = 0,
    ._init = false
};
  

// NOTE: all of these functions treat the TCA9535 8 bit register PAIRS as a single 16 bit WORD,
// so both ports are handled with a single operation.
// There are no functions to access a single 8 bit port.

/*******************************************************************************
* Function Name: TCA9535_writeReg()
****************************************************************************//**
* \brief
*   Write a register over the TCA9535 I2C bus
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
uint32_t TCA9535_writeReg(TCA9535_STATE_S* state, uint8_t regAddr, uint16_t val)
{
    if (state->_init)
    {
        /* Ensure Comms exists */
        uint32_t error = Comms_validateI2C(state->i2c);
        if(error)
        {
            /* Store the comms error reported */
            state->error = error;
            error = COMMS_ERROR_I2C;
        } 
        else 
        {
            /* Proceed with write */
            uint8_t msdb = (val >> SHIFT_BYTE_ONE);
            uint8_t lsdb = (val & MASK_BYTE_ONE);
            uint8_t sendArray[2] = {lsdb, msdb};
            uint32_t i2cError = state->i2c->writeArray(state->deviceAddr, regAddr, sendArray, 2);
            /* Place output error in the state struct */
            error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
            if (error) 
            {
              state->error = i2cError;              // specific I2C error
            }
        }
        return error;                               // general error
    }
    else
    {
        state->error = COMMS_ERROR_START;           // not initialized
        return state->error;
    }
}


/*******************************************************************************
* Function Name: TCA9535_readReg()
****************************************************************************//**
* \brief
*   Read a register over the TCA9535 I2C bus
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
static uint32_t TCA9535_readReg(TCA9535_STATE_S* state, uint8_t regAddr, uint16_t* val)
{
    if (state->_init)
    {
        /* Ensure Comms exists */
        uint32_t error = Comms_validateI2C(state->i2c);
        if(error)
        {
            /* Store the comms error reported */
            state->error = error;
            error = COMMS_ERROR_I2C;
        }
        else 
        {
            /* Proceed with read - Read array must be initialized to 0 */
            uint8_t readArray[TWO] = {0x00, 0x00};
            uint32_t i2cError = state->i2c->readArray(state->deviceAddr, regAddr, readArray, TWO);
            /* Write out */
            uint16_t LSDB = readArray[ZERO];
            uint16_t MSDB = readArray[ONE];
            *val = (MSDB << SHIFT_BYTE_ONE) |  LSDB ;
            error |= i2cError ? COMMS_ERROR_I2C : COMMS_ERROR_NONE;
            if (error) 
            {
                state->error = i2cError;        // specific I2C error
            }
      }
      return error;                             // general error
    }
    else
    {
        state->error = COMMS_ERROR_START;       // not initialized
        return state->error;
    }
}


/*******************************************************************************
* Function Name: TCA9535_start()
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
uint32_t TCA9535_start(TCA9535_STATE_S* state, COMMS_I2C_S* i2c, uint8_t i2cAddr)
{
    uint32_t error = COMMS_ERROR_NONE;
    state->deviceAddr = i2cAddr;
    state->i2c = i2c;
    error |= Comms_validateI2C(state->i2c);
    if(!error)
    {
        /* preemptively mark as initialized */
        state->_init = true;
        /* Test connectivity on Output Port 0 */
        uint16_t readData = 0x00;
        error |= TCA9535_writeReg(state, TCA9535_ADDR_OUTPUT, TCA9535_TEST_VAL);
        error |= TCA9535_readReg(state, TCA9535_ADDR_OUTPUT, &readData);
        /* Ensure read byte matches reset error */
        if(error || (readData != TCA9535_TEST_VAL))
        {
            state->error = readData;
            error |= COMMS_ERROR_START;
            /* Revert to uninitilized  */
            state->_init = false;
        } 
        else 
        {
            /* Success, reset to default state */
            error |= TCA9535_writeReg(state, TCA9535_ADDR_OUTPUT, TCA9535_OUTPUT_DEFAULT);
        }
    }
    else 
    {
        error |= COMMS_ERROR_START | COMMS_ERROR_I2C; 
    }

    return error;
}

/*******************************************************************************
* Function Name: TCA9535_setMode()
****************************************************************************//**
* \brief
*   Set the configuration port register for I/O state
*
* \param state [in/out]
* Pointer to the state struct
*
* \param mode [in]
*   Configuration register value
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t TCA9535_setMode(TCA9535_STATE_S * state, uint16_t mode){
  return TCA9535_writeReg(state, TCA9535_ADDR_CONFIG, mode);
}

/*******************************************************************************
* Function Name: TCA9535_setPolarity()
****************************************************************************//**
* \brief
*   Set the polarity of the Ports
*
* \param state [in/out]
* Pointer to the state struct
*
* \param polarity [in]
*   Configuration register value
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t TCA9535_setPolarity(TCA9535_STATE_S * state, uint16_t polarity){
  return TCA9535_writeReg(state, TCA9535_ADDR_INVERT, polarity);

}


/*******************************************************************************
* Function Name: TCA9535_write()
****************************************************************************//**
* \brief
*   Write to output port of the device
*
* \param state [in/out]
* Pointer to the state struct
*
* \param val [in]
*   Value to write
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t TCA9535_write(TCA9535_STATE_S * state, uint16_t val){
  return TCA9535_writeReg(state, TCA9535_ADDR_OUTPUT, val);
}


/*******************************************************************************
* Function Name: TCA9535_read()
****************************************************************************//**
* \brief
*   Read from in the input port of the device
*
* \param state [in/out]
* Pointer to the state struct
*
* \param val [out]
*   Pointer to result of the read operation
*  
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t TCA9535_read(TCA9535_STATE_S * state, uint16_t * val){
  return TCA9535_readReg(state, TCA9535_ADDR_INPUT, val);
}

/* [] END OF FILE */
