/***************************************************************************
*                                       MICA
* File: BMX055_Mag.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for interacting with the Bosch BMX055 Magnetometer
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_MAG_H
    #define `$INSTANCE_NAME`_MAG_H
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
    /* Magnetometer definitions used across the entire device */
    #define `$INSTANCE_NAME`_MAG_ADDR            (0x10u)     /**< I2C Address of the Magnetometer */
    #define `$INSTANCE_NAME`_MAG_CHIPID_REG      (0x40u)     /**< Address of the Magnetometer chip id register */
    #define `$INSTANCE_NAME`_MAG_CHIPID_VAL      (0x32u)     /**< Value of the Magnetometer chip id */
    #define `$INSTANCE_NAME`_MAG_X_MSB           (0x43u)     /**< Magnetometer register address of the X-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_MAG_X_LSB           (0x42u)     /**< Magnetometer register address of the X-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Y_MSB           (0x45u)     /**< Magnetometer register address of the Y-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Y_LSB           (0x44u)     /**< Magnetometer register address of the Y-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Z_MSB           (0x47u)     /**< Magnetometer register address of the Z-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_MAG_Z_LSB           (0x46u)     /**< Magnetometer register address of the Z-axis Least Significant Byte */
    
    /***********************************************
    * magnetometer definitions used setting the digital filters,
    * Ordinary Data Rate (ODR), and power management on the device
    * *********************************************/

    /* Sets the power mode of the Magnetometer */
    #define `$INSTANCE_NAME`_MAG_CONTROL_REG                (0x4Bu)     /**< Address of the Magnetometer Power Control register */
    #define `$INSTANCE_NAME`_MAG_CONTROL_PWR_CTRL_POS       (0u)     /**< Position of the Power control bit */
    #define `$INSTANCE_NAME`_MAG_CONTROL_RESET_1_POS        (1u)     /**< Position of one of the two soft reset bit */
    #define `$INSTANCE_NAME`_MAG_CONTROL_SPI3_POS           (2u)     /**< Position of one of the two soft reset bit */
    #define `$INSTANCE_NAME`_MAG_CONTROL_RESET_2_POS        (7u)     /**< Position of second of the two soft reset bit */
    #define `$INSTANCE_NAME`_MAG_CONTROL_PWR_CTRL           (1u << `$INSTANCE_NAME`_MAG_CONTROL_PWR_CTRL_POS)    /**< Mask of the Power control bit */
    #define `$INSTANCE_NAME`_MAG_CONTROL_RESET              ((1u << `$INSTANCE_NAME`_MAG_CONTROL_RESET_1_POS) & (1u << `$INSTANCE_NAME`_MAG_CONTROL_RESET_2_POS)) /**< Mask of the Power control bit */
    #define `$INSTANCE_NAME`_MAG_CONTROL_SPI3               (1u << `$INSTANCE_NAME`_MAG_CONTROL_SPI3_POS)     /**<Enable SPI1 */                
    #define `$INSTANCE_NAME`_MAG_CONTROL_WAKEUP_MS          (4u) /**< Wakeup time from suspend to sleep in ms */
    /* Sets the Operation mode, output rate and self-test */
    #define `$INSTANCE_NAME`_MAG_OPS_REG                        (0x4Cu)     /**< Address of the Magnetometer Operation Control register */
    #define `$INSTANCE_NAME`_MAG_OPS_SELF_TEST_POS              (0u)        /**< Position of the self test bit */
    #define `$INSTANCE_NAME`_MAG_OPS_MODE_POS                   (1u)        /**< Position of the Opmode */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_POS                   (3u)        /**< Position of the Data Rate */
    #define `$INSTANCE_NAME`_MAG_OPS_ADV_ST_POS                 (6u)        /**< Position of the Advanced Self test control */
    #define `$INSTANCE_NAME`_MAG_OPS_MODE_NORMAL                (0u)        /**< Normal mode */
    #define `$INSTANCE_NAME`_MAG_OPS_MODE_FORCED                (0b01 << `$INSTANCE_NAME`_MAG_OPS_MODE_POS)     /**< Forced mode */
    #define `$INSTANCE_NAME`_MAG_OPS_MODE_SLEEP                 (0b11 << `$INSTANCE_NAME`_MAG_OPS_MODE_POS)     /**< Sleep mode */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_10                 (0b000 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 10 Hz Ordinary Data Rate (ODR) */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_2                  (0b001 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 2 Hz Ordinary Data Rate (ODR)  */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_6                  (0b010 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 6 Hz Ordinary Data Rate (ODR)  */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_8                  (0b011 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 8 Hz Ordinary Data Rate (ODR)  */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_15                 (0b100 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 15 Hz Ordinary Data Rate (ODR)  */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_20                 (0b101 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 20 Hz Ordinary Data Rate (ODR)  */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_25                 (0b110 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 25 Hz Ordinary Data Rate (ODR)  */
    #define `$INSTANCE_NAME`_MAG_OPS_RATE_HZ_30                 (0b111 << `$INSTANCE_NAME`_MAG_OPS_RATE_POS)    /**< 30 Hz Ordinary Data Rate (ODR)  */
    /* Gain of the system */
    #define `$INSTANCE_NAME`_MAG_GAIN    (0.0625f)   /**< Magnetometer [uT/LSB] (unclear from datasheet if this is actually the correct gain) */
    
    /***************************************
    *        Function Prototypes
    ***************************************/
    /* Magnetometer specific functions */
    uint32 `$INSTANCE_NAME`_Mag_testConnection(uint32* i2cError);          /**< Test basic I2C contact with magnetometer */
    uint32 `$INSTANCE_NAME`_Mag_Reset(`$INSTANCE_NAME`_MAG_STATE_T* magState);    /**< Start the Magoscope*/
    uint32 `$INSTANCE_NAME`_Mag_SetPowerMode(`$INSTANCE_NAME`_MAG_STATE_T* magState, `$INSTANCE_NAME`_MAG_POWER_T powerMode);    /**< Put the Magscope into the specified power mode */
    uint32 `$INSTANCE_NAME`_Mag_Read(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_T* magData);                                            /**< Read data from the magoscope */
    uint32 `$INSTANCE_NAME`_Mag_Readf(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_F* magoData);      /**< Read the value of the Magoscope in float*/
    uint32 `$INSTANCE_NAME`_Mag_Int2Float(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_T* intData, MAG_DATA_F* floatData);     /**< Converts the Mago int type to float type*/
    uint32 `$INSTANCE_NAME`_Mag_Float2Int(`$INSTANCE_NAME`_MAG_STATE_T* state, MAG_DATA_F* floatData, MAG_DATA_T* intData);     /**< Converts the mago float type to int type*/
    
#endif /* `$INSTANCE_NAME`_MAG_H */
/* [] END OF FILE */
