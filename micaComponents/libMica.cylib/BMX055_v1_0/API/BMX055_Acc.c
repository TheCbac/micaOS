/***************************************************************************
*                                       MICA
* File: BMX055_Acc.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Bosch BMX055 Accelerometer
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`_Acc.h"
#include "`$i2cIncludeFile`.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_testConnection()
********************************************************************************
*
* \brief Test I2C Connectivity of the accelerometer
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
uint32 `$INSTANCE_NAME`_Acc_testConnection(uint32* i2cError){
    uint8 whoAmI = ZERO;
    /* Read the chip ID register */
    uint32 readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_CHIPID_REG, &whoAmI);
    /* Compare against known who am I */
    if (readError == `$INSTANCE_NAME`_ERR_OK) {
        /* Check the value received */
        if(  whoAmI == `$INSTANCE_NAME`_ACC_CHIPID_VAL) {
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
* Function Name: `$INSTANCE_NAME`_Acc_Reset()
****************************************************************************//**
*
* \brief
*  Initializes the Accelerometer. Meant to be a one time initialization / reset. 
* Use `$INSTANCE_NAME`_Acc_Wakeup if the sensor needs to be woken up from sleep
*
* \param accState
* Pointer to the state of the accelerometer
*
* \return  
* uint32: An error code with the result of the Start procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful Start
*******************************************************************************/
uint32 `$INSTANCE_NAME`_Acc_Reset(`$INSTANCE_NAME`_ACC_STATE_T* accState) {
    /* Initiate Accelerometer software reset */
    uint32 readError = `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_REG, `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_VAL);
    if(readError != `$INSTANCE_NAME`_ERR_OK){ return readError; }
    /* Wait necessary boot time */
    MICA_delayMs(`$INSTANCE_NAME`_ACC_BGW_SOFTRESET_MS);
    /* Set state values to the default */
    accState->powerState = `$INSTANCE_NAME`_ACC_PM_NORMAL;
    accState->scale = `$INSTANCE_NAME`_ACC_RANGE_2G_GAIN;
    accState->channels.X = true;
    accState->channels.Y = true;
    accState->channels.Z = true;
    /* Return Success */
    return `$INSTANCE_NAME`_ERR_OK;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_SetPowerMode()
****************************************************************************//**
*
* \brief
*  Puts the Accelerometer into the low power mode specified.
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
uint32 `$INSTANCE_NAME`_Acc_SetPowerMode(`$INSTANCE_NAME`_ACC_STATE_T* accState, `$INSTANCE_NAME`_ACC_POWER_T powerMode){
    uint8 powerRegVal;
    uint32 writeError;
    /* Current state */
    switch(accState->powerState){
        case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
            /* Normal to Next state */
            switch(powerMode){
                /* Place device in standby mode (SUSPEND + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_STANDBY: {
                    /* Set the lowpower bit in the LP register */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Prepare to place in Suspend mode */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;   
                }
                /* Place device in Low Power 1 mode (LOW_POWER + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_LP1:{
                    /* Clear the lowpower bit in the LP register (@TODO: Should read and then clear) */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG, ZERO);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Prepare for low power mode */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Low Power 2 mode (LOW_POWER + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_LP2:{
                    /* Set the lowpower bit in the LP register (@TODO: Should read and then Set) */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG,\
                                        `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Prepare for low power mode */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Suspend mode (SUSPEND + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Clear the lowpower bit in the LP register (@TODO: Should read and then clear) */
                    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG, ZERO);
                    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
                    /* Prepare for suspend */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_ACC_PM_NORMAL */
        case `$INSTANCE_NAME`_ACC_PM_STANDBY:{
            /* Standby to Next state */
            switch(powerMode){
                /* Exit Standby (NORMAL) */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in Low Power 2 mode (LOW_POWER + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_LP2:{
                    /* Prepare for low power mode (Low Power bit is already set in standby) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /* End `$INSTANCE_NAME`_ACC_PM_STANDBY */
        case `$INSTANCE_NAME`_ACC_PM_LP1:{
            /* Low Power 1 to Next state */
            switch(powerMode){
                /* Exit LP1 to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in SUSPEND mode (SUSPEND + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Prepare for low power mode (Low Power bit is already cleared in LP1) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_LP1 */
        case `$INSTANCE_NAME`_ACC_PM_LP2:{
            /* Low Power 2 to Next state */
            switch(powerMode){
                /* Exit LP2 to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in STANDBY mode (LowPower_En + LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Prepare for low power mode (Low Power bit is already set in LP2) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_LP2 */
        case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
            /* Suspend to Next state */
            switch(powerMode){
                /* Exit LP2 to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Place device in LP1 mode (LowPower_En + !LowPower Bit) */
                case `$INSTANCE_NAME`_ACC_PM_SUSPEND:{
                    /* Prepare for low power mode (Low Power bit is already cleared in LP1) */
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN;
                    break;
                }
                /* Place device in Deep Suspend mode (DEEP_SUSPEND) */
                case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND; 
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_SUSPEND */
        case `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND:{
            /* Deep Suspend to Next state */
            switch(powerMode){
                /* Exit Deep Suspend to NORMAL */
                case `$INSTANCE_NAME`_ACC_PM_NORMAL:{
                    powerRegVal = `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL;
                    break;
                }
                /* Invalid Power state */
                default:{
                    return `$INSTANCE_NAME`_ERR_MODE_INVALID;
                }
            }
            break;
        } /*End `$INSTANCE_NAME`_ACC_PM_DEEP_SUSPEND */
        /* Unknown state */
        default:{
            return `$INSTANCE_NAME`_ERR_MODE_UNKNOWN;
        }
    }
    /* Write to the low power register value selected from above */
    writeError = `$i2cWriteFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_PMU_LPW_REG, powerRegVal);
    if(writeError != `$INSTANCE_NAME`_ERR_OK){return `$INSTANCE_NAME`_ERR_I2C;}
    /* Update the state (valid if reached this point) */
    accState->powerState = powerMode;
    /* Return Success */
    return `$INSTANCE_NAME`_ERR_OK;
}



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Read()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Accelerometer. Places result into the dataArray
*
* \param state
*  Pointer to the state of the accelerometer
*
* \param accData
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
uint32 `$INSTANCE_NAME`_Acc_Read(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* accData){
    /* Check the power state of the device */
    switch(state->powerState){
        /* Valid modes */
        case `$INSTANCE_NAME`_ACC_PM_NORMAL:
        case `$INSTANCE_NAME`_ACC_PM_STANDBY:
        case `$INSTANCE_NAME`_ACC_PM_LP1:
        case `$INSTANCE_NAME`_ACC_PM_LP2:
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
    /* Read in the accelerometer data */
    uint8 msb = ZERO;
    uint8 lsb = ZERO;
    uint32 readError;
    /************** X Channel **************/
    if(chans.X){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_X_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Convert from base 12 two's comp to base 16 and Write X value */
        accData->Ax = `$INSTANCE_NAME`_twosCompToBase16(TWELVE, (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    }
    /************** Y Channel **************/
    if(chans.Y){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Y_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Convert from base 12 two's comp to base 16 and Write Y value */
        accData->Ay = `$INSTANCE_NAME`_twosCompToBase16(TWELVE, (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    }
    /************** Z Channel **************/
    if(chans.Z){
        /* Read the LSB first to lock MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_LSB, &lsb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Read the MSB */
        readError = `$i2cReadFunction`(`$INSTANCE_NAME`_ACC_ADDR, `$INSTANCE_NAME`_ACC_Z_MSB, &msb);
        if (readError != `$INSTANCE_NAME`_ERR_OK ) {return readError;}
        /* Convert from base 12 two's comp to base 16 and Write Y value */
        accData->Az = `$INSTANCE_NAME`_twosCompToBase16(TWELVE, (msb << SHIFT_BYTE_HALF) | ((lsb >> SHIFT_BYTE_HALF) & MASK_NIBBLE_LOW) );
    }
    /***************************************/
    /* Indicate success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Readf()
****************************************************************************//**
*
* \brief
*  Reads the specified channels of the Accelerometer and converts to a floating
*  point number.
*
* \param state
*  Pointer to the state of the Accelerometer\
*
* \param accData
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
uint32 `$INSTANCE_NAME`_Acc_Readf(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_F* accData){
    /* Read from the device */
    ACC_DATA_T accIntData;
    uint32 readError = `$INSTANCE_NAME`_Acc_Read(state, &accIntData);
    if(readError != `$INSTANCE_NAME`_ERR_OK) {return readError;}
    /* Convert to a float */
    readError = `$INSTANCE_NAME`_Acc_Int2Float(state, &accIntData, accData); 
    return readError;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Acc_Int2Float
****************************************************************************//**
*
* \brief
*  Converts an accelerometer data sample from int16 to float type. 
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
uint32 `$INSTANCE_NAME`_Acc_Int2Float(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* intData, ACC_DATA_F* floatData){
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the accelerometer */
    float gain = state->scale;
    /* Convert to float */
    if(chans.X){ floatData->Ax = gain * (float) intData->Ax; }
    if(chans.Y){ floatData->Ay = gain * (float) intData->Ay; }
    if(chans.Z){ floatData->Az = gain * (float) intData->Az; }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: ``$INSTANCE_NAME`_Acc_Float2Int(); 
****************************************************************************//**
*
* \brief
*  Converts an accelerometer data sample from float to int16 type. 
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
uint32 `$INSTANCE_NAME`_Acc_Float2Int(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_F* floatData, ACC_DATA_T* intData) {
    /* Extract channels */
    CHANNELS_XYZ_T chans = state->channels;
    /* Ensure at least one channel is enabled  */
    if( (!chans.X) && (!chans.Y) && (!chans.Z) ){
        return `$INSTANCE_NAME`_ERR_CHANNELS_NONE;
    }
    /* Gain of the accelerometer */
    float gain = state->scale;
    /* Convert to int */
    if(chans.X){ intData->Ax = (int16) (floatData->Ax / gain); }
    if(chans.Y){ intData->Ay = (int16) (floatData->Ay / gain); }
    if(chans.Z){ intData->Az = (int16) (floatData->Az / gain); }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/* [] END OF FILE */
