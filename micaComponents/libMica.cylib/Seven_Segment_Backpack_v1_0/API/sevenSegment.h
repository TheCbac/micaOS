/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
*
* Brief:
*   Header for sevenSegment.c
*
* 2019.03.18  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include "micaCommon.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_DEFAULT_ADDR            (0b1110000)  /**< Default Slave address (0b1110[A2][A1][A0] */
    
    #define `$INSTANCE_NAME`_ADDR_DISPLAY_DATA       (0x00)
    
    
    #define `$INSTANCE_NAME`_CMD_DISP_ON             (0x81)      /**< Command: Turn the display on */
    #define `$INSTANCE_NAME`_CMD_DISP_BLINK_2HZ      (0x83)      /**< Command: Blink the display at 2 Hz */ 
    #define `$INSTANCE_NAME`_CMD_DISP_BLINK_1HZ      (0x85)      /**< Command: Blink the display at 1 Hz */ 
    #define `$INSTANCE_NAME`_CMD_DISP_BLINK_HALF_HZ  (0x87)      /**< Command: Blink the display at 0.5 Hz */ 
    
    
    #define `$INSTANCE_NAME`_CMD_SYS_CLCK_ON         (0x21)      /**< Command: Enable the system clock */
     
    #define `$INSTANCE_NAME`_NUM_DIGITS              (9u)        /**< Number of digit registers */
    #define `$INSTANCE_NAME`_DIGIT_1                 (0u)        /**< Position of the digit */  
    #define `$INSTANCE_NAME`_DIGIT_2                 (1u)        /**< Position of the digit */  
    #define `$INSTANCE_NAME`_DIGIT_3                 (2u)        /**< Position of the digit */  
    #define `$INSTANCE_NAME`_DIGIT_4                 (3u)        /**< Position of the digit */  
    #define `$INSTANCE_NAME`_DIGIT_DOTS              (4u)        /**< Position of the digit */  
     
     
    #define `$INSTANCE_NAME`_REG_DIGIT_1             (0x00u)     /* Memory position of the left most digit */
    #define `$INSTANCE_NAME`_REG_DIGIT_2             (0x02u)     /* Memory position of the second digit from the left */
    #define `$INSTANCE_NAME`_REG_DIGIT_3             (0x06u)     /* Memory position of the third digit from the left */
    #define `$INSTANCE_NAME`_REG_DIGIT_4             (0x08u)     /* Memory position of the fourth digit from the left (right most) */
    #define `$INSTANCE_NAME`_REG_DIGIT_DOTS          (0x04u)     /* Memory position of the dots on the display */
     
    #define `$INSTANCE_NAME`_DIGIT_MAX               (9)         /**< Largest numeric digit */
    #define `$INSTANCE_NAME`_DIGIT_MIN               (0)         /**< Smallest numeric digit */
    #define `$INSTANCE_NAME`_POSITION_MAX            (4u)        /**< Number of position that are writeable */
    #define `$INSTANCE_NAME`_DISPLAY_VAL_MAX         (9999)      /**< Maximum value that can be displayed */
    
    #define `$INSTANCE_NAME`_CHAR_BLANK              (0b0000000) /**< Blank the display */
    #define `$INSTANCE_NAME`_CHAR_0                  (0b0111111) /**< 7-Segment display value of numeric 0 */
    #define `$INSTANCE_NAME`_CHAR_1                  (0b0000110) /**< 7-Segment display value of numeric 1 */
    #define `$INSTANCE_NAME`_CHAR_2                  (0b1011011) /**< 7-Segment display value of numeric 2 */
    #define `$INSTANCE_NAME`_CHAR_3                  (0b1001111) /**< 7-Segment display value of numeric 3 */
    #define `$INSTANCE_NAME`_CHAR_4                  (0b1100110) /**< 7-Segment display value of numeric 4 */
    #define `$INSTANCE_NAME`_CHAR_5                  (0b1101101) /**< 7-Segment display value of numeric 5 */
    #define `$INSTANCE_NAME`_CHAR_6                  (0b1111101) /**< 7-Segment display value of numeric 6 */
    #define `$INSTANCE_NAME`_CHAR_7                  (0b0000111) /**< 7-Segment display value of numeric 7 */
    #define `$INSTANCE_NAME`_CHAR_8                  (0b1111111) /**< 7-Segment display value of numeric 8 */
    #define `$INSTANCE_NAME`_CHAR_9                  (0b1100111) /**< 7-Segment display value of numeric 9 */

    #define `$INSTANCE_NAME`_CHAR_L                  (0b0111000) /**< 7-Segment display value of 'L' */
    #define `$INSTANCE_NAME`_CHAR_A                  (0b1110111) /**< 7-Segment display value of 'A' */
    #define `$INSTANCE_NAME`_CHAR_U                  (0b0111110) /**< 7-Segment display value of 'U' */
    #define `$INSTANCE_NAME`_CHAR_N                  (0b0110111) /**< 7-Segment display value of 'N' */
    #define `$INSTANCE_NAME`_CHAR_C                  (0b0111001) /**< 7-Segment display value of 'C' */
    #define `$INSTANCE_NAME`_CHAR_H                  (0b1110110) /**< 7-Segment display value of 'H' */
    #define `$INSTANCE_NAME`_CHAR_O                  (0b0111111) /**< 7-Segment display value of 'O' */
    #define `$INSTANCE_NAME`_CHAR_G                  (0b0111101) /**< 7-Segment display value of 'G' */
    #define `$INSTANCE_NAME`_CHAR_DASH               (0b1000000) /**< 7-Segment display value of '-' */   
    
    #define `$INSTANCE_NAME`_DOTS_SHIFT_CENTER       (1u)       /**< Center colon shift value */
    #define `$INSTANCE_NAME`_DOTS_SHIFT_LEFT_UPPER   (2u)       /**< Upper left dot shift value */
    #define `$INSTANCE_NAME`_DOTS_SHIFT_LEFT_LOWER   (3u)       /**< Lower left dot shift value */
    #define `$INSTANCE_NAME`_DOTS_SHIFT_RIGHT        (4u)       /**< right dot shift value */
    
    #define `$INSTANCE_NAME`_DOTS_CENTER             (1 << `$INSTANCE_NAME`_DOTS_SHIFT_CENTER)      /**< Center colon value */
    #define `$INSTANCE_NAME`_DOTS_LEFT_UPPER         (1 << `$INSTANCE_NAME`_DOTS_SHIFT_LEFT_UPPER)  /**< Upper left dot value */
    #define `$INSTANCE_NAME`_DOTS_LEFT_LOWER         (1 << `$INSTANCE_NAME`_DOTS_SHIFT_LEFT_LOWER)  /**< Lower left dot value */
    #define `$INSTANCE_NAME`_DOTS_RIGHT              (1 << `$INSTANCE_NAME`_DOTS_SHIFT_RIGHT)       /**< Right dot value */
    
    
    
    
    
    #define `$INSTANCE_NAME`_DOTS_SHIFT_CENTER       (1u)       /**< Center colon  shift value */

    

    
    #define `$INSTANCE_NAME`_OFFSET_CHAR        (0x30)      /**< Offset for converting from ascii to numeric */
    
    #define `$INSTANCE_NAME`_ERR_RANGE_SHIFT    (31u)       /**< Shift for an out of range character */
    #define `$INSTANCE_NAME`_ERR_COMMS_SHIFT    (30u)       /**< Shift for an unpopulated Comms structure*/
    #define `$INSTANCE_NAME`_ERR_RANGE          (1u << `$INSTANCE_NAME`_ERR_RANGE_SHIFT);       /**< Error for an out of range character */
    #define `$INSTANCE_NAME`_ERR_COMMS          (1u << `$INSTANCE_NAME`_ERR_COMMS_SHIFT);       /**< Error for an unpopulated Comms structure */

    /***************************************
    * Enumerated Types
    ***************************************/
    typedef enum {
        BLINK_SOLID,
        BLINK_2HZ,
        BLINK_1HZ,
        BLINK_HALFHZ,
    } `$INSTANCE_NAME`_BLINK_T;
    
    /***************************************
    * Structures
    ***************************************/
    /* Communication structure for I2C data transfer*/
    typedef struct {
        uint32_t (*i2c_write)(uint8_t deviceAddr, uint8_t regAddr, uint8_t val);    /**< Write to an I2C register */
        uint32_t (*i2c_writeCmd)(uint8_t deviceAddr, uint8_t cmd);                  /**< Send a command via I2C */
        uint32_t (*i2c_writeArray)(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len);  /**< Write multiple registers */
        uint32_t (*i2c_read)(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result); /**< Read from a register */
    } `$INSTANCE_NAME`_COMMUNICATION_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    void `$INSTANCE_NAME`_setCommunications(`$INSTANCE_NAME`_COMMUNICATION_S* comms);
    uint32_t `$INSTANCE_NAME`_validateComms(void);


    uint32_t `$INSTANCE_NAME`_start(uint8_t addr); 
    uint32_t `$INSTANCE_NAME`_clearDisplay(uint8_t addr);     
    uint32_t `$INSTANCE_NAME`_writeAllSegments(uint8_t addr, uint8_t val);
    uint32_t `$INSTANCE_NAME`_writeDigitRaw(uint8_t addr, uint8_t position, uint8_t val);
    uint32_t `$INSTANCE_NAME`_writeDigitNum(uint8_t addr, uint8_t position, uint8_t digit);
    uint32_t `$INSTANCE_NAME`_writeDigitChar(uint8_t addr, uint8_t position, uint8_t digit);
    uint32_t `$INSTANCE_NAME`_writeDisplayString(uint8_t addr, char* array);
    uint32_t `$INSTANCE_NAME`_writeDisplayNum(uint8_t addr, uint16_t val);  
    uint32_t `$INSTANCE_NAME`_writeDisplayArray(uint8_t addr, uint8_t *array);
    uint32_t `$INSTANCE_NAME`_blinkState(uint8_t addr,`$INSTANCE_NAME`_BLINK_T rate);
    uint32_t `$INSTANCE_NAME`_readDigit(uint8_t addr, uint8_t position, uint8_t *result);
    uint32_t `$INSTANCE_NAME`_readDisplay(uint8_t displayAddr, uint8_t *resultArray);
    
    

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
