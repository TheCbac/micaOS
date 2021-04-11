/***************************************************************************
*                                       MICA
* File: LTC6915.h
* Workspace: micaOS
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Driver file for the LTC6915 Instrumentation amplifier
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2020.06.19 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef LTC6915_H
  #define LTC6915_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaCommon.h"
  #include <stdbool.h>
  
  /***************************************
  * Macro Definitions
  ***************************************/
  #define LTC6915_ERROR_NONE       (0)
  #define LTC6915_ERROR_INIT       (1u << 0) /* Structure has not been initialized */
  #define LTC6915_ERROR_LOCKED     (1u << 1) /* Structure was locked */
  #define LTC6915_ERROR_PARALLEL   (1u << 2) /* Missing functions */
  #define LTC6915_ERROR_SERIAL     (1u << 3) /* Missing comms */
  #define LTC6915_ERROR_RANGE      (1u << 4) /* Invalid value */


  #define LTC6915_MASK_D0           (1u << 0)
  #define LTC6915_MASK_D1           (1u << 1)
  #define LTC6915_MASK_D2           (1u << 2)
  #define LTC6915_MASK_D3           (1u << 3)

  /***************************************
  * Enumerated types
  ***************************************/
  typedef enum {
    LTC6915_MODE_SERIAL,
    LTC6915_MODE_PARALLEL,
  } LTC6915_MODE_T;

  typedef enum {
    LTC6915_GAIN_0    = 0x00,
    LTC6915_GAIN_1    = 0x01,
    LTC6915_GAIN_2    = 0x02,
    LTC6915_GAIN_4    = 0x03,
    LTC6915_GAIN_8    = 0x04,
    LTC6915_GAIN_16   = 0x05,
    LTC6915_GAIN_32   = 0x06,
    LTC6915_GAIN_64   = 0x07,
    LTC6915_GAIN_128  = 0x08,
    LTC6915_GAIN_256  = 0x09,
    LTC6915_GAIN_512  = 0x0A,
    LTC6915_GAIN_1024 = 0x0B,
    LTC6915_GAIN_2048 = 0x0C,
    LTC6915_GAIN_4096 = 0x0D,
  } LTC6915_GAIN_T;
  /***************************************
  * Structures 
  ***************************************/
  typedef struct {
    void (*fn_pin_D0_Write) (uint8_t val);    /* Generic function to write D0 pin state in parallel mode  */
    void (*fn_pin_D1_Write) (uint8_t val);    /* Generic function to write D1 pin state in parallel mode */
    void (*fn_pin_D2_Write) (uint8_t val);    /* Generic function to write D2 pin state in parallel mode */
    void (*fn_pin_D3_Write) (uint8_t val);    /* Generic function to write D3 pin state in parallel mode */

    LTC6915_MODE_T _mode;    /* The mode of the device */
    LTC6915_GAIN_T _gain;   /* Gain of the amp */
    bool _init; /* Initialization error */
  } LTC6915_S;

  /* Default structure */
  extern const LTC6915_S LTC6915_DEFAULT_S;
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t ltc6915_startSerial(LTC6915_S *const ltc); 
  uint32_t ltc6915_startParallel(LTC6915_S *const ltc); 
  uint32_t ltc6915_setGain(LTC6915_S *const ltc, LTC6915_GAIN_T gain);

  uint32_t ltc6915_mapGainWord(LTC6915_GAIN_T gainWord, uint16_t *const result);
    
#endif /* LTC6915_H */
    

/* [] END OF FILE */
