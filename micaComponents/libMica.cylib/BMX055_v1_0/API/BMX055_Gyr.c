/***************************************************************************
*                                       MICA
* File: BMX055_Gyr.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 Gyroscope
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`_Gyr.h"
#include "`$i2cIncludeFile`.h"
#include "`$INSTANCE_NAME`_Common.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_testConnection()
********************************************************************************
*
* \brief Test I2C Connectivity of the Gyroscope
* 

*
* \return
* uint8: An error code with the result of the Wakeup procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On Successful Wakeup
*   `$INSTANCE_NAME`_ERR_WHOAMI             | Who am I value return did not match expected
*   `$INSTANCE_NAME`_ERR_I2C                | I2C Error occured
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_testConnection(uint32* i2cError){
    uint8 whoAmI = ZERO;
    /* Read the chip ID register */
    uint32 readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_CHIPID_REG, &whoAmI);
    /* Compare against known who am I */
    if (readError == `$INSTANCE_NAME`_ERR_OK) {
        /* Check the value received */
        if(  whoAmI == `$INSTANCE_NAME`_GYR_CHIPID_VAL) {
            return `$INSTANCE_NAME`_ERR_OK;
        }
        /* Bad Whoam i */
        return `$INSTANCE_NAME`_ERR_WHOAMI;
    }
    /* I2C Error */
    /* Pass the read error out */
    *i2cError = readError;
    return `$INSTANCE_NAME`_ERR_I2C;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Reset()
****************************************************************************//**
*
* \brief
*  Initializes the gyroscope. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Gyr_Wakeup if the sensor needs to be woken up from sleep
*
* \param gyrState
* Pointer to the state variable of the gyroscope 
*
* \return  
* uint32: An error code with the result of the Start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Start
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_Reset(`$INSTANCE_NAME`_GYR_STATE_T* gyrState) {
    /* Initiate a Gyroscope software reset */
    uint32 readError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_REG, `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_VAL);
    if(readError != `$INSTANCE_NAME`_ERR_OK){ return readError; }
    /* Wait necessary boot time */
    MICA_delayMs(`$INSTANCE_NAME`_GYR_BGW_SOFTRESET_MS);
    /* Set state values to the default */
    gyrState->powerState = `$INSTANCE_NAME`_GYR_PM_NORMAL;
    gyrState->scale = `$INSTANCE_NAME`_GYR_RANGE_2000_GAIN;
    gyrState->channels.X = true;
    gyrState->channels.Y = true;
    gyrState->channels.Z = true;
    /* Return Success  */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_SetPowerMode()
****************************************************************************//**
*
* \brief
*  Puts the Gyroscope into the low power mode specified.
*
* \param powerMode
*  Power mode to place the device into 
*
* \return  
* uint32: An error code with the result of the Sleep procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Sleep
*   `$INSTANCE_NAME`_ERR_MODE_INVALID       | An invalid power mode was specified
*   `$INSTANCE_NAME`_ERR_MODE_UNKNOWN       | An unknown power mode was specified
*   `$INSTANCE_NAME`_ERR_I2C                | I2C Error occured
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_SetPowerMode(`$INSTANCE_NAME`_GYR_STATE_T* gyrState, `$INSTANCE_NAME`_GYR_POWER_T powerMode){
    uint8 powerRegVal;
    uint32 writeError;
    bool queueWrite = true;
    /* Act according to the current state */
    switch(gyrState->powerState){
        case `$INSTANCE_NAME`_GYR_PM_NORMAL:{
            /* Normal to Next state */ 
            switch(powerMode){
                /* Place device in Fast powerup mode (Fast Powerup Bit Set + Suspend) */
                case `$INSTANCE_NAME`_GYR_PM_FAST_POWERUP:{
                    /* Set the fast power up bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_LPM2_REG , `$INSTANCE_NAME`_GYR_LPM2_FAST_POWERUP);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Prepare for suspend */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_SUSPEND;
                    break;
                }
                /* Place device in Suspend mode (Fast Powerup bit clear + Suspend) */
                case `$INSTANCE_NAME`_GYR_PM_SUSPEND:{
                    /* Clear the fast power up bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_LPM2_REG , ZERO);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Prepare for suspend */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend Mode (Deep suspend bit) */
                case `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND:{
                    /* Prepare for deep suspend */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_DEEP_SUSPEND;
                    break;    
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;  
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_GYR_PM_NORMAL */
        case `$INSTANCE_NAME`_GYR_PM_FAST_POWERUP:{
            /* Fast powerup to next state */
            switch(powerMode){
                /* Clear suspend bit */
                case  `$INSTANCE_NAME`_GYR_PM_NORMAL:{
                    /* Prepare for normal */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_NORMAL;
                    break;
                }
                /* Clear fast power up bit */
                case `$INSTANCE_NAME`_GYR_PM_SUSPEND:{
                    /* Clear the fast power up bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_LPM2_REG , ZERO);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Dequeue the LP1 Write */
                    queueWrite = false;
                    break;
                }
                /* Set the deep suspend bit */
                case `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND: {
                    /* Prepare for Deep Suspend */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_DEEP_SUSPEND;
                    break;    
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;  
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_GYR_PM_FAST_POWERUP */
        case `$INSTANCE_NAME`_GYR_PM_SUSPEND:{
            switch(powerMode){
                /* Clear suspend bit */
                case  `$INSTANCE_NAME`_GYR_PM_NORMAL:{
                    /* Prepare for normal */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_NORMAL;
                    break;
                }
                /* Clear fast power up bit */
                case `$INSTANCE_NAME`_GYR_PM_SUSPEND:{
                    /* Clear the fast power up bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_LPM2_REG , `$INSTANCE_NAME`_GYR_LPM2_FAST_POWERUP);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Dequeue the LP1 Write */
                    queueWrite = false;
                    break;
                }
                /* Set the deep suspend bit */
                case `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND: {
                    /* Prepare for Deep Suspend */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_DEEP_SUSPEND;
                    break;    
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;  
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_GYR_PM_SUSPEND */
        case `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND:{
            switch(powerMode){
                /* Clear deep suspend bit */
                case  `$INSTANCE_NAME`_GYR_PM_NORMAL:{
                    /* Prepare for normal */
                    powerRegVal = `$INSTANCE_NAME`_GYR_LPM1_NORMAL;
                    break;
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;  
                }
            }
            break;   
        } /* End `$INSTANCE_NAME`_GYR_PM_DEEP_SUSPEND */ 
        /* Unknown Power state */
        default:{
            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN;
        }
    }
    
    /* Write to the low power register value selected from above */
    if(queueWrite){
        writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_LPM1_REG, powerRegVal);
        if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
    }
    /* Update the state (valid if reached this point) */
    gyrState->powerState = powerMode;
    /* Return Success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Gyro. Places result into the gyrData
*
* \param state
*  Pointer to the state of the gyroscope
*
* \param gyrData
*  Pointer to struct to place the data into
*
* \return 
* uint32: An error code with the result of the read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | Data was not requested from any channels
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_Read(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_T* gyrData){
    /* Check the power state of the device */
    switch(state->powerState){
        /* Valid modes */
        case `$INSTANCE_NAME`_GYR_PM_NORMAL:
            break;
        /* return an error */
        default:{
            return `$INSTANCE_NAME`_ERR_MODE_INVALID;
         }
    }
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    /* Ensure at least one channel is enabled  */
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Read in the gyroscope data */
    uint8 msb = ZERO;
    uint8 lsb = ZERO;
    uint32 readError;
    /************** X Channel **************/
    if(chans.X){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_X_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_X_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Write X value */
        gyrData->Wx = (msb << SHIFT_BYTE_ONE) | lsb;
    }
    /************** Y Channel **************/
    if(chans.Y){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Y_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Y_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Write Y value */
        gyrData->Wy =(msb << SHIFT_BYTE_ONE) | lsb;
    }
    /************** Z Channel **************/
    if(chans.Z){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Z_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_GYR_ADDR, `$INSTANCE_NAME`_GYR_Z_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Write Z value */
        gyrData->Wz = (msb << SHIFT_BYTE_ONE) | lsb;
    }
    /***************************************/
    /* Indicate success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Readf_deg()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Gyroscope and converts to a floating
*  point number in units of [deg/s]
*
* \param state
*  Pointer to the state of the Gyroscope
*
* \param gyroDegData
*  Pointer to struct to place the data into
*
* \return 
* uint32: An error code with the result of the read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | Data was not requested from any channels
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_Readf_deg(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_DEG_F* gyroDegData){
    /* Read from the device */
    GYR_DATA_T gyrIntData;
    uint32 readError = `$INSTANCE_NAME`_Gyr_Read(state, &gyrIntData);
    if(readError != `$INSTANCE_NAME`_ERR_OK) {return readError;}
    /* Convert to a float */
    readError = `$INSTANCE_NAME`_Gyr_Int2FloatDeg(state, &gyrIntData, gyroDegData); 
    return readError;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Readf_rad()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Gyroscope and converts to a floating
*  point number in units of [rad/s]
*
* \param state
*  Pointer to the state of the Gyroscope
*
* \param gyrRadData
*  Pointer to struct to place the data into
*
* \return 
* uint32: An error code with the result of the read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | Data was not requested from any channels
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_Readf_rad(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_RAD_F* gyrRadData){
    /* Intermediate variables */
    GYR_DATA_DEG_F gyrDegData;
    GYR_DATA_T gyrIntData;
    /* Read from the device */
    uint32 readError = `$INSTANCE_NAME`_Gyr_Read(state, &gyrIntData);
    if(readError != `$INSTANCE_NAME`_ERR_OK) {return readError;}
    /* Convert to a float [deg/s] */
    readError = `$INSTANCE_NAME`_Gyr_Int2FloatDeg(state, &gyrIntData, &gyrDegData); 
    if(readError != `$INSTANCE_NAME`_ERR_OK) {return readError;}
    /* Convert to [rad/s] */
    readError =  `$INSTANCE_NAME`_Gyr_degToRad(&gyrDegData, gyrRadData); 
    return readError;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_Int2FloatDeg
****************************************************************************//**
*
* \brief
*  Converts an gyroscope data sample from int16 to float type. 
*
* \param State
*  Pointer to the Struct containing the settings of the device in order to scale correctly
*
* \param intData
*  Pointer to the int16 data to be converted
*       
* \param floatData 
*   Pointer to the output data in float format 
*
* \return 
* uint32: An error code with the result of the conversion procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   `$INSTANCE_NAME`_ERR_CHANNELS_NONE      | No channels indicated for conversion
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_Int2FloatDeg(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_T* intData, GYR_DATA_DEG_F* floatData){
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the gyroscope */
    float gain = state->scale;
    /* Convert to float */
    if(chans.X){ floatData->Wx = gain * (float) intData->Wx; }
    if(chans.Y){ floatData->Wy = gain * (float) intData->Wy; }
    if(chans.Z){ floatData->Wz = gain * (float) intData->Wz; }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Gyr_FloatDeg2Int(); 
****************************************************************************//**
*
* \brief
*  Converts an gyroscope data sample from float to int16 type. 
*
* \param State
*  Pointer to the Struct containing the settings of the device in order to scale correctly
*
* \param floatData
*  Pointer to the float data to be converted
*       
* \param intData 
*   Pointer to the output data in int16 format 
*
* \return 
* uint32: An error code with the result of the conversion procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_FloatDeg2Int(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_DEG_F* floatData, GYR_DATA_T* intData) {
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    /* Ensure at least one channel is enabled  */
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the gyroscope */
    float gain = state->scale;
    /* Convert to int */
    if(chans.X){ intData->Wx = (int16) (floatData->Wx / gain); }
    if(chans.Y){ intData->Wy = (int16) (floatData->Wy / gain); }
    if(chans.Z){ intData->Wz = (int16) (floatData->Wz / gain); }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_degToRad
****************************************************************************//**
*
* \brief
*  Converts an gyroscope data sample from [deg/s] to [rad/s]
*
* \param degData
*  Pointer to the struct containing the data in [deg/s]
*
* \param radData
*  Pointer to the output struct in [rad/s]
*
* \return 
* uint32: An error code with the result of the conversion procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_degToRad(GYR_DATA_DEG_F* degData, GYR_DATA_RAD_F* radData){
    /* convert to degrees */
    radData->Wx = to_radians(degData->Wx);
    radData->Wy = to_radians(degData->Wy);
    radData->Wz = to_radians(degData->Wz);
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Gyr_radToDeg
****************************************************************************//**
*
* \brief
*  Converts an gyroscope data sample from [rad/s] to [deg/s]
*
* \param radData
*  Pointer to the Struct containing the data in [rad/s]
*
* \param degData
*  Pointer to the output data in [deg/s]
*
* \return 
* uint32: An error code with the result of the conversion procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Gyr_radToDeg(GYR_DATA_RAD_F* radData, GYR_DATA_DEG_F* degData){
    /* convert to degrees */
    degData->Wx = to_degrees(radData->Wx);
    degData->Wy = to_degrees(radData->Wy);
    degData->Wz = to_degrees(radData->Wz);
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/* [] END OF FILE */
