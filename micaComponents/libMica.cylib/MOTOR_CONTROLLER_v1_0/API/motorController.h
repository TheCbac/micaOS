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
*   2018.04.04 CC - Document created
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
    void `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_T direction, uint16 speed);
    void `$INSTANCE_NAME`_Test(uint8 runs, uint16 speed);
    void `$INSTANCE_NAME`_WriteSpeed(int16 speed);
    void `$INSTANCE_NAME`_commandEffort(float effort);
//    int16_t `$INSTANCE_NAME`_GetSpeed(void);


#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */
