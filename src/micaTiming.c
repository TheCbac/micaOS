/***************************************************************************
*                                       MICA
* File: micaTiming.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   Communications functions used in micaSO 
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2019.10.01 CC - Document created
********************************************************************************/
#include "micaTiming.h"
#include "micaCommon.h"


/*******************************************************************************
* Function Name: timing_validateStruct()
****************************************************************************//**
* \brief
*  Validate the Timing structure provided
*
* \param state
*  Pointer to the TIMING Struct
*
* \return
*  An error code with the result
*******************************************************************************/
uint32_t timing_validateStruct(TIMING_S *state){
  uint32_t error = TIMING_ERROR_NONE;
  error |= (state == NULL)               ? TIMING_ERROR_STATE : TIMING_ERROR_NONE;
  error |= (state->delayMs == NULL)        ? TIMING_ERROR_DELAY : TIMING_ERROR_NONE;
  return error;
}


/* [] END OF FILE */
