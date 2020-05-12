/***************************************************************************
*                              MICA  © 2020
*                               
*
* File: SevenSegDual.c
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
*   2 Digit 7 Segment display, driven by the TCA9535 Port Expander
*
* 2020.04.29  - Document Created
********************************************************************************/
#include "SevenSegDual.h"
#include "micaCommon.h"

/* Character mapping array - Digits  */
const uint8_t SevenSeg_digArray[10] = {
  SEVENSEG_CHAR_0,
  SEVENSEG_CHAR_1,
  SEVENSEG_CHAR_2,
  SEVENSEG_CHAR_3,
  SEVENSEG_CHAR_4,
  SEVENSEG_CHAR_5,
  SEVENSEG_CHAR_6,
  SEVENSEG_CHAR_7,
  SEVENSEG_CHAR_8,
  SEVENSEG_CHAR_9
};
/* Character mapping array - Characters  */
const uint8_t SevenSeg_charArray[26] = {
  SEVENSEG_CHAR_A,
  SEVENSEG_CHAR_B,
  SEVENSEG_CHAR_C,
  SEVENSEG_CHAR_D,
  SEVENSEG_CHAR_E,
  SEVENSEG_CHAR_F,
  SEVENSEG_CHAR_G,
  SEVENSEG_CHAR_H,
  SEVENSEG_CHAR_I,
  SEVENSEG_CHAR_J,
  SEVENSEG_CHAR_K,
  SEVENSEG_CHAR_L,
  SEVENSEG_CHAR_M,
  SEVENSEG_CHAR_N,
  SEVENSEG_CHAR_O,
  SEVENSEG_CHAR_P,
  SEVENSEG_CHAR_K,
  SEVENSEG_CHAR_R,
  SEVENSEG_CHAR_S,
  SEVENSEG_CHAR_T,
  SEVENSEG_CHAR_U,
  SEVENSEG_CHAR_V,
  SEVENSEG_CHAR_W,
  SEVENSEG_CHAR_X,
  SEVENSEG_CHAR_Y,
  SEVENSEG_CHAR_Z,
};

/*******************************************************************************
* Function Name: SEVENSEG_start()
****************************************************************************//**
* \brief Starts the Display and Blanks the displays
*  
* \param state Pointer to the state struct for the Seven Segment 
*
* \param addr Address of the TCA Port expander I2C Device
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t SEVENSEG_start(SEVENSEG_STATE_S* state, COMMS_I2C_S *i2c, uint8_t addr){
  uint32_t error = SEVENSEG_ERROR_NONE; 

  /* Start the TCA port expander */
  state->_tca.deviceAddr = addr;
  state->_tca.i2c = i2c;
  error |= TCA9535_start(&state->_tca, i2c, addr);
  /* On success */
  if(!error) {
    /* configure as Output */
    error |= TCA9535_setMode(&state->_tca, TCA9535_MODE_OUTPUT);
    /* Display Blank */
    state->_char0 = SEVENSEG_CHAR_BLANK | SEVENSEG_CHAR_DOT;
    state->_char1 = SEVENSEG_CHAR_BLANK;
    error |= SEVENSEG_update(state);

  } else {
    state->error = error;
    error = SEVENSEG_ERROR_TCA;
  }
  return error;
}

/*******************************************************************************
* Function Name: SEVENSEG_update()
****************************************************************************//**
* \brief Updates the TCA port expander with the values stored in the state struct
*  
* \param state Pointer to the state struct for the Seven Segment 
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t SEVENSEG_update(SEVENSEG_STATE_S* state){
  uint16_t ctrl = (state->_char1 << SHIFT_BYTE_ONE) | state->_char0;
  return TCA9535_write(&state->_tca, ctrl);
}

/*******************************************************************************
* Function Name: SEVENSEG_mapChar()
****************************************************************************//**
* \brief Maps an ascii character (A-Z, 0-9, '-', '.') to a 7 Seg display value
*  
* \param val [in] 
*   Value to convert to 7Seg
*
* \param display [out]
*   Encoded 7-Seg digit
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t SEVENSEG_mapChar(uint8_t val, uint8_t * display){
  uint32_t error = SEVENSEG_ERROR_NONE;
  /* Ascii Digit */
  if(val >= '0' && val <= '9'){
    *display = SevenSeg_digArray[val - '0'];
  } 
  /* Numeric Digit */
  else if (val >= 0 && val <= 9){
    *display = SevenSeg_digArray[val];
  }
  /* Lower case */
  else if (val >= 'a' && val <='z') {
    *display = SevenSeg_charArray[val - 'a'];
  }
  /* Uppder case */
  else if (val >= 'A' && val <='Z') {
    *display = SevenSeg_charArray[val - 'A'];
  }
  /* Dash */
  else if (val == '-') {
    *display = SEVENSEG_CHAR_DASH;
  }
  /* Unknown */
  else {
    error = SEVENSEG_ERROR_RANGE;
    *display = SEVENSEG_CHAR_DASH;
  }
  return error;
}

/*******************************************************************************
* Function Name: SEVENSEG_displayNum()
****************************************************************************//**
* \brief Maps an ascii character (A-Z, 0-9, '-', '.') to a 7 Seg display value
*  
* \param state [In/Out] Pointer to the state struct for the Seven Segment 
*
* \param val [in] Values in tenths to display [0.0 - 99.9]
*     5 -> 0.5 -> 0.5
*     12 -> 1.2 -> 1.2
*     71 -> 7.1 -> 7.1
*     589 -> 58.9 -> 58.
*     590  -> 59.0 -> 59
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t SEVENSEG_displayNum(SEVENSEG_STATE_S* state, uint16_t val) {
  uint32_t error = SEVENSEG_ERROR_NONE;
  if (val > SEVENSEG_DECIMAL_MAX){
    error = SEVENSEG_ERROR_RANGE;
  }
  if(!error) {
    /* Store Value */
    state->_val =val;
    uint8_t lsb = 0;
    uint8_t msb = 0;
    bool dpl = false;
    bool dpm = false;
    /* <10, Represent as X.Y */
    if(val < 100) {
      lsb = val % 10;
      msb = val / 10;
      dpm = true;
    } 
    /* >=10, Represent as "XY" if integer, or "XY."" if non-integer */
    else {
      dpl = val % 10;
      lsb = val / 10;
      msb = val / 100;
    }
    /* Update character numbers */
    SEVENSEG_mapChar(lsb, &state->_char0);
    SEVENSEG_mapChar(msb, &state->_char1);
    /* Set Decimal Points */
    if(dpl) {state->_char0 |= SEVENSEG_CHAR_DOT; }
    if(dpm) {state->_char1 |= SEVENSEG_CHAR_DOT; }
    /* Update */
    error |= SEVENSEG_update(state);
  }

  return error; 
}


/* [] END OF FILE */
