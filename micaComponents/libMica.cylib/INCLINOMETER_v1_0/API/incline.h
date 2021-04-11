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
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "micaCommon.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_ERR_OK                 (0u) /**< Operation was successful */
    #define `$INSTANCE_NAME`_ERR_SINGLUAR_NORTH     (1u) /**< Quaternion was singluar at the north pole */
    #define `$INSTANCE_NAME`_ERR_SINGLUAR_SOUTH     (2u) /**< Quaternion was singluar at the south pole */
    /***************************************
    * Enumerated Types
    ***************************************/

    /***************************************
    * Structures
    ***************************************/
    /* Structure for controlling the filter */
    typedef struct {
        float beta;         /**< Filter Gain */
        float gyrDrift;     /**< Gyroscope drift param [rad/s] */
        float samplePeriod; /**< Sampling period [s] */
        QUATERNION_T state; /**< Value of the filter */
    } `$INSTANCE_NAME`_STATE_T;
    /***************************************
    * Function Prototype
    ***************************************/
    uint32 `$INSTANCE_NAME`_Init(`$INSTANCE_NAME`_STATE_T* filterState, float samplePeriod, float gyrDrift);
    uint32 `$INSTANCE_NAME`_UpdateFilter(`$INSTANCE_NAME`_STATE_T* filterState, ACC_DATA_F* accData, GYR_DATA_RAD_F* gyroData);
    uint32 `$INSTANCE_NAME`_QuaternionToEuler(QUATERNION_T * quat, EULER_ANGLE_T * eAngle);

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
