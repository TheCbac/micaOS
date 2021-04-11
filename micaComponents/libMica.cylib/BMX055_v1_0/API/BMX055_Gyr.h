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
/* Header Guard */
#ifndef `$INSTANCE_NAME`_GYR_H
    #define `$INSTANCE_NAME`_GYR_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"
    #include "micaCommon.h"
    #include "`$INSTANCE_NAME`_Common.h"
    
    /***************************************
    * Enumerated Types
    ***************************************/

    /***************************************
    * Structs
    ***************************************/

    
    /***************************************
    * Macro Definitions
    ***************************************/
    /* Gyroscope definitions used across the entire device */
    #define `$INSTANCE_NAME`_GYR_ADDR            (0x69u)     /**< I2C Address of the gyroscope */
    #define `$INSTANCE_NAME`_GYR_CHIPID_REG      (0x00u)     /**< Address of the gyroscope chip id register */
    #define `$INSTANCE_NAME`_GYR_CHIPID_VAL      (0x0Fu)     /**< Value of the gyroscope chip id */
    #define `$INSTANCE_NAME`_GYR_X_MSB           (0x03u)     /**< Gyroscope register address of the X-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_GYR_X_LSB           (0x02u)     /**< Gyroscope register address of the X-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_GYR_Y_MSB           (0x05u)     /**< Gyroscope register address of the Y-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_GYR_Y_LSB           (0x04u)     /**< Gyroscope register address of the Y-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_GYR_Z_MSB           (0x07u)     /**< Gyroscope register address of the Z-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_GYR_Z_LSB           (0x06u)     /**< Gyroscope register address of the Z-axis Least Significant Byte */

    /***********************************************
    * Gyroscope definitions used setting the digital filters,
    * Ordinary Data Rate (ODR), and power management on the device
    * *********************************************/
    /* Controls the range of the Gyroscope */
    #define `$INSTANCE_NAME`_GYR_RANGE_REG          (0x0Fu)     /**< Address of the range Register*/
    #define `$INSTANCE_NAME`_GYR_RANGE_2000         (0x00u)      /**< Value that corresponds to ± 2000°/s */
    #define `$INSTANCE_NAME`_GYR_RANGE_1000         (0x01u)      /**< Value that corresponds to ± 1000°/s */
    #define `$INSTANCE_NAME`_GYR_RANGE_500          (0x02u)      /**< Value that corresponds to ±  500°/s */
    #define `$INSTANCE_NAME`_GYR_RANGE_250          (0x03u)      /**< Value that corresponds to ±  250°/s */
    #define `$INSTANCE_NAME`_GYR_RANGE_125          (0x04u)      /**< Value that corresponds to ±  125°/s */
    #define `$INSTANCE_NAME`_GYR_RANGE_2000_GAIN    (0.0610f)   /**< Gyr gain of the ± 2000°/s setting [°/s/LSB] */
    #define `$INSTANCE_NAME`_GYR_RANGE_1000_GAIN    (0.0305f)   /**< Gyr gain of the ± 1000°/s setting [°/s/LSB] */
    #define `$INSTANCE_NAME`_GYR_RANGE_500_GAIN     (0.0153f)   /**< Gyr gain of the ±  500°/s setting [°/s/LSB] */
    #define `$INSTANCE_NAME`_GYR_RANGE_250_GAIN     (0.0076f)   /**< Gyr gain of the ±  250°/s setting [°/s/LSB] */   
    #define `$INSTANCE_NAME`_GYR_RANGE_125_GAIN     (0.0038f)   /**< Gyr gain of the ±  125°/s setting [°/s/LSB] */ 
    /* Sets the bandwidth and Ordinary Data rate of the gyroscope */
    #define `$INSTANCE_NAME`_GYR_BW_REG          (0x10u)     /**< Address of the gyroscope chip id */
    #define `$INSTANCE_NAME`_GYR_BW_2000_523     (0x00u)     /**< Value of 2000 Hz ODR and 523 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_2000_230     (0x01u)     /**< Value of 2000 Hz ODR and 230 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_1000_116     (0x02u)     /**< Value of 1000 Hz ODR and 116 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_400_47       (0x03u)     /**< Value of 400 Hz ODR and 47 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_200_23       (0x04u)     /**< Value of 200 Hz ODR and 23 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_100_12       (0x05u)     /**< Value of 100 Hz ODR and 12 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_200_64       (0x06u)     /**< Value of 200 Hz ODR and 64 Hz Filter Bandwidth */
    #define `$INSTANCE_NAME`_GYR_BW_100_32       (0x07u)     /**< Value of 100 Hz ODR and 32 Hz Filter Bandwidth */
    /* Sets the power mode of the gyroscope */
    #define `$INSTANCE_NAME`_GYR_LPM1_REG                (0x11u)      /**< Address of the power selection Reg */
    #define `$INSTANCE_NAME`_GYR_LPM1_SUSPEND_POS        (7u)        /**< Position for "Suspend" mode bit */
    #define `$INSTANCE_NAME`_GYR_LPM1_DEEP_SUSPEND_POS   (5u)        /**< Position for "Deep Suspend" bit */
    #define `$INSTANCE_NAME`_GYR_LPM1_SUSPEND            (1u << `$INSTANCE_NAME`_GYR_LPM1_SUSPEND_POS)        /**< Mask for "Suspend" mode */
    #define `$INSTANCE_NAME`_GYR_LPM1_DEEP_SUSPEND       (1u << `$INSTANCE_NAME`_GYR_LPM1_DEEP_SUSPEND_POS)   /**< Mask for "Deep Suspend" mode */
    #define `$INSTANCE_NAME`_GYR_LPM1_NORMAL             (0u)                                    /**< Mask for "Normal" mode */
    /* Fast Powerup and external trigger */
    #define `$INSTANCE_NAME`_GYR_LPM2_REG                   (0x12u)     /**< Address of the Low Power 2 Reg */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS     (0u)        /**< Position for LSB of autosleep duration */
    #define `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_POS      (4u)        /**< Position for the LSB of external trigger selection */
    #define `$INSTANCE_NAME`_GYR_LPM2_POWER_SAVE_MODE_POS   (6u)        /**< Position for the Power Save mode bit */
    #define `$INSTANCE_NAME`_GYR_LPM2_FAST_POWERUP_POS      (7u)        /**< Position for the Fast powerup bit */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_4_MS    (0b001 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 4 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_5_MS    (0b010 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 5 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_8_MS    (0b011 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 8 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_10_MS   (0b100 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 10 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_15_MS   (0b101 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 15 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_20_MS   (0b110 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 20 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_40_MS   (0b111 << `$INSTANCE_NAME`_GYR_LPM2_AUTOSLEEP_DUR_POS)  /**< Value for 40 ms second auto sleep */
    #define `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_INT1     (0b01 << `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_POS)    /**< Value for INT1 as EXT */
    #define `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_INT2     (0b10 << `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_POS)    /**< Value for INT2 as EXT */
    #define `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_SDO      (0b11 << `$INSTANCE_NAME`_GYR_LPM2_EXT_TRIG_SEL_POS)    /**< Value for SDO pin (SPI3 mode)*/
    #define `$INSTANCE_NAME`_GYR_LPM2_POWER_SAVE_MODE       (1u << `$INSTANCE_NAME`_GYR_LPM2_POWER_SAVE_MODE_POS)   /**< Value for the Power Save mode bit */
    #define `$INSTANCE_NAME`_GYR_LPM2_FAST_POWERUP          (1u << `$INSTANCE_NAME`_GYR_LPM2_FAST_POWERUP_POS)      /**< Value for the Fast powerup bit */
    /* Soft Reset Register */
    #define `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_REG       (0x14u)     /**< Address of the soft reset register */
    #define `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_VAL       (0xB6u)     /**< Value that initiates a soft reset */
    #define `$INSTANCE_NAME`_GYR_BGW_SOFTRESET_MS        (1u)       /** Delay in ms for gyroscope boot (Unverified) */
    /***************************************
    * Function Prototypes
    ***************************************/
    uint32 `$INSTANCE_NAME`_Gyr_testConnection(uint32* i2cError);          /**< Test basic I2C contact with Gyroscope */
    uint32 `$INSTANCE_NAME`_Gyr_Reset(`$INSTANCE_NAME`_GYR_STATE_T* gyrState);    /**< Start the Gyroscope*/
    uint32 `$INSTANCE_NAME`_Gyr_SetPowerMode(`$INSTANCE_NAME`_GYR_STATE_T* gyrState, `$INSTANCE_NAME`_GYR_POWER_T powerMode);    /**< Put the Gyrscope into the specified power mode */
    uint32 `$INSTANCE_NAME`_Gyr_Read(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_T* gyrData);                                            /**< Read data from the gyroscope */
    uint32 `$INSTANCE_NAME`_Gyr_Readf_deg(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_DEG_F* gyroDegData);      /**< Read the value of the Gyroscope in float [deg/s]*/
    uint32 `$INSTANCE_NAME`_Gyr_Readf_rad(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_RAD_F* gyrRadData);      /**< Read the value of the Gyroscope in float [rad/s]*/
    
    uint32 `$INSTANCE_NAME`_Gyr_Int2FloatDeg(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_T* intData, GYR_DATA_DEG_F* floatData);     /**< Converts the Gyro int type to float type [deg/s]*/
    uint32 `$INSTANCE_NAME`_Gyr_FloatDeg2Int(`$INSTANCE_NAME`_GYR_STATE_T* state, GYR_DATA_DEG_F* floatData, GYR_DATA_T* intData);     /**< Converts the gyro float type [deg/s] to int type */
    uint32 `$INSTANCE_NAME`_Gyr_degToRad(GYR_DATA_DEG_F* degData, GYR_DATA_RAD_F* radData);
    uint32 `$INSTANCE_NAME`_Gyr_radToDeg(GYR_DATA_RAD_F* radData, GYR_DATA_DEG_F* degData);
    
    
#endif /* `$INSTANCE_NAME`_GYR_H */

/* [] END OF FILE */
