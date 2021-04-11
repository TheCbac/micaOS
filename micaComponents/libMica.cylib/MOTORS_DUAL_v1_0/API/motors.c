/***************************************************************************
*                                       MICA
* File: `$INSTANCE_NAME`.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for contolling dual Hbridge motors
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.04.10 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_PWM_M1.h"
#include "`$INSTANCE_NAME`_PWM_M2.h"
#include "`$INSTANCE_NAME`_ControlReg.h"
#include "micaCommon.h"

#define `$INSTANCE_NAME`_TEST_DELAY         (1500)
#define `$INSTANCE_NAME`_TEST_DELAY_HALF    (`$INSTANCE_NAME`_TEST_DELAY / 2)
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
* Summary:
*   Initialize the H-brige - start the PWM blocks.
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void) {
    /* Start the PWM blocks */    
    `$INSTANCE_NAME`_PWM_M1_Start();
    `$INSTANCE_NAME`_PWM_M2_Start();
    /* Disable both motors from moving */
    `$INSTANCE_NAME`_Disable();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable()
********************************************************************************
* Summary:
*   Enables both motors
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void) {
    /* Read the current value in the control register*/    
    uint8 val = `$INSTANCE_NAME`_ControlReg_Read();
    /* Set enable bits */
    val |= (`$INSTANCE_NAME`_M1_EN | `$INSTANCE_NAME`_M2_EN);
    /* Write the value out */
    `$INSTANCE_NAME`_ControlReg_Write(val);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Disable()
********************************************************************************
* Summary:
*   Enables both motors
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Disable(void) {
    /* Read the current value in the control register*/    
    uint8 val = `$INSTANCE_NAME`_ControlReg_Read();
    /* Clear enable bits */
    val &= ~(`$INSTANCE_NAME`_M1_EN | `$INSTANCE_NAME`_M2_EN);
    /* Write the value out */
    `$INSTANCE_NAME`_ControlReg_Write(val);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetState()
********************************************************************************
* Summary:
*   Sets the state of the motors
*
* \param state
*   Next state of the motor to write
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SetState(bool state){
    if(state){
        `$INSTANCE_NAME`_Enable();
    } else {
        `$INSTANCE_NAME`_Disable();   
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Move()
********************************************************************************
* Summary:
*   Moves the robot in the specified direction at the specified speed.
*
* Parameter direction
*   The diretion to move
*
* Parameter speed
*   The speed to move at
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_T direction, uint16 speed){
    /* Don't change Enable/disable state */
    uint8 controlVal = `$INSTANCE_NAME`_ControlReg_Read() & `$INSTANCE_NAME`_MASK_ENABLE;
    /* Act according to direction */
    switch(direction) {
        /* Forward */
        case  `$INSTANCE_NAME`_DIRECTION_FORWARD: {
            controlVal |= ( `$INSTANCE_NAME`_M1_FORWARD | `$INSTANCE_NAME`_M2_FORWARD);
            break;
        }
        /* Backward */
        case `$INSTANCE_NAME`_DIRECTION_BACKWARD: {
            controlVal |= ( `$INSTANCE_NAME`_M1_BACKWARD | `$INSTANCE_NAME`_M2_BACKWARD);
            break;
        }
        /* CW */
        case `$INSTANCE_NAME`_DIRECTION_CW: {
            controlVal |= ( `$INSTANCE_NAME`_M1_FORWARD | `$INSTANCE_NAME`_M2_BACKWARD);
            break;
        }
         /* CCW */
        case `$INSTANCE_NAME`_DIRECTION_CCW: {
            controlVal |= ( `$INSTANCE_NAME`_M1_BACKWARD | `$INSTANCE_NAME`_M2_FORWARD);
            break;
        }
    }
    /* Write the control register value */
    `$INSTANCE_NAME`_ControlReg_Write(controlVal);
    /* Clip the speed to max value */
    uint16 clippedSpeed = (speed > `$INSTANCE_NAME`_SPEED_MAX) ? `$INSTANCE_NAME`_SPEED_MAX : speed;
    /* Write to the PWM blocks */
    `$INSTANCE_NAME`_PWM_M1_WriteCompare(clippedSpeed);
    `$INSTANCE_NAME`_PWM_M2_WriteCompare(clippedSpeed);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Test()
********************************************************************************
* Summary:
*   Runs through a testing routine of the motors
*
* Parameter runs
*   The number of times to run through the test routine - 0 means infinite
*
* Parameter speed
*   The compare value for the PWM motors
*
* Return:
*   None.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Test(uint8 runs, uint16 speed){
    uint8 i = ZERO;
    /* Run through a specified number of times */
    while( (i++ < runs) || runs == 0) {
        /* Initial Delay */
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY);
        
        /* Forward  */
        `$INSTANCE_NAME`_Enable();
        `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_FORWARD, speed);
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY);
        /* Stop for half time */
        `$INSTANCE_NAME`_Disable();
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY_HALF);
        
        /* Back  */
        `$INSTANCE_NAME`_Enable();
        `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_BACKWARD, speed);
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY);
        /* Stop for half time */
        `$INSTANCE_NAME`_Disable();
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY_HALF);
        
        /* CW  */
        `$INSTANCE_NAME`_Enable();
        `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_CW, speed);
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY);
        /* Stop for half time */
        `$INSTANCE_NAME`_Disable();
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY_HALF);
        
        /* CCW  */
        `$INSTANCE_NAME`_Enable();
        `$INSTANCE_NAME`_Move(`$INSTANCE_NAME`_DIRECTION_CCW, speed);
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY);
        /* Disable motors at end of run */
        `$INSTANCE_NAME`_Disable();
        MICA_delayMs(`$INSTANCE_NAME`_TEST_DELAY_HALF);
    }
}
    
    
/* [] END OF FILE */
