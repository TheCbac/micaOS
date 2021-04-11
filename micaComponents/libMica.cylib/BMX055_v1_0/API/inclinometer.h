/***************************************************************************
*                                       MICA
* File: Inclinometer.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for sensor fusion library
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.17 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef INCLINOMETER_H
    #define INCLINOMETER_H
    /***************************************
    * Included Files
    ***************************************/

    /***************************************
    * Macro Definitions
    ***************************************/
    /* System Constants */
    #define DELTA_T             (0.001f) /**< Sampling period in seconds */
    #define GYRO_MEAS_ERROR     (3.14159265358979f) * (5.0f / 180.0f) /**< Gyroscope measurement error */
    #define BETA                sqrt(3.0f / 4.0f) * GYRO_MEAS_ERROR /**< Compute beta */

    #define ZERO_F              (0.0f)  /**< Floating point Zero */
    #define HALF_F              (0.5f)  /**< Floating point half */
    #define ONE_F               (1.0f)  /**< Floating point One */
    #define TWO_F               (2.0f)  /**< Floating point two */
    
    /***************************************
    * Structs
    ***************************************/

    /* Struct for passing data from the IMU (Acc, GYR) */
    typedef struct {
        float Ax; /**< Acceleration X */
        float Ay; /**< Acceleration Y */
        float Az; /**< Acceleration Z */
        float Wx; /**< Angular velocity, X */
        float Wy; /**< Angular velocity, Y */
        float Wz; /**< Angular velocity, Z */
    } IMU_DATA_T; 

    /* Struct for representing a Quaternion */
    typedef struct {
        float q1; /**< First element (Scalar) */
        float q2; /**< Second element (i) */
        float q3; /**< Second element (j) */
        float q4; /**< Second element (k) */
    } QUATERNION_T;

    // /* Struct for representing a Quaternion */
    // typedef struct {
    //     float beta; /**< Value used in filter */
    //     float deltaT; /**< Second element (i) */
    // } FILTER_SETTING_T;

#endif /* INCLINOMETER_H */
/* [] END OF FILE */