/***************************************************************************
*                                       MICA
* File: button.h
* Workspace: micaOS
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
*   2020.06.18 CC - Update to anonymous struct
********************************************************************************/
/* Header Guard */
#ifndef BUTTON_H
  #define BUTTON_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaCommon.h"
  #include <stdbool.h>
  
  /***************************************
  * Macro Definitions
  ***************************************/
  #define btnEncoder_ACTIVE_HIGH         (1)

  
  #define BUTTON_ERROR_NONE       (0)
  #define BUTTON_ERROR_INIT       (1u << 0) /* Structure has not been initialized */
  #define BUTTON_ERROR_LOCKED     (1u << 1) /* Structure was locked */

  /***************************************
  * Structures 
  ***************************************/
  typedef struct {
    uint32_t _btnPressCount;   /* Number of times button has been pressed */
    uint32_t _btnReleaseCount;     /* Number of times button has been released */
    bool _pressed;      /* Has the button been pressed */
    bool _released;     /* Has the button been released */
    void (*fn_pressCallback) (void); /* Pointer to an optional press callback function */
    void (*fn_releaseCallback) (void); /*  Pointer to an optional release callback function*/
    
    bool _locked;   /* Mutex */
    bool _init;
  } BUTTON_S;

  /* Default structure */
  extern const BUTTON_S BUTTON_DEFAULT_S;
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t button_start(BUTTON_S *const btn); 
  uint32_t button_wasButtonPressed(BUTTON_S *const btn, bool *const result);
  uint32_t button_wasButtonReleased(BUTTON_S *const btn, bool *const result);
  uint32_t button_getPressCount(BUTTON_S *const btn, uint32_t *const result);
  uint32_t button_getReleaseCount(BUTTON_S *const btn, uint32_t *const result);
  uint32_t button_resetCounts(BUTTON_S *const btn);


  uint32_t button_ISR_press(BUTTON_S *const btn);
  uint32_t button_ISR_release(BUTTON_S *const btn);

  /***************************************
  * ISR prototypes
  ***************************************/

    
#endif /* BUTTON_H */
    

/* [] END OF FILE */
