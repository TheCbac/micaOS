/***************************************************************************/ /**
* \file inclinometer.c
* \version 1.0
*
* \brief
* Sensor fusion library to go from acceleration and angular velocity to 
*
* \date Date Created:  2018.03.17
* \date Last Modified: 2017..03.17
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
#include "inclinometer.h"
#include <math.h> /**< Needed for sqrt function */

/* Estimated Orientation quaternion element, with initial conditions */
QUATERNION_T stateQuaternion = {
    .q1 = ONE_F, /**< Initial guess for Rotation */
    .q2 = ZERO_F, /**< Initial guess for X */
    .q3 = ZERO_F, /**< Initial guess for Y */
    .q4 = ZERO_F, /**< Initial guess for Z */    
}
/*******************************************************************************
* Function Name: updateFilter()
****************************************************************************//**
*
* \brief Takes the new accelerometer and gyroscope datapoint and the previous
* state and calculates the new state. Replaces the old state with new.
*
* \param newData
* Pointer to the struct that contains the latest IMU (Acc, GYR) data.
*
* \param State
* Pointer to the quaternion for the previous state. Use these values to calculate
* new state, place in state. 
*
*******************************************************************************/
void updateFilter(IMU_DATA_T* newData, QUATERNION_T* State) {
    /*** Local variables ***/
    float norm;                 /**< Vector norm */
    float f1, f2, f3;           /**< Objective function elements */
    float J11, J12, J13, J14, J32, J33; /**< Objective function Jacobian elements */
    QUATERNION_T SEqDot_omega;  /**< Quaternion derivative from gyr */    
    QUATERNION_T SEqHatDot;     /**< Estimated direction of the gyroscope error*/
    
    /* Copy state into local variable */
    QUATERNION_T SEq = *State; 
    /* Unpack input Acceleration and angular velocity */
    float Ax = newData->Ax, Ay = newData->Ay, Az = newData->Az;
    float Wx = newData->Wx, Wy = newData->Wy, Wz = newData->Wz;
    

    /*** Auxilary variables to avoid repeated calculations ***/
    /* Half of the current estimate */
    QUATERNION_T halfSEq = {    
        .q1 = (HALF_F * SEq.q1),
        .q2 = (HALF_F * SEq.q2),
        .q3 = (HALF_F * SEq.q3),
        .q4 = (HALF_F * SEq.q4),        
    }
    /* Double the current estimate */
    QUATERNION_T twoSEq = {    
        .q1 = (TWO_F * SEq.q1),
        .q2 = (TWO_F * SEq.q2),
        .q3 = (TWO_F * SEq.q3),
        .q4 = (TWO_F * SEq.q4),        
    }

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
    J32 = TWO_F * twoSEq.q2;    /**< Negated in matrix multiplication */
    J33 = TWO_F * twoSEq.q3;    /**< Negated in matrix multiplication */
    
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
    SEqDot_omega.q1 = (-halfSEq.q2 * Wx) - (halfSEq.q3 * Wy) - (halfSeq.q4 * Wz);
    SEqDot_omega.q2 = ( halfSEq.q1 * Wx) + (halfSEq.q3 * Wz) - (halfSeq.q4 * Wy);
    SEqDot_omega.q3 = ( halfSEq.q1 * Wy) - (halfSEq.q2 * Wz) + (halfSeq.q4 * Wx);
    SEqDot_omega.q4 = ( halfSEq.q1 * Wz) + (halfSEq.q2 * Wy) - (halfSeq.q3 * Wx);
    
    /* Compute and integrate the estimated quaternion derivative */
    SEq.q1 += (SEqDot_omega.q1 - (BETA * SEqHatDot.q1)) * DELTA_T;
    SEq.q2 += (SEqDot_omega.q2 - (BETA * SEqHatDot.q2)) * DELTA_T;
    SEq.q3 += (SEqDot_omega.q3 - (BETA * SEqHatDot.q3)) * DELTA_T;
    SEq.q4 += (SEqDot_omega.q4 - (BETA * SEqHatDot.q4)) * DELTA_T;
    /* Normalize */
    norm = sqrt( (SEq.q1 * SEq.q1) + (SEq.q2 * SEq.q2) + (SEq.q3 * SEq.q3) + (SEq.q4 * SEq.q4) );
    SEq.q1 /= norm;
    SEq.q2 /= norm;
    SEq.q3 /= norm;
    SEq.q4 /= norm;
    
    /* Copy output to state */
    *State = SEq;
}
/* [] END OF FILE */
