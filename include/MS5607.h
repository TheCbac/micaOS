/***************************************************************************
*                              Majestic Labs  © 2020
*                               
*
* File: MS5607.h
* Workspace: micaOS
* Project: Drivers
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: N/A 
*
* Brief:
*   Header for MS5607.c Pressure sensor 
*
* 2020.05.12  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef MS5607_H
  #define MS5607_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
    
  /***************************************
  * Macro Definitions
  ***************************************/
  #define MS5607_CMD_RESET       (0x1E)  /* Reset the device */
  #define MS5607_CMD_D1_256      (0x40)  /* Begin the D1 conversion at an OSR of 256 */
  #define MS5607_CMD_D1_512      (0x42)  /* Begin the D1 conversion at an OSR of 512 */
  #define MS5607_CMD_D1_1024     (0x44)  /* Begin the D1 conversion at an OSR of 1024 */
  #define MS5607_CMD_D1_2048     (0x46)  /* Begin the D1 conversion at an OSR of 2048 */
  #define MS5607_CMD_D1_4096     (0x48)  /* Begin the D1 conversion at an OSR of 4096 */
  #define MS5607_CMD_D2_256      (0x50)  /* Begin the D2 conversion at an OSR of 256 */
  #define MS5607_CMD_D2_512      (0x52)  /* Begin the D2 conversion at an OSR of 512 */
  #define MS5607_CMD_D2_1024     (0x54)  /* Begin the D2 conversion at an OSR of 1024 */
  #define MS5607_CMD_D2_2048     (0x56)  /* Begin the D2 conversion at an OSR of 2048 */
  #define MS5607_CMD_D2_4096     (0x58)  /* Begin the D2 conversion at an OSR of 4096 */
  #define MS5607_CMD_ADC         (0x00)  /* Read the ADC*/

  #define MS5607_ADDR_PROM        (0xA0)  /* Address of the  the C1 Coefficient*/
  // #define MS5607_CMD_PROM_C1     (0xA0)  /* Read the C1 Coefficient*/
  // #define MS5607_CMD_PROM_C2     (0xA2)  /* Read the C2 Coefficient*/
  // #define MS5607_CMD_PROM_C3     (0xA4)  /* Read the C3 Coefficient*/
  // #define MS5607_CMD_PROM_C4     (0xA6)  /* Read the C4 Coefficient*/
  // #define MS5607_CMD_PROM_C5     (0xA8)  /* Read the C5 Coefficient*/
  // #define MS5607_CMD_PROM_C6     (0xAE)  /* Read the C6 Coefficient*/

  #define MS5607_COEFFS_LEN     (6)
  /***************************************
  * Enumerated Types
  ***************************************/
  typedef enum {
    MS5607_OSR_256,     /* Conversion time 0.54 ms */
    MS5607_OSR_512,     /* Conversion time 1.06 ms */
    MS5607_OSR_1024,    /* Conversion time 2.08 ms */
    MS5607_OSR_2048,    /* Conversion time 4.13 ms */
    MS5607_OSR_4096     /* Conversion time 8.22 ms */
  } MS5607_OSR_T;
  /* Which variable to read */
  typedef enum {
    MS5607_PRESSURE,
    MS5607_TEMP,
  }MS5607_DATA_T;
  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
    uint32_t error;         /**< Functions that exit with an error use this to transmit info out */
    int32_t temp;         /* Calculated temperature */
    int32_t pressure;     /* Calculated pressure */
    COMMS_I2C_S *_i2c;     /**< Pointer to the I2C comms struct */      
    uint8_t _deviceAddr;     /**< Address of the device to communicate with */
    MS5607_DATA_T _convertType; /* The data type from the last read  */
    uint16_t _coeffs[MS5607_COEFFS_LEN];
  } MS5607_STATE_S;
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t MS5607_start(MS5607_STATE_S *const state, COMMS_I2C_S *const i2c, uint8_t i2cAddr);
  uint32_t MS5607_reset(MS5607_STATE_S *const state);
  uint32_t MS5607_startConvert(MS5607_STATE_S *const state, MS5607_DATA_T convertType, MS5607_OSR_T osr);
  uint32_t MS5607_read_ADC(MS5607_STATE_S *const state);
  uint32_t MS5607_read_ROM(MS5607_STATE_S *const state);
  uint32_t MS5607_calculatePressureTemp(MS5607_STATE_S *const state);

  uint32_t MS5607_writeCmd(MS5607_STATE_S *const state, uint8_t cmd);





#endif /* MS5607_H */
/* [] END OF FILE */
