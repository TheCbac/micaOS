/***************************************************************************
*                                       MICA
* File: BMX055_Acc.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for interacting with the Bosch BMX055 Accelerometer
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.06.04 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_ACC_H
    #define `$INSTANCE_NAME`_ACC_H
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
     /* Accelerometer definitions used across the entire device */
    #define `$INSTANCE_NAME`_ACC_ADDR            (0x18u)     /**< I2C Address of the accelerometer */
    #define `$INSTANCE_NAME`_ACC_CHIPID_REG      (0x00u)     /**< Chip ID Register address of the accelerometer */
    #define `$INSTANCE_NAME`_ACC_CHIPID_VAL      (0xFAu)     /**< Chip ID value of the accelerometer */
    #define `$INSTANCE_NAME`_ACC_X_MSB           (0x03u)     /**< Accelerometer register address of the X-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_ACC_X_LSB           (0x02u)     /**< Accelerometer register address of the X-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_ACC_Y_MSB           (0x05u)     /**< Accelerometer register address of the Y-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_ACC_Y_LSB           (0x04u)     /**< Accelerometer register address of the Y-axis Least Significant Byte */
    #define `$INSTANCE_NAME`_ACC_Z_MSB           (0x07u)     /**< Accelerometer register address of the Z-axis Most Significant Byte */
    #define `$INSTANCE_NAME`_ACC_Z_LSB           (0x06u)     /**< Accelerometer register address of the Z-axis Least Significant Byte */

    /***********************************************
     *  Accelerometer definitions used for interrupts 
     * *********************************************/

    /**
    * Interrupt Status Register 0 contains interrupt status flags,
    * including Single & double tap, orientation, freefall, and high-G interrupts
    **/
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_0_REG            (0x09u) /**< Address of the accelerometer Interrupt Status Register 0 */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_0_D_TAP_INT_POS  (4u)    /**< Position of the Double tap enable bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_0_S_TAP_INT_POS  (5u)    /**< Position of the Single tap enable bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_0_D_TAP_INT      (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_0_D_TAP_INT_POS)  /**< Mask of the Double tap enable bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_0_S_TAP_INT      (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_0_S_TAP_INT_POS)  /**< Mask of the Single tap enable bit */
    /* Interupt Status Register 1 controls interrupts with the other 2 status registers */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_1_REG            (0x0Au) /**< Address of the accelerometer Interrupt Status Register 1 */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_1_DATA_INT_POS   (3u)    /**< Position of the data ready interrupt status bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_1_DATA_INT       (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_1_DATA_INT_POS)  /**< Mask of the data ready interrupt status bit */
    /* Interupt Status Register 2 contains the status of the single/double tap & slope interrupt sources */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_REG                (0x0Bu) /**< Address of the accelerometer Interrupt Status Register 2 */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_X_POS    (4u)    /**< Position of the Tap X bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_Y_POS    (5u)    /**< Position of the Tap Y bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_Z_POS    (6u)    /**< Position of the Tap Z bit */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_SIGN_POS       (7u)    /**< Position of the Tap sign bit - indicates the sign of the tap */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_X        (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_X_POS)    /**< Mask of the Tap X bit - indicates that the X axis was tapped first */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_Y        (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_Y_POS)    /**< Mask of the Tap Y bit - indicates that the Y axis was tapped first */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_Z        (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_FIRST_Z_POS)    /**< Mask of the Tap Z bit - indicates that the Z axis was tapped first */
    #define `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_SIGN           (1u << `$INSTANCE_NAME`_ACC_INT_STATUS_2_TAP_SIGN_POS)        /**< Mask of the Tap sign bit - indicates the sign of the tap */
    /* Interupt Engine 0 controls which interrupts in group 0 are enabled such as flat, orientation, taps, and slopes. */
    #define `$INSTANCE_NAME`_ACC_INT_EN_0_REG                (0x16u)     /**< Address of the accelerometer Interrupt Engine Register 1 */
    #define `$INSTANCE_NAME`_ACC_D_TAP_EN_POS                (4u)        /**< Position of the Double Tap interrupt enable bit */
    #define `$INSTANCE_NAME`_ACC_S_TAP_EN_POS                (5u)        /**< Position of the Single Tap interrupt enable bit */
    #define `$INSTANCE_NAME`_ACC_D_TAP_EN                    (1u << `$INSTANCE_NAME`_ACC_D_TAP_EN_POS)    /**< Mask of the Double Tap interrupt enable bit */
    #define `$INSTANCE_NAME`_ACC_S_TAP_EN                    (1u << `$INSTANCE_NAME`_ACC_S_TAP_EN_POS)    /**< Mask of the Single Tap interrupt enable bit */
    /* Interupt Engine 1 controls which interrupts in group 1 are enabled */
    #define `$INSTANCE_NAME`_ACC_INT_EN_1_REG                (0x17u) /**< Address of the accelerometer Interrupt Engine Register 1 */
    #define `$INSTANCE_NAME`_ACC_INT_EN_1_DRDY_POS           (4u)    /**< Position of the Data Ready interrupt enable bit */
    #define `$INSTANCE_NAME`_ACC_INT_EN_1_DRDY               (1u << `$INSTANCE_NAME`_ACC_INT_EN_1_DRDY_POS)    /**< Mask of the Data Ready interrupt */
    /* Interrupt map 0 control which interrupt signals are mapped to the INT1 pin */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_0_REG               (0x19u) /**< Address of the interrupt map 0 register */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_0_INT1_D_TAP_POS    (4u)    /**< Position of the double tap to INT1 interrupt map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_0_INT1_S_TAP_POS    (5u)    /**< Position of the single tap to INT1 interrupt map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_0_INT1_D_TAP        (1u << `$INSTANCE_NAME`_ACC_INT_MAP_0_INT1_D_TAP_POS)    /**< Mask of the double tap to INT1 map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_0_INT1_S_TAP        (1u << `$INSTANCE_NAME`_ACC_INT_MAP_0_INT1_S_TAP_POS)    /**< Mask of the single tap to INT1 map bit */
    /* Interrupt map 1 control which interrupt signals are mapped to the INT1 & INT2 pins */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_1_REG               (0x1Au) /**< Address of the interrupt map 0 register */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_1_INT1_DATA_POS     (0u)    /**< Position of the data ready to INT1 map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_1_INT1_DATA         (1u << `$INSTANCE_NAME`_ACC_INT_MAP_1_INT1_DATA_POS) /**< Map of the data ready to INT1 map bit */
    /* Interrupt map 2 control which interrupt signals are mapped to the INT2 pins */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_2_REG               (0x1Bu) /**< Address of the interrupt map 2 register */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_2_INT2_D_TAP_POS    (4u)    /**< Position of the double tap to INT2 map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_2_INT2_S_TAP_POS    (5u)    /**< Position of the single tap to INT2 map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_2_INT2_D_TAP        (1u << `$INSTANCE_NAME`_ACC_INT_MAP_2_INT2_D_TAP_POS)    /**< Mask of the single tap to INT2 map bit */
    #define `$INSTANCE_NAME`_ACC_INT_MAP_2_INT2_S_TAP        (1u << `$INSTANCE_NAME`_ACC_INT_MAP_2_INT2_S_TAP_POS)    /**< Mask of the double tap to INT2 map bit */
    /* Interrupt Output Control determines the electrical behavior of the interrupt pins */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_REG            (0x20u) /**< Address of the interrupt output control register */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT1_LVL_POS   (0u)    /**< Position of the INT1 active level bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT1_OD_POS    (1u)    /**< Position of the INT1 open drain bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT2_LVL_POS   (2u)    /**< Position of the INT2 active level bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT2_OD_POS    (3u)    /**< Position of the INT2 open drain bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT1_LVL       (1u << `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT1_LVL_POS)   /**< Mask of the INT1 active level bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT1_OD        (1u << `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT1_OD_POS)    /**< Mask of the INT1 open drain bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT2_LVL       (1u << `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT2_LVL_POS)   /**< Mask of the INT2 active level bit */
    #define `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT2_OD        (1u << `$INSTANCE_NAME`_ACC_INT_OUT_CTRL_INT2_OD_POS)    /**< Mask of the INT2 open drain bit */
    /* Interrupt register 8 contains the timing definitions for the single tap and double tap interrupts */
    #define `$INSTANCE_NAME`_ACC_INT_8_REG       (0x2Au)  /**< Address of interrupt register 8 */
    #define `$INSTANCE_NAME`_ACC_TAP_QUIET_POS   (7u)     /**< Position of the tap quiet level selection bit*/
    #define `$INSTANCE_NAME`_ACC_TAP_SHOCK_POS   (6u)     /**< Position of the tap shock level selection bit*/
    #define `$INSTANCE_NAME`_ACC_TAP_QUIET_30MS  (0u << `$INSTANCE_NAME`_ACC_TAP_QUIET_POS)    /**< Mask for setting tap quiet to 30ms */
    #define `$INSTANCE_NAME`_ACC_TAP_QUIET_20MS  (1u << `$INSTANCE_NAME`_ACC_TAP_QUIET_POS)    /**< Mask for setting tap quiet to 20ms */
    #define `$INSTANCE_NAME`_ACC_TAP_SHOCK_50MS  (0u << `$INSTANCE_NAME`_ACC_TAP_SHOCK_POS)    /**< Mask for setting tap shock to 50ms */
    #define `$INSTANCE_NAME`_ACC_TAP_SHOCK_75MS  (1u << `$INSTANCE_NAME`_ACC_TAP_SHOCK_POS)    /**< Mask for setting tap shock to 75ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_50MS    (0x00u)  /**< Mask for setting tap duration to 50ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_100MS   (0x01u)  /**< Mask for setting tap duration to 100ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_150MS   (0x02u)  /**< Mask for setting tap duration to 150ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_200MS   (0x03u)  /**< Mask for setting tap duration to 200ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_250MS   (0x04u)  /**< Mask for setting tap duration to 250ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_375MS   (0x05u)  /**< Mask for setting tap duration to 375ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_500MS   (0x06u)  /**< Mask for setting tap duration to 500ms */
    #define `$INSTANCE_NAME`_ACC_TAP_DUR_700MS   (0x07u)  /**< Mask for setting tap duration to 700ms */
    /** 
    * Interrupt register 9 contains the definitions for the number of samples processed by the single/double
    * tap interrupt engine after wake-up in low-power mode, as well as the threshold definition.
    **/
    #define `$INSTANCE_NAME`_ACC_INT_9_REG       (0x2Bu)  /**< Address of interrupt register 9 */
    #define `$INSTANCE_NAME`_ACC_TAP_SAMP_POS    (6u)     /**< Position of the number of tap samples LSB*/
    #define `$INSTANCE_NAME`_ACC_TAP_SAMP_2      (0x00 << `$INSTANCE_NAME`_ACC_TAP_SAMP_POS)   /**< Value for setting the number of tap samples to 2 */
    #define `$INSTANCE_NAME`_ACC_TAP_SAMP_4      (0x01 << `$INSTANCE_NAME`_ACC_TAP_SAMP_POS)   /**< Value for setting the number of tap samples to 4 */
    #define `$INSTANCE_NAME`_ACC_TAP_SAMP_8      (0x02 << `$INSTANCE_NAME`_ACC_TAP_SAMP_POS)   /**< Value for setting the number of tap samples to 8 */
    #define `$INSTANCE_NAME`_ACC_TAP_SAMP_16     (0x03 << `$INSTANCE_NAME`_ACC_TAP_SAMP_POS)   /**< Value for setting the number of tap samples to 16 */
    #define `$INSTANCE_NAME`_ACC_TAP_TH_5_MPS2   (0x08u)  /**< Value for setting the tap Threshold ** Range dependent ** */
    #define `$INSTANCE_NAME`_ACC_TAP_TH_6_MPS2   (0x0Au)  /**< Value for setting the tap Threshold ** Range dependent ** */
    #define `$INSTANCE_NAME`_ACC_TAP_TH_7_MPS2   (0x0Cu)  /**< Value for setting the tap Threshold ** Range dependent ** */
    #define `$INSTANCE_NAME`_ACC_TAP_TH_9_MPS2   (0x0Fu)  /**< Value for setting the tap Threshold ** Range dependent ** */
    #define `$INSTANCE_NAME`_ACC_TAP_TH_MAX      (0x1Fu)  /**< Value for setting the tap Threshold ** Range dependent ** */

    /***********************************************
    * Accelerometer definitions used setting the digital filters,
    * Ordinary Data Rate (ODR), and power management on the device
    * *********************************************/

    /* Sets the range of the accelerometer */    
    #define `$INSTANCE_NAME`_ACC_RANGE_REG       (0x0Fu)        /**< Address of accelerometer range register*/
    #define `$INSTANCE_NAME`_ACC_RANGE_2G        (0x03u)        /**< Value for setting the bandwidth to ± 2 g */
    #define `$INSTANCE_NAME`_ACC_RANGE_4G        (0x05u)        /**< Value for setting the bandwidth to ± 4 g */
    #define `$INSTANCE_NAME`_ACC_RANGE_8G        (0x08u)        /**< Value for setting the bandwidth to ± 8 g */
    #define `$INSTANCE_NAME`_ACC_RANGE_16G       (0x0Cu)        /**< Value for setting the bandwidth to ± 16 g */
    #define `$INSTANCE_NAME`_ACC_RANGE_2G_GAIN   (0.0096138f)   /**< Acc gain of the ± 2 g setting [m/s^2] */
    #define `$INSTANCE_NAME`_ACC_RANGE_4G_GAIN   (0.0191295f)   /**< Acc gain of the ± 4 g setting [m/s^2] */
    #define `$INSTANCE_NAME`_ACC_RANGE_8G_GAIN   (0.0383571f)   /**< Acc gain of the ± 8 g setting [m/s^2] */
    #define `$INSTANCE_NAME`_ACC_RANGE_16G_GAIN  (0.0766161f)   /**< Acc gain of the ± 16 g setting [m/s^2] */    
    /* Sets the bandwidth the of the accelerometer data filter */
    #define `$INSTANCE_NAME`_ACC_BW_REG          (0x10u)     /**< Address of filter bandwidth register */
    #define `$INSTANCE_NAME`_ACC_BW_8_HZ         (0x08u)     /**< Value for setting the bandwidth to 8 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_16_HZ        (0x09u)     /**< Value for setting the bandwidth to 16 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_31_HZ        (0x0Au)     /**< Value for setting the bandwidth to 31 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_62_HZ        (0x0Bu)     /**< Value for setting the bandwidth to 62 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_125_HZ       (0x0Cu)     /**< Value for setting the bandwidth to 125 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_250_HZ       (0x0Du)     /**< Value for setting the bandwidth to 250 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_500_HZ       (0x0Eu)     /**< Value for setting the bandwidth to 500 HZ */
    #define `$INSTANCE_NAME`_ACC_BW_1000_HZ      (0x0Fu)     /**< Value for setting the bandwidth to 1000 HZ */
    /* Selection of the main power modes and the low power sleep period */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_REG                         (0x11u)     /**< Address of Power Mode Selection Register */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND_POS            (5u)        /**< Position of "Deep Suspend" bit */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN_POS             (6u)        /**< Position of "Low Power" bit */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND_POS                 (7u)        /**< Position of "Suspend" bit */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND                (1u << `$INSTANCE_NAME`_ACC_PMU_LPW_DEEP_SUSPEND_POS)    /**< Mask of "Deep Suspend" mode */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN                 (1u << `$INSTANCE_NAME`_ACC_PMU_LPW_LOWPOWER_EN_POS)     /**< Mask of "Low Power" mode */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND                     (1u << `$INSTANCE_NAME`_ACC_PMU_LPW_SUSPEND_POS)         /**< Mask of "Suspend" mode */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_NORMAL                      (0u)                                        /**< Mask of "Normal" mode */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_HALFMS            (0b0000)    /**< Value for setting the sleep duration to 0.5 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_1MS               (0b0110)    /**< Value for setting the sleep duration to 1 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_2MS               (0b0111)    /**< Value for setting the sleep duration to 2 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_4MS               (0b1000)    /**< Value for setting the sleep duration to 4 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_6MS               (0b1001)    /**< Value for setting the sleep duration to 6 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_10MS              (0b1010)    /**< Value for setting the sleep duration to 10 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_25MS              (0b1011)    /**< Value for setting the sleep duration to 25 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_50MS              (0b1100)    /**< Value for setting the sleep duration to 50 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_100MS             (0b1101)    /**< Value for setting the sleep duration to 100 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_500MS             (0b1110)    /**< Value for setting the sleep duration to 500 ms */
    #define `$INSTANCE_NAME`_ACC_PMU_LPW_SLEEP_DUR_1000MS            (0b1111)    /**< Value for setting the sleep duration to 1000 ms */
    /* Configuration settings for low power mode */
    #define `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_REG                   (0x12u)     /**< Address of Low Power Mode settings Register */
    #define `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_SLEEPTIMER_MODE_POS   (5u)        /**< Position of sleep timer mode bit */  
    #define `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE_POS     (6u)        /**< Position of lower power mode bit */
    #define `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_SLEEPTIMER_MODE       (1u << `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_SLEEPTIMER_MODE_POS)   /**< Mask of sleep timer mode */
    #define `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE         (1u << `$INSTANCE_NAME`_ACC_PMU_LOW_POWER_LOWPOWER_MODE_POS)     /**< Mask of low power mode */
    /* Sets acceleration data acquisition and data output format */
    #define `$INSTANCE_NAME`_ACC_ACCD_REG                (0x13u)     /**< Address of output format register */
    #define `$INSTANCE_NAME`_ACC_ACCD_DATA_HIGH_BW_POS   (7u)        /**< Position for disable filters bit */
    #define `$INSTANCE_NAME`_ACC_ACCD_SHADOW_DIS_POS     (6u)        /**< Position for shadowing enable bit */
    #define `$INSTANCE_NAME`_ACC_ACCD_DATA_HIGH_BW       (1u << `$INSTANCE_NAME`_ACC_ACCD_DATA_HIGH_BW_POS)   /**< Mask for disabling filters (enable high speed) */
    #define `$INSTANCE_NAME`_ACC_ACCD_SHADOW_DIS         (1u << `$INSTANCE_NAME`_ACC_ACCD_SHADOW_DIS_POS)     /**< Mask for disabling shadowing (LSB locked until MSB read) */
    /* Soft Reset Register */
    #define `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_REG              (0x14u) /**< Address of the accelerometer soft reset register */
    #define `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_VAL              (0xB6u) /**< Value that causes the accelerometer to reset */
    #define `$INSTANCE_NAME`_ACC_BGW_SOFTRESET_MS               (1u)    /**< Time in ms that it takes to reset the device*/
    /***************************************
    *        Function Prototypes
    ***************************************/
    /* Accelerometer specific functions */
    uint32 `$INSTANCE_NAME`_Acc_testConnection(uint32* i2cError);          /**< Test basic I2C contact with Accelerometer */
    uint32 `$INSTANCE_NAME`_Acc_Reset(`$INSTANCE_NAME`_ACC_STATE_T* accState);    /**< Start the Accelerometer */
    uint32 `$INSTANCE_NAME`_Acc_SetPowerMode(`$INSTANCE_NAME`_ACC_STATE_T* accState, `$INSTANCE_NAME`_ACC_POWER_T powerMode);    /**< Put the Accelerometer into the specified power mode */
    uint32 `$INSTANCE_NAME`_Acc_Read(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* accData);      /**< Read the value of the Accelerometer in int16 precision*/
    uint32 `$INSTANCE_NAME`_Acc_Readf(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_F* accData);    /**< Read the value of the Accelerometer in floating point precision*/
    uint32 `$INSTANCE_NAME`_Acc_Int2Float(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_T* intData, ACC_DATA_F* floatData);     /**< Converts the accelerometer int type to float type*/
    uint32 `$INSTANCE_NAME`_Acc_Float2Int(`$INSTANCE_NAME`_ACC_STATE_T* state, ACC_DATA_F* floatData, ACC_DATA_T* intData);     /**< Converts the accelerometer float type to int type*/
    
#endif /* `$INSTANCE_NAME`_ACC_H */
/* [] END OF FILE */
