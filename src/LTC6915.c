/***************************************************************************
*                                       MICA
* File: LTC6915.c
* Workspace: micaOS
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Driver file for the LTC6915 Instrumentation amplifier
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2020.06.19 CC - Document created
********************************************************************************/
#include "LTC6915.h" 

const LTC6915_S LTC6915_DEFAULT_S = {
  ._init = false,
  .fn_pin_D0_Write = NULL,
  .fn_pin_D1_Write = NULL,
  .fn_pin_D2_Write = NULL,
  .fn_pin_D3_Write = NULL,
  ._gain = LTC6915_GAIN_0,
};


/*******************************************************************************
* Function Name: ltc6915_startSerial()
****************************************************************************//**
* \brief
*   Starts the LTC6915 Instrumentation amp in serial mode 
*   **** NOT IMPLEMENTED *******
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t ltc6915_startSerial(LTC6915_S *const ltc) {
  ltc->_init = false;
  return LTC6915_ERROR_INIT; 
}

/*******************************************************************************
* Function Name: ltc6915_startParallel()
****************************************************************************//**
* \brief
*   Starts the LTC6915 Instrumentation amp in  parallel mode. 
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t ltc6915_startParallel(LTC6915_S *const ltc){
  uint32_t error = LTC6915_ERROR_NONE;

  error |= ltc->fn_pin_D0_Write == NULL ? LTC6915_ERROR_PARALLEL : LTC6915_ERROR_NONE;
  error |= ltc->fn_pin_D1_Write == NULL ? LTC6915_ERROR_PARALLEL : LTC6915_ERROR_NONE;
  error |= ltc->fn_pin_D2_Write == NULL ? LTC6915_ERROR_PARALLEL : LTC6915_ERROR_NONE;
  error |= ltc->fn_pin_D3_Write == NULL ? LTC6915_ERROR_PARALLEL : LTC6915_ERROR_NONE;
  if(!error) {
    ltc->_init = true;
    ltc->_mode = LTC6915_MODE_PARALLEL;
  }

  return error; 
}


/*******************************************************************************
* Function Name: ltc6915_setGain()
****************************************************************************//**
* \brief
*   Sets the gain of the device
*
* \param state [in/out]
* Pointer to the state struct
*
* \param gain [in]
*   Value of the desired gain
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t ltc6915_setGain(LTC6915_S *const ltc, LTC6915_GAIN_T gain){
  uint32_t error = LTC6915_ERROR_NONE;

  if(ltc->_init){
    if(ltc->_mode == LTC6915_MODE_SERIAL){
      /* TODO: implement serial comms */
      error = LTC6915_ERROR_SERIAL;
    } 
    /* Update in parallel mode */
    else if (ltc->_mode == LTC6915_MODE_PARALLEL){
      ltc->_gain=gain;
      ltc->fn_pin_D0_Write(gain & LTC6915_MASK_D0);
      ltc->fn_pin_D1_Write(gain & LTC6915_MASK_D1);
      ltc->fn_pin_D2_Write(gain & LTC6915_MASK_D2);
      ltc->fn_pin_D3_Write(gain & LTC6915_MASK_D3);
    }
  } else {
    error = LTC6915_ERROR_INIT;
  } 

  return error; 
}

/*******************************************************************************
* Function Name: ltc6915_mapGainWord()
****************************************************************************//**
* \brief
*   Helper function to map the gainWord to gain value
*
* \param gainWord [in]
*   Input gain word
*
* \param result [out]
*   Numeric gain value
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t ltc6915_mapGainWord(LTC6915_GAIN_T gainWord, uint16_t *const result) {
  uint32_t error = LTC6915_ERROR_NONE;

  uint16_t val = 0;
  if(gainWord == LTC6915_GAIN_0){
    val = 0;
  }
  else if (gainWord <= LTC6915_GAIN_4096 ) {
    val = 1 << (gainWord - 1);
  } else {
    val = 0;
    error = LTC6915_ERROR_RANGE;
  }
  // switch (gainWord) {
  //   case LTC6915_GAIN_0: {
  //     val = 0;
  //     break;
  //   }
  //   case LTC6915_GAIN_1: {
  //     val = 1;
  //     break;
  //   }
  //   case LTC6915_GAIN_2: {
  //     val = 2;
  //     break;
  //   }
  //   case LTC6915_GAIN_4: {
  //     val = 4;
  //     break;
  //   }
  //   case LTC6915_GAIN_8: {
  //     val = 8;
  //     break;
  //   }
  //   case LTC6915_GAIN_16: {
  //     val = 16;
  //     break;
  //   }
  //   case LTC6915_GAIN_32: {
  //     val = 32;
  //     break;
  //   }
  //   case LTC6915_GAIN_64: {
  //     val = 64;
  //     break;
  //   }
  //   case LTC6915_GAIN_128: {
  //     val = 128;
  //     break;
  //   }
  //   case LTC6915_GAIN_256: {
  //     val = 256;
  //     break;
  //   }
  //   case LTC6915_GAIN_512: {
  //     val = 512;
  //     break;
  //   }
  //   case LTC6915_GAIN_1024: {
  //     val = 1024;
  //     break;
  //   }
  //   case LTC6915_GAIN_2048: {
  //     val = 2048;
  //     break;
  //   }
  //   case LTC6915_GAIN_4096: {
  //     val = 4096;
  //     break;
  //   }
  //   default: {
  //     val = 0;
  //     error = LTC6915_ERROR_RANGE;
  //     break;
  //   }
  // }
  /* Update output */
  *result = val;
  return error;
}



/* [] END OF FILE */