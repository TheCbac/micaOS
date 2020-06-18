/***************************************************************************
*                                       MICA
* File: RGB.h
* Workspace: micaOs
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for controlling RGB LED
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.02.28 CC - Document created
*   2020.06.15 CC - Updated to generic 
********************************************************************************/
/* Header Guard */
#ifndef RGB_H
  #define RGB_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaCommon.h"

  /***************************************
  * Macro Definitions
  ***************************************/
  #define RGB_ACTIVE_HIGH   (1)
  #define RGB_ACTIVE_LOW    (0)

  #define RGB_R_MASK        (1u << 0)
  #define RGB_G_MASK        (1u << 1)
  #define RGB_B_MASK        (1u << 2)

  #define RGB_ERROR_NONE      (0)
  #define RGB_ERROR_INIT      (1u << 0) /* Struct has not been initialized */
  #define RGB_ERROR_PINWRITE  (1u << 1) /* Function pointer is invalid */
  #define RGB_ERROR_LOCKED    (1u << 2) /* Structure was locked */
  /***************************************
  * Enumerated types
  ***************************************/
  /* Color Types  */
  typedef enum {
    RGB_None = 0x00,
    RGB_Red =     RGB_R_MASK,
    RGB_Green =   RGB_G_MASK,
    RGB_Blue =    RGB_B_MASK,
    RGB_Yellow =  RGB_R_MASK + RGB_G_MASK,  /* Red + Green */
    RGB_Magenta = RGB_R_MASK + RGB_B_MASK, /* Red + Blue */
    RGB_Cyan =    RGB_G_MASK + RGB_G_MASK,    /* Green + Blue */
    RGB_White =   RGB_R_MASK + RGB_G_MASK + RGB_B_MASK    /* All On */
  } RGB_Colors_T;

  /* LED state */
  typedef enum {
    RGB_OFF = 0x00,
    RGB_ON = 0x01
  } RGB_LED_T;
  /***************************************
  * Structures
  ***************************************/
  typedef struct {
    void (*fn_pin_R_Write) (uint8_t pinVal);    /* Generic function to write Red LED pin state */
    void (*fn_pin_G_Write) (uint8_t pinVal);    /* Generic function to write Green LED pin state */
    void (*fn_pin_B_Write) (uint8_t pinVal);    /* Generic function to write Blue LED pin state */
    bool _Red;     /* State of R LED */
    bool _Green;     /* State of G LED */
    bool _Blue;     /* State of B LED */
    bool _activeLow; /* If this is set to true, values are inverted before being written to the pins  */
    bool _init;   /* initialization variable */
  } RGB_S; 

  /* Default struct to initialize - guarantees _init is 0 */
  extern const RGB_S RGB_DEFAULT_S;
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t RGB_Start(RGB_S *const state, bool activePinVal);
  uint32_t RGB_Write(RGB_S *const state, RGB_Colors_T color);

  uint32_t RGB_R_Write(RGB_S *const state, RGB_LED_T ledR);
  uint32_t RGB_G_Write(RGB_S *const state, RGB_LED_T ledG);
  uint32_t RGB_B_Write(RGB_S *const state, RGB_LED_T ledB);

  uint32_t RGB_R_Toggle(RGB_S *const state);
  uint32_t RGB_G_Toggle(RGB_S *const state);
  uint32_t RGB_B_Toggle(RGB_S *const state);
   
#endif /* RGB_H */
/* [] END OF FILE */