/***************************************************************************
*                                 MICA  © 2019
*
* File: PSoC_timing.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   
*
* <date>  - Document Created
********************************************************************************/
#include "PSoC_timing.h"
#include "project.h"

/*******************************************************************************
* Function Name: timingPsoc_start()
****************************************************************************//**
* \brief Registers timing functions
*
* \param state [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t timingPsoc_start(TIMING_S* state) {
  /* Register the Psoc commands and start */
  state->delayMs = timingPsoc_delayMs;
  return TIMING_ERROR_NONE;
}

/*******************************************************************************
* Function Name: timingPsoc_delayMs()
****************************************************************************//**
* \brief delays (blocks) for a specified number of milliseconds
*
* \param uart [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t timingPsoc_delayMs(uint32_t millis) {
  CyDelay(millis);
  return TIMING_ERROR_NONE;
}

/* [] END OF FILE */
