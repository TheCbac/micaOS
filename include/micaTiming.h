/***************************************************************************
*                                 MICA  © 2019
*
* File: micaTiming.h
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief: Timing API for MICA
*   
*
* 2019.10.08  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef MICA_TIMING_H
  #define MICA_TIMING_H
  /***************************************
  * Included files
  ***************************************/
  #include <stdint.h>
  /***************************************
  * Macro Definitions
  ***************************************/
  #define TIMING_ERROR_SHIFT_STATE              (0) /**< Shift of a null state*/  
  #define TIMING_ERROR_SHIFT_DELAY              (1) /**< Shift of a null delay function*/

  #define TIMING_ERROR_NONE                    (0) /**< No error occurred */
  #define TIMING_ERROR_STATE                   (1u << TIMING_ERROR_SHIFT_STATE)       /**< Flag of a null state function */  
  #define TIMING_ERROR_DELAY                   (1u << TIMING_ERROR_SHIFT_DELAY)       /**< Flag of a null delay function */

  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
      uint32_t (*delayMs) (uint32_t time);
  } TIMING_S;
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t timing_validateStruct(TIMING_S* state);
 
#endif /* MICA_TIMING_H */
/* [] END OF FILE */
