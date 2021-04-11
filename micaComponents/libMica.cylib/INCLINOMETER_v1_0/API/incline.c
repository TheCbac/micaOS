/***************************************************************************
*                                       MICA
* File:  `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Definitions for the Incline sensor
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.10 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include <math.h> /**< Needed for sqrt function */

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init()
********************************************************************************
* Summary:
*   Initialize the Inclinometer filter
*
* \param filterState
*   Pointer to the Inclinometer filter state
*
* \param samplePeriod
*   The nominal time between each sample in [s]
*
* \param gyrDrift
*   The nominal gyroscope drift [deg/s]
*
* \return
*   An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Initialization
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Init(`$INSTANCE_NAME`_STATE_T* filterState, float samplePeriod, float gyrDrift){
    /* Reset the state quaternion */
    QUATERNION_T initQaut = {.q1 = (ONE_F), .q2 = (ZERO_F), .q3 = (ZERO_F), .q4 = (ZERO_F)};
    filterState->state = initQaut;
    /* Set the sample period */
    filterState->samplePeriod = samplePeriod;
    /* Calculate and set gain */
    filterState->gyrDrift = gyrDrift;
    filterState->beta = PI * gyrDrift / (180.0f);
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UpdateFilter()
****************************************************************************//**
*
* \brief Takes the new accelerometer and gyroscope datapoint and the previous
* state and calculates the new state. Replaces the old state with new.
*
* \param filterState
* Pointer to the quaternion for the previous state. Use these values to calculate
* new state, place in state. 
*
* \param accData
* Pointer to the struct that contains the latest Acc data [m/s^2]
* 
* \param gyroData
* Pointer to the struct that contains the latest Gyr data [rad/s]
*
* \return
*   An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Initialization
*******************************************************************************/
 uint32 `$INSTANCE_NAME`_UpdateFilter(`$INSTANCE_NAME`_STATE_T* filterState, ACC_DATA_F* accData, GYR_DATA_RAD_F* gyroData){
    /*** Local variables ***/
    float norm;                 /**< Vector norm */
    float f1, f2, f3;           /**< Objective function elements */
    float J11, J12, J13, J14, J32, J33; /**< Objective function Jacobian elements */
    QUATERNION_T SEqDot_omega;  /**< Quaternion derivative from gyr */    
    QUATERNION_T SEqHatDot;     /**< Estimated direction of the gyroscope error*/
    
    /* Copy state into local variable */
    QUATERNION_T SEq = filterState->state; 
    float beta = filterState->beta;
    float samplePeriod = filterState->samplePeriod;
    /* Unpack input Accelerometer data*/
    float Ax = accData->Ax;
    float Ay = accData->Ay;
    float Az = accData->Az;
    /* Unpack input gyro data*/
    float Wx = gyroData->Wx;
    float Wy = gyroData->Wy;
    float Wz = gyroData->Wz;

    /*** Auxilary variables to avoid repeated calculations ***/
    /* Half of the current estimate */
    QUATERNION_T halfSEq = {    
        .q1 = (HALF_F * SEq.q1),
        .q2 = (HALF_F * SEq.q2),
        .q3 = (HALF_F * SEq.q3),
        .q4 = (HALF_F * SEq.q4),        
    };
    /* Double the current estimate */
    QUATERNION_T twoSEq = {    
        .q1 = (TWO_F * SEq.q1),
        .q2 = (TWO_F * SEq.q2),
        .q3 = (TWO_F * SEq.q3),
        .q4 = (TWO_F * SEq.q4),        
    };

    /* Normalize the Accelerometer measurements */
    norm = sqrt( (Ax * Ax) + (Ay * Ay) + (Az * Az) );
    Ax /= norm;
    Ay /= norm;
    Az /= norm;

    /* Compute objective function (Eqn. 25) */
    f1 =         (twoSEq.q2 * SEq.q4) - (twoSEq.q1 * SEq.q3) - Ax;
    f2 =         (twoSEq.q1 * SEq.q2) + (twoSEq.q3 * SEq.q4) - Ay;
    f3 = ONE_F - (twoSEq.q2 * SEq.q2) - (twoSEq.q3 * SEq.q3) - Az;

    /* Compute the Jacobian (Eqn. 26) */
    J11 = twoSEq.q3;            /**< Negated in matrix multiplication */
    J12 = twoSEq.q4;    
    J13 = twoSEq.q1;            /**< Negated in matrix multiplication */
    J14 = twoSEq.q2;
    J32 = TWO_F * J14;    /**< Negated in matrix multiplication */
    J33 = TWO_F * J11;    /**< Negated in matrix multiplication */
    
    /* Compute the gradient */
    SEqHatDot.q1 = (J14 * f2) - (J11 * f1);
    SEqHatDot.q2 = (J12 * f1) + (J13 * f2) - (J32 * f3);
    SEqHatDot.q3 = (J12 * f2) - (J33 * f3) - (J13 * f1);
    SEqHatDot.q4 = (J14 * f1) + (J11 * f2);
    /* Normalize the gradient */
    norm = sqrt( (SEqHatDot.q1 * SEqHatDot.q1) + (SEqHatDot.q2 * SEqHatDot.q2) +\
                 (SEqHatDot.q3 * SEqHatDot.q3) + (SEqHatDot.q4 * SEqHatDot.q4) ); 
    SEqHatDot.q1 /= norm;
    SEqHatDot.q2 /= norm;
    SEqHatDot.q3 /= norm;
    SEqHatDot.q4 /= norm;

    /* Compute the quaternion derivative measured by GYR */
    SEqDot_omega.q1 = (-halfSEq.q2 * Wx) - (halfSEq.q3 * Wy) - (halfSEq.q4 * Wz);
    SEqDot_omega.q2 = ( halfSEq.q1 * Wx) + (halfSEq.q3 * Wz) - (halfSEq.q4 * Wy);
    SEqDot_omega.q3 = ( halfSEq.q1 * Wy) - (halfSEq.q2 * Wz) + (halfSEq.q4 * Wx);
    SEqDot_omega.q4 = ( halfSEq.q1 * Wz) + (halfSEq.q2 * Wy) - (halfSEq.q3 * Wx);
    
    /* Compute and integrate the estimated quaternion derivative */
    SEq.q1 += (SEqDot_omega.q1 - (beta * SEqHatDot.q1)) * samplePeriod;
    SEq.q2 += (SEqDot_omega.q2 - (beta * SEqHatDot.q2)) * samplePeriod;
    SEq.q3 += (SEqDot_omega.q3 - (beta * SEqHatDot.q3)) * samplePeriod;
    SEq.q4 += (SEqDot_omega.q4 - (beta * SEqHatDot.q4)) * samplePeriod;
    /* Normalize */
    norm = sqrt( (SEq.q1 * SEq.q1) + (SEq.q2 * SEq.q2) + (SEq.q3 * SEq.q3) + (SEq.q4 * SEq.q4) );
    SEq.q1 /= norm;
    SEq.q2 /= norm;
    SEq.q3 /= norm;
    SEq.q4 /= norm;
    
    /* Copy output to state */
    filterState->state = SEq;
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_QuaternionToEuler()
****************************************************************************//**
*
* \brief Takes in a quaternion and converts it to euler angles. 
*
* \param quat - Pointer to quaternion to convert
*
* \param eAngle - Pointer to euler angle to place results into
*
* \return
*   An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Initialization
*******************************************************************************/
 uint32 `$INSTANCE_NAME`_QuaternionToEuler(QUATERNION_T * quat, EULER_ANGLE_T * eAngle){
    /* Unpack quaternion */
    float qw = quat->q1;
    float qx = quat->q2;
    float qy = quat->q3;
    float qz = quat->q4;
    
    float test = qx*qy + qz*qw;
    /* Singular at North pole */
    if(test > (0.499f) ){
        eAngle->pitch = TWO_F * atan2f(qx, qw);
        eAngle->yaw = M_PI / TWO_F;
        eAngle->roll = ZERO_F;
        return `$INSTANCE_NAME`_ERR_SINGLUAR_NORTH;
    }
    /* Singular at south pole */
    if(test < (-0.499f) ){
        eAngle->pitch = (-1.0f) * TWO_F * atan2f(qx, qw);
        eAngle->yaw = (-1.0f) * M_PI / TWO_F;
        eAngle->roll = ZERO_F;
        return `$INSTANCE_NAME`_ERR_SINGLUAR_SOUTH;   
    }
    /* Pre-compute */
    float sqx = qx*qx;
    float sqy = qy*qy;
    float sqz = qz*qz;
    /* Assign values */
    eAngle->pitch = atan2f( (TWO_F * qy * qw) - (TWO_F * qx * qz), ONE_F - (TWO_F * (sqy + sqz)) );
    eAngle->yaw = asinf(TWO_F * test);
    eAngle->roll = atan2f(TWO_F * (qx*qw - qy*qz), ONE_F - (TWO_F * (sqx + sqz)) ); 
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/* [] END OF FILE */
