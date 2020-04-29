/***************************************************************************
*                              MICA  © 2020
*                               
*
* File: SevenSegDual.h
* Workspace: MICA OS
* Project: MICA OS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: N/A N/A
* PSoC: 
*
* Brief:
*   Header for SevenSegDual.c
*
* 2020.04.29  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef SevenSegDual_H
  #define SevenSegDual_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
  #include "TCA9535.h"
  /***************************************
  * Macro Definitions
  ***************************************/
  #define SEVENSEG_CHAR_BLANK              (0b0000000) /**< Blank the display */
  #define SEVENSEG_CHAR_0                  (0b0111111) /**< 7-Segment display value of numeric 0 */
  #define SEVENSEG_CHAR_1                  (0b0000110) /**< 7-Segment display value of numeric 1 */
  #define SEVENSEG_CHAR_2                  (0b1011011) /**< 7-Segment display value of numeric 2 */
  #define SEVENSEG_CHAR_3                  (0b1001111) /**< 7-Segment display value of numeric 3 */
  #define SEVENSEG_CHAR_4                  (0b1100110) /**< 7-Segment display value of numeric 4 */
  #define SEVENSEG_CHAR_5                  (0b1101101) /**< 7-Segment display value of numeric 5 */
  #define SEVENSEG_CHAR_6                  (0b1111101) /**< 7-Segment display value of numeric 6 */
  #define SEVENSEG_CHAR_7                  (0b0000111) /**< 7-Segment display value of numeric 7 */
  #define SEVENSEG_CHAR_8                  (0b1111111) /**< 7-Segment display value of numeric 8 */
  #define SEVENSEG_CHAR_9                  (0b1100111) /**< 7-Segment display value of numeric 9 */


  #define SEVENSEG_CHAR_A                  (0b1110111) /**< 7-Segment display value of 'A' */
  #define SEVENSEG_CHAR_B                  (0b1111100) /**< 7-Segment display value of 'B' */
  #define SEVENSEG_CHAR_C                  (0b0111001) /**< 7-Segment display value of 'C' */
  #define SEVENSEG_CHAR_D                  (0b1011110) /**< 7-Segment display value of 'D' */
  #define SEVENSEG_CHAR_E                  (0b1111001) /**< 7-Segment display value of 'E' */
  #define SEVENSEG_CHAR_F                  (0b1110001) /**< 7-Segment display value of 'F' */
  #define SEVENSEG_CHAR_G                  (0b0111101) /**< 7-Segment display value of 'G' */
  #define SEVENSEG_CHAR_H                  (0b1110110) /**< 7-Segment display value of 'H' */
  #define SEVENSEG_CHAR_I                  (0b0000110) /**< 7-Segment display value of 'I' */
  #define SEVENSEG_CHAR_J                  (0b0011110) /**< 7-Segment display value of 'J' */
  #define SEVENSEG_CHAR_K                  (0b1111000) /**< 7-Segment display value of 'K' */
  #define SEVENSEG_CHAR_L                  (0b0111000) /**< 7-Segment display value of 'L' */
  #define SEVENSEG_CHAR_M                  (0b0010101) /**< 7-Segment display value of 'M' */
  #define SEVENSEG_CHAR_N                  (0b0110111) /**< 7-Segment display value of 'N' */
  #define SEVENSEG_CHAR_O                  (0b0111111) /**< 7-Segment display value of 'O' */
  #define SEVENSEG_CHAR_P                  (0b1110011) /**< 7-Segment display value of 'P' */
  #define SEVENSEG_CHAR_K                  (0b1100111) /**< 7-Segment display value of 'K' */
  #define SEVENSEG_CHAR_R                  (0b1010000) /**< 7-Segment display value of 'R' */
  #define SEVENSEG_CHAR_S                  (0b1101101) /**< 7-Segment display value of 'S' */
  #define SEVENSEG_CHAR_T                  (0b1000110) /**< 7-Segment display value of 'T' */
  #define SEVENSEG_CHAR_U                  (0b0111110) /**< 7-Segment display value of 'U' */
  #define SEVENSEG_CHAR_V                  (0b0011100) /**< 7-Segment display value of 'V' */
  #define SEVENSEG_CHAR_W                  (0b0101010) /**< 7-Segment display value of 'W' */
  #define SEVENSEG_CHAR_X                  (0b1001001) /**< 7-Segment display value of 'X' */
  #define SEVENSEG_CHAR_Y                  (0b1101110) /**< 7-Segment display value of 'Y' */
  #define SEVENSEG_CHAR_Z                  (0b1011011) /**< 7-Segment display value of 'Z' */
  #define SEVENSEG_CHAR_DASH               (0b1000000) /**< 7-Segment display value of '-' */  
  #define SEVENSEG_CHAR_DOT                (0b10000000) /**< 7-Segment display value of '.' */  


  #define SEVENSEG_ERROR_NONE             (0x00)  /**< No error */
  #define SEVENSEG_ERROR_TCA              (1u << 0)  /**< Error with the TCA */
  #define SEVENSEG_ERROR_RANGE            (1u << 1) /**< An out of value range */

  #define SEVENSEG_DECIMAL_MAX            (999) /* Max value in tenths */
  
  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  typedef struct {  
    uint32_t error;         /**< Functions that exit with an error use this to transmit info out */
    uint8_t _char0;      /* Value for the first digit */
    uint8_t _char1;      /* Value for the first digit */
    TCA9535_STATE_S _tca;   /**< Driver for controlling the port */
    uint16_t _val;    /* Store the value in tenths e.g. 101 -> 10.1 */

  } SEVENSEG_STATE_S;
  
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t SEVENSEG_start(SEVENSEG_STATE_S* state, uint8_t addr, COMMS_I2C_S *i2c);
  uint32_t SEVENSEG_update(SEVENSEG_STATE_S* state);
  uint32_t SEVENSEG_mapChar(uint8_t val, uint8_t * display);
  uint32_t SEVENSEG_displayNum(SEVENSEG_STATE_S* state, uint16_t val);
  



  // uint32_t SEVENSEG_clearDisplay(SEVENSEG_STATE_S* state);     
  // uint32_t SEVENSEG_writeAllSegments(SEVENSEG_STATE_S* state, uint8_t val);
  // uint32_t SEVENSEG_writeDigitRaw(SEVENSEG_STATE_S* state, uint8_t position, uint8_t val);
  // uint32_t SEVENSEG_writeDigitNum(SEVENSEG_STATE_S* state, uint8_t position, uint8_t digit);
  // uint32_t SEVENSEG_writeDigitChar(SEVENSEG_STATE_S* state, uint8_t position, uint8_t digit);
  // uint32_t SEVENSEG_writeDisplayString(SEVENSEG_STATE_S* state, char* array);
  // uint32_t SEVENSEG_writeDisplayNum(SEVENSEG_STATE_S* state, uint16_t val);  
  // uint32_t SEVENSEG_writeDisplayArray(SEVENSEG_STATE_S* state, uint8_t *array);
  // uint32_t SEVENSEG_readDigit(SEVENSEG_STATE_S* state, uint8_t position, uint8_t *result);
  // uint32_t SEVENSEG_readDisplay(SEVENSEG_STATE_S* state, uint8_t displayAddr, uint8_t *resultArray);

#endif /* SevenSegDual_H */
/* [] END OF FILE */
