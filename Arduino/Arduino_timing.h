/***************************************************************************
*                                 MICA  © 2019
*
* File: Arduino_timing.h
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
#ifndef ARDUINO_TIMING_H
  #define ARDUINO_TIMING_H
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
  uint32_t timingArduino_start(TIMING_S* state);
  uint32_t timingArduino_delayMs(uint32_t millis);
 
#endif /* ARDUINO_TIMING_H */
/* [] END OF FILE */
