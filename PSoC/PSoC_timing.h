/***************************************************************************
*                                 MICA  © 2019
*
* File: PSoC_timing.h
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   
*
* <date>  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef PSOC_TIMING_H
  #define PSOC_TIMING_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaTiming.h"
  /***************************************
  * Macro Definitions
  ***************************************/

  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t timingPsoc_start(TIMING_S* state);
  uint32_t timingPsoc_delayMs(uint32_t millis);
 
#endif /* PSOC_TIMING_H */
/* [] END OF FILE */
