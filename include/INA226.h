/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: ina226.h
* Workspace: micaOS
* Project: micaOS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: N/A N/A
* PSoC: 
*
* Brief:
*   Header for ina226.c
*
* 2019.10.03  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef INA226_H
  #define INA226_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
  /***************************************
  * Macro Definitions
  ***************************************/

  #define INA226_ADDR_CONFIG          (0x00) /**< Address of the configuration register */
  #define INA226_ADDR_SHUNT           (0x01) /**< Address of the Shunt Voltage register */
  #define INA226_ADDR_BUS             (0x02) /**< Address of the Bus Voltage register */
  #define INA226_ADDR_POWER           (0x03) /**< Address of the Power register */
  #define INA226_ADDR_CURRENT         (0x04) /**< Address of the Current register */
  #define INA226_ADDR_CALIBRATION     (0x05) /**< Address of the Calibration register */
  #define INA226_ADDR_ENABLE          (0x06) /**< Address of the Mask/Enable register */
  #define INA226_ADDR_ALERT           (0x07) /**< Address of the Alert limit register */
  #define INA226_ADDR_ID_MFG          (0xFE) /**< Address of the Manufacturer ID register */
  #define INA226_ADDR_ID_DIE          (0xFF) /**< Address of the Die ID register */

  /* Configuration register */
  #define INA_CONFIG_VAL              (0x4127) /**< Default value of the configuration register */
  #define INA_CONFIG_SHIFT_MODE1      (0) /**< Shift for the Mode 1 flag */
  #define INA_CONFIG_SHIFT_MODE2      (1) /**< Shift for the Mode 2 flag */
  #define INA_CONFIG_SHIFT_MODE3      (2) /**< Shift for the Mode 3 flag */
  #define INA_CONFIG_SHIFT_VSHCT0     (3) /**< Shift for the Shunt voltage conversion time 0 flag */
  #define INA_CONFIG_SHIFT_VSHCT1     (4) /**< Shift for the Shunt voltage conversion time 1 flag */
  #define INA_CONFIG_SHIFT_VSHCT2     (5) /**< Shift for the Shunt voltage conversion time 2 flag */
  #define INA_CONFIG_SHIFT_VBUSCT0    (6) /**< Shift for the Bus voltage conversion time 0 flag */
  #define INA_CONFIG_SHIFT_VBUSCT1    (7) /**< Shift for the Bus voltage conversion time 1 flag */
  #define INA_CONFIG_SHIFT_VBUSCT2    (8) /**< Shift for the Bus voltage conversion time 2 flag */
  #define INA_CONFIG_SHIFT_AVG0       (9) /**< Shift for the Averaging mode 0 flag */
  #define INA_CONFIG_SHIFT_AVG1       (10) /**< Shift for the Averaging mode 1 flag */
  #define INA_CONFIG_SHIFT_AVG2       (11) /**< Shift for the Averaging mode 2 flag */
  #define INA_CONFIG_SHIFT_RES1       (14) /**< Shift for the reserved bit*/
  #define INA_CONFIG_SHIFT_RST        (15) /**< Shift for Reset flag */
  #define INA_CONFIG_MASK_MODE1       (1u << INA_CONFIG_SHIFT_MODE1) /**< Mask for the Mode 1 flag */
  #define INA_CONFIG_MASK_MODE2       (1u << INA_CONFIG_SHIFT_MODE2) /**< Mask for the Mode 2 flag */
  #define INA_CONFIG_MASK_MODE3       (1u << INA_CONFIG_SHIFT_MODE3) /**< Mask for the Mode 3 flag */
  #define INA_CONFIG_MASK_VSHCT0      (1u << INA_CONFIG_SHIFT_VSHCT0) /**< Mask for the Shunt voltage conversion time 0 flag */
  #define INA_CONFIG_MASK_VSHCT1      (1u << INA_CONFIG_SHIFT_VSHCT1) /**< Mask for the Shunt voltage conversion time 1 flag */
  #define INA_CONFIG_MASK_VSHCT2      (1u << INA_CONFIG_SHIFT_VSHCT2) /**< Mask for the Shunt voltage conversion time 2 flag */
  #define INA_CONFIG_MASK_VBUSCT0     (1u << INA_CONFIG_SHIFT_VBUSCT0) /**< Mask for the Bus voltage conversion time 0 flag */
  #define INA_CONFIG_MASK_VBUSCT1     (1u << INA_CONFIG_SHIFT_VBUSCT1) /**< Mask for the Bus voltage conversion time 1 flag */
  #define INA_CONFIG_MASK_VBUSCT2     (1u << INA_CONFIG_SHIFT_VBUSCT2) /**< Mask for the Bus voltage conversion time 2 flag */
  #define INA_CONFIG_MASK_AVG0        (1u << INA_CONFIG_SHIFT_AVG0) /**< Mask for the Averaging mode 0 flag */
  #define INA_CONFIG_MASK_AVG1        (1u << INA_CONFIG_SHIFT_AVG1) /**< Mask for the Averaging mode 1 flag */
  #define INA_CONFIG_MASK_AVG2        (1u << INA_CONFIG_SHIFT_AVG2) /**< Mask for the Averaging mode 2 flag */
  #define INA_CONFIG_MASK_RES1        (1u << INA_CONFIG_SHIFT_RES1) /**< Mask for the reserved bit*/ 
  #define INA_CONFIG_MASK_RST         (1u << INA_CONFIG_SHIFT_RST) /**< Mask for Reset flag */

  #define INA_CONFIG_AVG_1            (0x0 << INA_CONFIG_SHIFT_AVG0) /**< Value for 1 average */
  #define INA_CONFIG_AVG_4            (0x1 << INA_CONFIG_SHIFT_AVG0) /**< Value for 4 average */
  #define INA_CONFIG_AVG_16           (0x2 << INA_CONFIG_SHIFT_AVG0) /**< Value for 16 average */
  #define INA_CONFIG_AVG_64           (0x3 << INA_CONFIG_SHIFT_AVG0) /**< Value for 64 average */
  #define INA_CONFIG_AVG_128          (0x4 << INA_CONFIG_SHIFT_AVG0) /**< Value for 128 average */
  #define INA_CONFIG_AVG_256          (0x5 << INA_CONFIG_SHIFT_AVG0) /**< Value for 256 average */
  #define INA_CONFIG_AVG_512          (0x6 << INA_CONFIG_SHIFT_AVG0) /**< Value for 512 average */
  #define INA_CONFIG_AVG_1024         (0x7 << INA_CONFIG_SHIFT_AVG0) /**< Value for 1024 average */

  #define INA_CONFIG_VBUSCT_140       (0x0 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 140 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_204       (0x1 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 204 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_332       (0x2 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 332 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_588       (0x3 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 588 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_1100      (0x4 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 1100 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_2116      (0x5 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 2116 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_4156      (0x6 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 4156 µS bus conversion time */
  #define INA_CONFIG_VBUSCT_8244      (0x7 << INA_CONFIG_SHIFT_VBUSCT0) /* Value for 8244 µS bus conversion time */

  #define INA_CONFIG_VSHCT_140        (0x0 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 140 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_204        (0x1 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 204 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_332        (0x2 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 332 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_588        (0x3 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 588 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_1100       (0x4 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 1100 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_2116       (0x5 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 2116 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_4156       (0x6 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 4156 µS Shunt conversion time */
  #define INA_CONFIG_VSHCT_8244       (0x7 << INA_CONFIG_SHIFT_VSHCT0) /* Value for 8244 µS Shunt conversion time */

  #define INA_CONFIG_MODE_POWERDOWN   (0x0 << INA_CONFIG_SHIFT_MODE1) /* Value for Power down */
  #define INA_CONFIG_MODE_TRIG_SHUNT  (0x1 << INA_CONFIG_SHIFT_MODE1) /* Value for Triggered, Shunt Voltage */
  #define INA_CONFIG_MODE_TRIG_BUS    (0x2 << INA_CONFIG_SHIFT_MODE1) /* Value for triggered, Bus voltage*/
  #define INA_CONFIG_MODE_TRIG_SH_BUS (0x3 << INA_CONFIG_SHIFT_MODE1) /* Value for triggered, Shunt & bus voltage */
  #define INA_CONFIG_MODE_POWERDOWN2  (0x4 << INA_CONFIG_SHIFT_MODE1) /* Value for Power down */
  #define INA_CONFIG_MODE_CONT_SHUNT  (0x5 << INA_CONFIG_SHIFT_MODE1) /* Value for continuous, Shunt voltage */
  #define INA_CONFIG_MODE_CONT_BUS    (0x6 << INA_CONFIG_SHIFT_MODE1) /* Value for continuous, Bus voltage */
  #define INA_CONFIG_MODE_CONT_SH_BUS (0x7 << INA_CONFIG_SHIFT_MODE1) /* Value for continuous, Shunt & bus voltage */


  /* Calibration register */
  #define INA_CALIBRATION_VAL         (0x0000) /**< Default value of the Calibration register */
  
  /* Mask/Enable register */
  #define INA_ENABLE_VAL              (0x0000) /**< Default value of the Mask/Enable register */
  #define INA_ENABLE_SHIFT_LEN        (0) /**< Shift of the Alert Latch bit */
  #define INA_ENABLE_SHIFT_APOL       (1) /**< Shift of the Alert Polarity bit */
  #define INA_ENABLE_SHIFT_OVF        (2) /**< Shift of the Math Overflow bit */
  #define INA_ENABLE_SHIFT_CVRF       (3) /**< Shift of the Conversion Ready Flag bit */
  #define INA_ENABLE_SHIFT_AFF        (4) /**< Shift of the Alert Function bit */
  #define INA_ENABLE_SHIFT_CNVR       (10) /**< Shift of the Conversion Ready bit */
  #define INA_ENABLE_SHIFT_POL        (11) /**< Shift of the Power Over-Limit bit */
  #define INA_ENABLE_SHIFT_BUL        (12) /**< Shift of the Bus Undervoltage bit */
  #define INA_ENABLE_SHIFT_BOL        (13) /**< Shift of the Bus Overvoltage bit */
  #define INA_ENABLE_SHIFT_SUL        (14) /**< Shift of the Shunt Under-voltage bit */
  #define INA_ENABLE_SHIFT_SOL        (15) /**< Shift of the Shunt over-voltage bit */
  #define INA_ENABLE_MASK_LEN         (1u << INA_ENABLE_SHIFT_LEN) /**<  Flag of the Alert Latch bit */
  #define INA_ENABLE_MASK_APOL        (1u << INA_ENABLE_SHIFT_APOL) /**<  Flag of the Alert Polarity bit */
  #define INA_ENABLE_MASK_OVF         (1u << INA_ENABLE_SHIFT_OVF) /**<  Flag of the Math Overflow bit */
  #define INA_ENABLE_MASK_CVRF        (1u << INA_ENABLE_SHIFT_CVRF) /**<  Flag of the Conversion Ready Flag bit */
  #define INA_ENABLE_MASK_AFF         (1u << INA_ENABLE_SHIFT_AFF) /**<  Flag of the Alert Function bit */
  #define INA_ENABLE_MASK_CNVR        (1u << INA_ENABLE_SHIFT_CNVR) /**< Flag  of the Conversion Ready bit */
  #define INA_ENABLE_MASK_POL         (1u << INA_ENABLE_SHIFT_POL) /**< Flag  of the Power Over-Limit bit */
  #define INA_ENABLE_MASK_BUL         (1u << INA_ENABLE_SHIFT_BUL) /**< Flag  of the Bus Undervoltage bit */
  #define INA_ENABLE_MASK_BOL         (1u << INA_ENABLE_SHIFT_BOL) /**< Flag  of the Bus Overvoltage bit */
  #define INA_ENABLE_MASK_SUL         (1u << INA_ENABLE_SHIFT_SUL) /**< Flag  of the Shunt Under-voltage bit */
  #define INA_ENABLE_MASK_SOL         (1u << INA_ENABLE_SHIFT_SOL) /**< Flag  of the Shunt over-voltage bit */

  /* VSHUNT */
  #define INA_VSHUNT_LSB              (0.0000025f) /* Value in Volts of a LSB */   
  #define INA_VSHUNT_MASK             (0x7FFF) /* Full range of the VBUS register */
  #define INA_BIT_WIDTH               (16) /* Number of bits per register */
  #define INA_CURRENT_LSB_SCALE       (32768.0) /* Scaling factor for the device */
  #define INA_CAL_SCALE               (0.00512) /* Scaling factor for the calibration reg */
  #define INA_POWER_SCALE             (25.0) /* Fixed scale for Power conversion */
  /* VBUS  */
  #define INA_VBUS_LSB                (0.00125f) /* Value in Volts of a LSB */   
  #define INA_VBUS_MASK               (0x7FFF) /* Full range of the VBUS register */

  /* MFG ID */
  #define INA_ID_MFG_VAL              (0x5449) /*<< Manufacturer ID */

  /* Die ID */
  #define INA_ID_DIE_VAL              (0x2260) /*<< Die ID */


  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
    COMMS_I2C_S *i2c;       /**< Pointer to the I2C comms struct */      
    uint32_t error;         /**< Functions that exit with an error use this to transmit info out */
    uint8_t deviceAddr;     /**< Address of the device to communicate with */
    float maxCurrent;       /**< Maximum expected current in units of Amperes */
    float rShunt;           /**< Value of the shunt resistor in units of Ohms */
    float _currentLsb;       /**< Internal use only, do not set directly */
    float _calibration;      /**< Internal use only, do not set directly */
  } INA226_STATE_S; 
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t INA226_writeReg(INA226_STATE_S* state, uint8_t regAddr, uint16_t val);
  uint32_t INA226_readReg(INA226_STATE_S* state, uint8_t regAddr, uint16_t* val);
  uint32_t INA226_reset(INA226_STATE_S* state);
  uint32_t INA226_start(INA226_STATE_S* state);
  uint32_t INA226_readVoltage_Bus(INA226_STATE_S* state, float* val);
  uint32_t INA226_readVoltage_Shunt(INA226_STATE_S* state, float* val);
  uint32_t INA226_readCurrent(INA226_STATE_S* state, float* val);
  uint32_t INA226_readPower(INA226_STATE_S* state, float* val);


#endif /* INA226_H */
/* [] END OF FILE */
