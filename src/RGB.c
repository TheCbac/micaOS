/***************************************************************************
*                                       MICA
* File: RGB.c
* Workspace: micaOS
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for controlling an RGB LED
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.02.28 CC - Document created
********************************************************************************/
#include "RGB.h"


/*******************************************************************************
* Function Name: RGB_start()
****************************************************************************//**
* \brief
*   Checks to ensure the RGB pin functions are valid, sets the active low state,
*   and turns all the LEDs off
*
* \param state [in/out]
* Pointer to the state struct
*
* \param activePinVal [in]
* Value of the active pin. I.e. 1 -> LED will be on when the pin is high
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_start(RGB_S *const state, bool activePinState){
  uint32_t error = RGB_ERROR_NONE;
  error |= (state->_RGB_pin_R_Write == NULL) ? RGB_ERROR_NONE : RGB_ERROR_PINWRITE;
  error |= (state->_RGB_pin_G_Write == NULL) ? RGB_ERROR_NONE : RGB_ERROR_PINWRITE;
  error |= (state->_RGB_pin_B_Write == NULL) ? RGB_ERROR_NONE : RGB_ERROR_PINWRITE;
  if(!error) {
    state->_init = true;
    state->_activeLow = !activePinState;
    error |= RGB_Write(state, RGB_None);
  } else {
    state->_init = false;
  }
  return error; 
}

/*******************************************************************************
* Function Name: RGB_start()
****************************************************************************//**
* \brief
*   Checks to ensure the RGB pin functions are valid, sets the active low state,
*   and turns all the LEDs off
*
* \param state [in/out]
* Pointer to the state struct
*
* \param activePinVal [in]
* Value of the active pin. I.e. 1 -> LED will be on when the pin is high
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_Write(RGB_S *const state, RGB_Colors_T color) {
  uint32_t error = RGB_ERROR_NONE;
  if(state->_init) {
    /* Update state variables */
    state->_R = (bool) color & RGB_R_MASK;
    state->_G = (bool) color & RGB_G_MASK;
    state->_B = (bool) color & RGB_B_MASK;
    /* Account for the active state */
    bool actLow = state->_activeLow;
    state->_RGB_pin_R_Write(actLow ^ state->_R);
    state->_RGB_pin_G_Write(actLow ^ state->_G);
    state->_RGB_pin_B_Write(actLow ^ state->_B);
  } else {
    error = RGB_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: RGB_R_Write()
****************************************************************************//**
* \brief
*   Sets the state of the red pin
*
* \param state [in/out]
* Pointer to the state struct
*
* \param ledR [in]
* Value of the LED state 
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_R_Write(RGB_S *const state, RGB_LED_T ledR) {
  uint32_t error = RGB_ERROR_NONE;
  if(state->_init) {
    state->_R=ledR;
    state->_RGB_pin_R_Write(state->_activeLow ^ state->_R);
  } else {
    error = RGB_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: RGB_G_Write()
****************************************************************************//**
* \brief
*   Sets the state of the green pin
*
* \param state [in/out]
* Pointer to the state struct
*
* \param ledR [in]
* Value of the LED state 
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_G_Write(RGB_S *const state, RGB_LED_T ledG) {
  uint32_t error = RGB_ERROR_NONE;
  if(state->_init) {
    state->_G=ledG;
    state->_RGB_pin_G_Write(state->_activeLow ^ state->_G);
  } else {
    error = RGB_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: RGB_B_Write()
****************************************************************************//**
* \brief
*   Sets the state of the blue pin
*
* \param state [in/out]
* Pointer to the state struct
*
* \param ledR [in]
* Value of the LED state 
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_B_Write(RGB_S *const state, RGB_LED_T ledB) {
  uint32_t error = RGB_ERROR_NONE;
  if(state->_init) {
    state->_B=ledB;
    state->_RGB_pin_B_Write(state->_activeLow ^ state->_B);
  } else {
    error = RGB_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: RGB_R_Toggle()
****************************************************************************//**
* \brief
*   Toggle the Red led state
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_R_Toggle(RGB_S *const state){
  return RGB_R_Write(state, !state->_R); 
}

/*******************************************************************************
* Function Name: RGB_G_Toggle()
****************************************************************************//**
* \brief
*   Toggle the Green led state
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_G_Toggle(RGB_S *const state){
  return RGB_G_Write(state, !state->_G); 
}

/*******************************************************************************
* Function Name: RGB_B_Toggle()
****************************************************************************//**
* \brief
*   Toggle the blue led state
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t RGB_B_Toggle(RGB_S *const state){
  return RGB_B_Write(state, !state->_B); 
}

/* [] END OF FILE */
