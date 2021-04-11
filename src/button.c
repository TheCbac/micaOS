/***************************************************************************
*                                       MICA
* File: pushButton.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Component for interactive with a push button
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.07.03 CC - Document created
*   2020.06.18 CC - Update to anonyumous struct 
********************************************************************************/
#include "button.h"

const BUTTON_S BUTTON_DEFAULT_S = {
  ._locked = false,
  ._init = false,
  ._btnPressCount = ZERO,
  ._btnReleaseCount = ZERO,
  ._pressed = false,
  ._released = false, 
  .fn_pressCallback = NULL,
  .fn_releaseCallback= NULL,
};

/*******************************************************************************
* Function Name: button_start()
****************************************************************************//**
* \brief
*  Initializes the system
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_start(BUTTON_S *const btn){
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == false){
    btn->_init = true;
  }
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_wasButtonPressed()
****************************************************************************//**
* \brief
*  Checks to see if the button was pressed since the last check. Places the result
*   into the result param
*
* \param state [in/out]
* Pointer to the state struct
*
* \param result [out]
* Pointer to the result
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_wasButtonPressed(BUTTON_S *const btn, bool *const result) {
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* perform operation and reset */
      *result = btn->_pressed;
      btn->_pressed = false;
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_wasButtonReleased()
****************************************************************************//**
* \brief
*  Checks to see if the button was Released since the last check. Places the result
*   into the result param
*
* \param state [in/out]
* Pointer to the state struct
*
* \param result [out]
* Pointer to the result
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_wasButtonReleased(BUTTON_S *const btn, bool *const result) {
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* perform operation and reset */
      *result = btn->_released;
      btn->_released = false;
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_getPressCount()
****************************************************************************//**
* \brief
*  Places the press count into the result parameter
*
* \param state [in/out]
* Pointer to the state struct
*
* \param result [out]
* Pointer to the result
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_getPressCount(BUTTON_S *const btn, uint32_t *const result) {
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* perform operation and reset */
      *result = btn->_btnPressCount;
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_getReleaseCount()
****************************************************************************//**
* \brief
*  Places the Release count into the result parameter
*
* \param state [in/out]
* Pointer to the state struct
*
* \param result [out]
* Pointer to the result
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_getReleaseCount(BUTTON_S *const btn, uint32_t *const result) {
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* perform operation and reset */
      *result = btn->_btnReleaseCount;
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_resetCounts()
****************************************************************************//**
* \brief
*  Resets all of the counts
*
* \param state [in/out]
* Pointer to the state struct
*

*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_resetCounts(BUTTON_S *const btn){
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* perform operation and reset */
      btn->_btnPressCount = ZERO;
      btn->_btnReleaseCount = ZERO;
      btn->_pressed = false;
      btn->_released = false;
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_ISR_press()
****************************************************************************//**
* \brief
*  Function to be called by the system ISR when a button was pressed 
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_ISR_press(BUTTON_S *const btn){
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* Log the press */
      btn->_btnPressCount++;
      btn->_pressed = true;
      /* Trigger callback, if present */
      if(btn->fn_pressCallback != NULL ){
        btn->fn_pressCallback();
      }
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}

/*******************************************************************************
* Function Name: button_ISR_release()
****************************************************************************//**
* \brief
*  Function to be called by the system ISR when the button was released
*
* \param state [in/out]
* Pointer to the state struct
*
* \return
*  Error code of the operation
*******************************************************************************/
uint32_t button_ISR_release(BUTTON_S *const btn){
  uint32_t error = BUTTON_ERROR_NONE;
  if(btn->_init == true){
    if(btn->_locked == false){
      /* Lock the struct */
      btn->_locked = true;
      /* Log the press */
      btn->_btnReleaseCount++;
      btn->_released = true;
      /* Trigger callback, if present */
      if(btn->fn_releaseCallback != NULL ){
        btn->fn_releaseCallback();
      }
      /* Unlock */
      btn->_locked = false;
      }
    /* Struct was locked */
    else {
      error = BUTTON_ERROR_LOCKED;
    }
  }
  /* Struct has not been initialized */
  else {
    error = BUTTON_ERROR_INIT;
  }
  return error; 
}
/* [] END OF FILE */
