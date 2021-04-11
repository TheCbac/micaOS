/***************************************************************************
*                                       MICA
* File: BMX055_Mag.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 Magnetometer
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`_Mag.h"
#include "`$i2cIncludeFile`.h"
#include "`$INSTANCE_NAME`_Common.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_testConnection()
********************************************************************************
*
* \brief Test I2C Connectivity of the Magnetometer. This can only be read if 
*   the magnetometer is enabled, i.e. not in Susend mode
* 
* \param i2cError
*   Pointer to variable to pass out the I2C Error
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
uint32 `$INSTANCE_NAME`_Mag_testConnection(uint32* i2cError){
    uint8 whoAmI = ZERO;
    /* Read the chip ID register */
    uint32 readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_CHIPID_REG, &whoAmI);
    /* Compare against known who am I */
    if (readError == `$INSTANCE_NAME`_ERR_OK) {
        /* Check the value received */
        if(  whoAmI == `$INSTANCE_NAME`_MAG_CHIPID_VAL) {
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
* Function Name: `$INSTANCE_NAME`_Mag_Reset()
****************************************************************************//**
*
* \brief
*  Initializes the magnetometer. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Mag_Wakeup if the sensor needs to be woken up from sleep
*
*
* \return  
* uint32: An error code with the result of the Start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Start
*******************************************************************************/
 uint32 `$INSTANCE_NAME`_Mag_Reset(`$INSTANCE_NAME`_MAG_STATE_T* magState){
    /* Place into Suspend Mode */
    uint32 readError = `$i2cWriteFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_CONTROL_REG, ZERO);
    if(readError != `$INSTANCE_NAME`_ERR_OK){ return readError; }
    /* Bring into sleep Mode */
    readError = `$i2cWriteFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_CONTROL_REG, `$INSTANCE_NAME`_MAG_CONTROL_PWR_CTRL);
    if(readError != `$INSTANCE_NAME`_ERR_OK){ return readError; }
    /* Wait necessary boot time */
    MICA_delayMs(`$INSTANCE_NAME`_MAG_CONTROL_WAKEUP_MS);
    
    /* Set state values to the default */
    magState->powerState = `$INSTANCE_NAME`_MAG_PM_SLEEP;
    magState->scale = `$INSTANCE_NAME`_MAG_GAIN;
    magState->channels.X = true;
    magState->channels.Y = true;
    magState->channels.Z = true;
    /* Return Success  */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_SetPowerMode()
****************************************************************************//**
*
* \brief
*  Puts the Magnetometer into the low power mode specified.
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
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_SetPowerMode(`$INSTANCE_NAME`_MAG_STATE_T* magState, `$INSTANCE_NAME`_MAG_POWER_T powerMode){
    uint8 powerRegVal;
    uint32 writeError;
    bool queueWrite = true;
    /* Act according to the current state */
    switch(magState->powerState){
        case `$INSTANCE_NAME`_MAG_PM_SUSPEND:{
            /* Suspend to next state (only sleep) */
            switch(powerMode){
                /* Suspend mode to sleep mode */
                case `$INSTANCE_NAME`_MAG_PM_SLEEP:{
                    /* Write the power control bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_CONTROL_REG, `$INSTANCE_NAME`_MAG_CONTROL_PWR_CTRL);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Dequeue Op write */
                    queueWrite = false;
                    break;    
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;   
                }
            }
            break;
        }  /* End `$INSTANCE_NAME`_MAG_PM_SUSPEND */
        case `$INSTANCE_NAME`_MAG_PM_SLEEP:{
            /* Sleep to Next State */
            switch(powerMode){
                /* Sleep to suspend */
                case `$INSTANCE_NAME`_MAG_PM_SUSPEND:{
                    /* Clear the power control bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_CONTROL_REG, ZERO);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Dequeue Op write */
                    queueWrite = false;
                    break;     
                }
                /* Sleep to Normal */
                case `$INSTANCE_NAME`_MAG_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_MAG_OPS_MODE_NORMAL;
                    break;    
                }
                /* Sleep to Forced */
                case `$INSTANCE_NAME`_MAG_PM_FORCED:{
                    /* forced mode is one shot, go back to sleep */
                    powerRegVal = `$INSTANCE_NAME`_MAG_OPS_MODE_FORCED;
                    break;    
                }
                 /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;   
                }   
            }
            break;
        } /* End `$INSTANCE_NAME`_MAG_PM_SLEEP */
        case `$INSTANCE_NAME`_MAG_PM_NORMAL:{
            /* Normal to next state */
            switch(powerMode){ 
                /* Normal to suspend */
                case `$INSTANCE_NAME`_MAG_PM_SUSPEND:{
                    /* Clear the power control bit */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_CONTROL_REG, ZERO);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Dequeue Op write */
                    queueWrite = false;
                    break;     
                }
                /* Normal to sleep */
                case `$INSTANCE_NAME`_MAG_PM_SLEEP:{
                    powerRegVal = `$INSTANCE_NAME`_MAG_OPS_MODE_SLEEP;
                    break;    
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;   
                }
            }
            break;    
        } /* End `$INSTANCE_NAME`_MAG_PM_NORMAL */
        case `$INSTANCE_NAME`_MAG_PM_FORCED:{
            /* Forced mode is a One shot mode - after one measurement the device immediatly goes back to sleep */
            switch(powerMode){
                case `$INSTANCE_NAME`_MAG_PM_SLEEP:{
                    /* Automatic, nothing to do */
                    queueWrite = false;
                    break;
                }
                /* Invalid state transition */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;   
                }
            }
        }
        /* Unknown Power state */
        default:{
            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN;
        }
    }
    /* Write to the low power register value selected from above */
    if(queueWrite){
        writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_OPS_REG, powerRegVal);
        if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
    }
    /* Update the state (valid if reached this point) */
    magState->powerState = powerMode;
    /* If mode was forced, go back to sleep */
    if(powerMode == `$INSTANCE_NAME`_MAG_PM_FORCED) {
        return `$INSTANCE_NAME`_Mag_SetPowerMode(magState, `$INSTANCE_NAME`_MAG_PM_SLEEP);
    }
    /* Return Success */
    return `$INSTANCE_NAME`_ERR_OK;
}
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the magnetometer. Places result into the dataArray
*
* \param state
*  Pointer to the state of the Magnetometer
*
* \param magData
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
*   `$INSTANCE_NAME`_ERR_MODE_INVALID       | Device is in an invalid state
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Mag_Read(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_T* magData){
    /* Check the power state of the device */
    switch(state->powerState){
        /* Valid modes */
        case `$INSTANCE_NAME`_MAG_PM_NORMAL:
        case `$INSTANCE_NAME`_MAG_PM_FORCED:
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
    /* Read in the magelerometer data */
    uint8 msb = ZERO;
    uint8 lsb = ZERO;
    uint32 readError;
    /************** X Channel **************/
    if(chans.X){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_X_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_X_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Convert from base 13 two's comp to base 16 and Write X value */
        magData->X = `$INSTANCE_NAME`_twosCompToBase16(THIRTEEN, (msb << SIX) | (lsb >> THREE) );
    }
    /************** Y Channel **************/
    if(chans.Y){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Y_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Y_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Convert from base 13 two's comp to base 16 and Write Y value */
        magData->Y = `$INSTANCE_NAME`_twosCompToBase16(THIRTEEN, (msb << SIX) | (lsb >> THREE) );
    }
    /************** Z Channel **************/
    if(chans.Z){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Z_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_MAG_ADDR, `$INSTANCE_NAME`_MAG_Z_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Convert from base 13 two's comp to base 16 and Write Y value */
        magData->Z = `$INSTANCE_NAME`_twosCompToBase16(THIRTEEN, (msb << SIX) | (lsb >> THREE) );
    }
    /***************************************/
    /* Indicate success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Readf()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Accelerometer and converts to a floating
*  point number.
*
* \param state
*  Pointer to the state of the Accelerometer\
*
* \param magData
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
uint32 `$INSTANCE_NAME`_Mag_Readf(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_F* magData){
    /* Read from the device */
    MAG_DATA_T magIntData;
    uint32 readError = `$INSTANCE_NAME`_Mag_Read(state, &magIntData);
    if(readError != `$INSTANCE_NAME`_ERR_OK) {return readError;}
    /* Convert to a float */
    readError = `$INSTANCE_NAME`_Mag_Int2Float(state, &magIntData, magData); 
    return readError;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Mag_Int2Float
****************************************************************************//**
*
* \brief
*  Converts an magnetometer data sample from int16 to float type. 
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
uint32 `$INSTANCE_NAME`_Mag_Int2Float(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_T* intData, MAG_DATA_F* floatData){
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the magnetometer */
    float gain = state->scale;
    /* Convert to float */
    if(chans.X){ floatData->X = gain * (float) intData->X; }
    if(chans.Y){ floatData->Y = gain * (float) intData->Y; }
    if(chans.Z){ floatData->Z = gain * (float) intData->Z; }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Mag_Float2Int(); 
****************************************************************************//**
*
* \brief
*  Converts an magnetometer data sample from float to int16 type. 
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
uint32 `$INSTANCE_NAME`_Mag_Float2Int(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_F* floatData, MAG_DATA_T* intData) {
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    /* Ensure at least one channel is enabled  */
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the magnetometer */
    float gain = state->scale;
    /* Convert to int */
    if(chans.X){ intData->X = (int16) (floatData->X / gain); }
    if(chans.Y){ intData->Y = (int16) (floatData->Y / gain); }
    if(chans.Z){ intData->Z = (int16) (floatData->Z / gain); }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/* [] END OF FILE */
