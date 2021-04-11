/***************************************************************************
*                                       MICA
* File: pushButton.h
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
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include "cytypes.h"
    #include "micaCommon.h"
    #include <stdbool.h>
    
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_ACTIVE_HIGH         (`$activeHigh`)
    /***************************************
    * Function declarations 
    ***************************************/
    uint32 `$INSTANCE_NAME`_getPressCount(void);
    uint32 `$INSTANCE_NAME`_getReleaseCount(void);
    void `$INSTANCE_NAME`_resetBtnCounts(void);
    bool `$INSTANCE_NAME`_wasButtonPressed(void);
    bool `$INSTANCE_NAME`_wasButtonReleased(void);
    void `$INSTANCE_NAME`_EnableBtnInterrupts(void);
    void `$INSTANCE_NAME`_SetBtnPressIsr(FUNCTION_VOID_T * callback);
    void `$INSTANCE_NAME`_SetBtnReleaseIsr(FUNCTION_VOID_T * callback);
    /***************************************
    * ISR prototypes
    ***************************************/
    void `$INSTANCE_NAME`_ISR_testButton_press(void);
    void `$INSTANCE_NAME`_ISR_testButton_release(void);
    
    
#endif /* `$INSTANCE_NAME`_H */
    

/* [] END OF FILE */
