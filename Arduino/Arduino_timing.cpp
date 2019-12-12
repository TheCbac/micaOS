/***************************************************************************
*                                 MICA  © 2019
*
* File: Arduino_timing.cpp
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   
*
* <date>  - Document Created
********************************************************************************/
#include "Arduino_timing.h"
#include "Arduino.h"

/*******************************************************************************
* Function Name: timingArduino_start()
****************************************************************************//**
* \brief Registers timing functions
*
* \param state [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t timingArduino_start(TIMING_S* state) {
  /* Register the Arduino commands and start */
  state->delayMs = timingArduino_delayMs;
  return TIMING_ERROR_NONE;
}

/*******************************************************************************
* Function Name: timingArduino_delayMs()
****************************************************************************//**
* \brief delays (blocks) for a specified number of milliseconds
*
* \param uart [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t timingArduino_delayMs(uint32_t millis) {
  delay(millis);
  return TIMING_ERROR_NONE;
}

/* [] END OF FILE */
