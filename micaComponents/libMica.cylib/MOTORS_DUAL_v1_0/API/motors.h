/***************************************************************************
*                                       MICA
* File:  `$INSTANCE_NAME`.h
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Definition for the H-bridge controller
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.03 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"
    #include <stdbool.h>
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_FORWARD        (0b00u)
    #define `$INSTANCE_NAME`_BACKWARD       (0b01u)
    #define `$INSTANCE_NAME`_EN             (1u << 2u)

    #define `$INSTANCE_NAME`_M1_SHIFT       (0u)
    #define `$INSTANCE_NAME`_M2_SHIFT       (4u)

    #define `$INSTANCE_NAME`_M1_FORWARD     (`$INSTANCE_NAME`_FORWARD  << `$INSTANCE_NAME`_M1_SHIFT)
    #define `$INSTANCE_NAME`_M1_BACKWARD    (`$INSTANCE_NAME`_BACKWARD << `$INSTANCE_NAME`_M1_SHIFT)
    #define `$INSTANCE_NAME`_M1_EN          (`$INSTANCE_NAME`_EN       << `$INSTANCE_NAME`_M1_SHIFT)
    
    #define `$INSTANCE_NAME`_M2_FORWARD     (`$INSTANCE_NAME`_FORWARD  << `$INSTANCE_NAME`_M2_SHIFT)
    #define `$INSTANCE_NAME`_M2_BACKWARD    (`$INSTANCE_NAME`_BACKWARD << `$INSTANCE_NAME`_M2_SHIFT)
    #define `$INSTANCE_NAME`_M2_EN          (`$INSTANCE_NAME`_EN       << `$INSTANCE_NAME`_M2_SHIFT)
    
    #define `$INSTANCE_NAME`_MASK_ENABLE   (`$INSTANCE_NAME`_M1_EN | `$INSTANCE_NAME`_M2_EN)
    
    #define `$INSTANCE_NAME`_SPEED_MAX      (2400)
    #define `$INSTANCE_NAME`_SPEED_HALF     (`$INSTANCE_NAME`_SPEED_MAX / 2)
    #define `$INSTANCE_NAME`_SPEED_SLOW     (`$INSTANCE_NAME`_SPEED_MAX / 6)
    #define `$INSTANCE_NAME`_SPEED_MIN      (0)
    
    
    /***************************************
    * Enumerated Types
    ***************************************/
    /* The possible directions*/
    typedef enum{
        `$INSTANCE_NAME`_DIRECTION_FORWARD = (0u),
        `$INSTANCE_NAME`_DIRECTION_BACKWARD,
        `$INSTANCE_NAME`_DIRECTION_CW,
        `$INSTANCE_NAME`_DIRECTION_CCW
    } `$INSTANCE_NAME`_DIRECTION_T;
    /***************************************
    * Structures
    ***************************************/
    /* Contains the speed of the motors */
    typedef struct{
        int16 leftSpeed;
        int16 rightSpeed;
    } `$INSTANCE_NAME`_MOTOR_T; 
    /***************************************
    * Function Prototype
    ***************************************/
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_Enable(void);
    void `$INSTANCE_NAME`_Disable(void);
    void `$INSTANCE_NAME`_SetState(bool state);
    
    void `$INSTANCE_NAME`_M1_WriteSpeed(int16 speed);
    void `$INSTANCE_NAME`_M2_WriteSpeed(int16 speed);
    void `$INSTANCE_NAME`_WriteSpeed(`$INSTANCE_NAME`_MOTOR_T* motors);
    `$INSTANCE_NAME`_MOTOR_T `$INSTANCE_NAME`_GetSpeed(void);
    void `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_T direction, uint16 speed);
    void `$INSTANCE_NAME`_Test(uint8 runs, uint16 speed);

#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */
