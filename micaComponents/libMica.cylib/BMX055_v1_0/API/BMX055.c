/***************************************************************************
*                                       MICA
* File: BMX055.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 IMU
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.13 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$i2cIncludeFile`.h"
#include "`$INSTANCE_NAME`_Common.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
*
* \brief Starts all three devices (Acc, GYR, and MAG)
*
* \param deviceState
*  Pointer to struct to place the device settings into
*
* \return
*  An error code with the result of the start procedure. 
*  The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Start(`$INSTANCE_NAME`_STATE_T* deviceState) {
    /* Initialize Accelerometer */
    uint32 initError = ZERO;
    initError += `$INSTANCE_NAME`_Acc_Reset(&deviceState->acc);
    /* Initialize Gyroscope */
    initError += `$INSTANCE_NAME`_Gyr_Reset(&deviceState->gyr);
    /* Initialize Magnetomter */
    initError += `$INSTANCE_NAME`_Mag_Reset(&deviceState->mag);
    /* Return any errors */
    return initError;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop(`$INSTANCE_NAME`_STATE_T* deviceState)
********************************************************************************
*
* \brief Stop all three devices (Acc, GYR, and MAG)
*
* \param deviceState
*  Pointer to struct to place the device settings into
*
* \return
* uint8: An error code with the result of the Stop procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful stop
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Stop(`$INSTANCE_NAME`_STATE_T* deviceState) {
    /* Place Accelerometer in deep suspend  */
    uint32 stopError = `$INSTANCE_NAME`_Acc_SetPowerMode(&deviceState->acc, `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND);
    /* Place Gyro in deep suspend */
    stopError += `$INSTANCE_NAME`_Gyr_SetPowerMode(&deviceState->gyr, `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND);
    /* Place Mag in suspend */
    stopError += `$INSTANCE_NAME`_Mag_SetPowerMode(&deviceState->mag, `$INSTANCE_NAME`_MAG_PM_SUSPEND);
    /* Return any errors */
    return stopError;    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetParameters()
********************************************************************************
*
* \brief Writes the parameters out to the device specified
*
* \param deviceAddr
*  Address of the device
*
* \param numParams
* Number of parameters to be written to the device. The array sensor params
* should be double this length as each parameter is in the formate (address, value)
* 
* \param registerList
* The list of registers to write to. Must be of same length as registerVal
* 
* \param registerVal
* The list of values to write to the registers. Forms a pair with register
* list, must be of same length. 
*
* \return
* uint8: An error code with the result of the start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN;    | An unknown device address used
*   Error from I2C Write function, `$i2cWriteFunction`
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SetParameters(uint8 deviceAddr, uint8 numParams, uint8* registerList, uint8* registerVal) {
    /* Ensure the correct device was written to */
    switch(deviceAddr){
        /* Accelerometer, gyroscope or magnetometer */
        case `$INSTANCE_NAME`_ACC_ADDR:        
        case `$INSTANCE_NAME`_GYR_ADDR:
        case `$INSTANCE_NAME`_MAG_ADDR:
            break;
        /* Unknown device */
        default:
            return `$INSTANCE_NAME`_ERR_DEVICE_UNKNOWN;
    }
   /* Iterate through each command */
    uint8 index;
    for (index = ZERO; index < numParams; index++ ){
        uint32 result = `$i2cWriteFunction`(deviceAddr, registerList[index], registerVal[index]);
        /* Ensure it was valid */
        if (result != `$INSTANCE_NAME`_ERR_OK) {
            return result;
        }
    }
    /* Return Success*/
    return `$INSTANCE_NAME`_ERR_OK;
}

/* [] END OF FILE */
