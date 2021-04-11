/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: sevenSegment.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   API for controlling the seven segment display HT16K33 Backpack
*
* 2019.03.18  - Document Created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"

/* Commincations structure for holding the I2C functions */
`$INSTANCE_NAME`_COMMUNICATION_S `$INSTANCE_NAME`_comms;

/* Mapping of the position numeric value to their register value */
uint8_t `$INSTANCE_NAME`_positionArray[`$INSTANCE_NAME`_POSITION_MAX + ONE] = {
    `$INSTANCE_NAME`_REG_DIGIT_1,
    `$INSTANCE_NAME`_REG_DIGIT_2,
    `$INSTANCE_NAME`_REG_DIGIT_3,
    `$INSTANCE_NAME`_REG_DIGIT_4,
    `$INSTANCE_NAME`_REG_DIGIT_DOTS
};

/* Mapping of the digits numeric value to display value */
uint8_t `$INSTANCE_NAME`_digitArray[`$INSTANCE_NAME`_DIGIT_MAX + ONE] = {
    `$INSTANCE_NAME`_CHAR_0,
    `$INSTANCE_NAME`_CHAR_1,
    `$INSTANCE_NAME`_CHAR_2,
    `$INSTANCE_NAME`_CHAR_3,
    `$INSTANCE_NAME`_CHAR_4,
    `$INSTANCE_NAME`_CHAR_5,
    `$INSTANCE_NAME`_CHAR_6,
    `$INSTANCE_NAME`_CHAR_7,
    `$INSTANCE_NAME`_CHAR_8,
    `$INSTANCE_NAME`_CHAR_9
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_setCommunications()
****************************************************************************//**
* \brief
*  Stores the communication structure passed in. Must be called before any
*   other functions.
*
* \param comms
*   Pointer to the structure containing the I2C data structures
*
* \return
*  None
*******************************************************************************/
void `$INSTANCE_NAME`_setCommunications(`$INSTANCE_NAME`_COMMUNICATION_S* comms){
  /* Copy the structure */
  `$INSTANCE_NAME`_comms.i2c_write = comms->i2c_write;
  `$INSTANCE_NAME`_comms.i2c_writeCmd = comms->i2c_writeCmd;
  `$INSTANCE_NAME`_comms.i2c_writeArray = comms->i2c_writeArray;
  `$INSTANCE_NAME`_comms.i2c_read = comms->i2c_read;
    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_validateComms()
****************************************************************************//**
* \brief
*  Validate the communication structure
*
*
* \return
*  Error of the validation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_validateComms(void) {
  if(
    `$INSTANCE_NAME`_comms.i2c_write == NULL ||
    `$INSTANCE_NAME`_comms.i2c_writeCmd == NULL ||
    `$INSTANCE_NAME`_comms.i2c_writeArray == NULL ||
    `$INSTANCE_NAME`_comms.i2c_read == NULL
  ){ return `$INSTANCE_NAME`_ERR_COMMS; }
  return ZERO;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_start()
****************************************************************************//**
* \brief
*  Turns on the HT16 system clock, enables the display, and clears al the segments
*
* \param addr
*   I2C Address of the device 
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_start(uint8_t addr){
  /* validate the communication structure */
  uint32_t error = `$INSTANCE_NAME`_validateComms();
  if(error) {return error;}
  /* Turn the HT16 system clock on */
  error = `$INSTANCE_NAME`_comms.i2c_writeCmd(addr, `$INSTANCE_NAME`_CMD_SYS_CLCK_ON);
  /* Turn the display on */
  error |= `$INSTANCE_NAME`_comms.i2c_writeCmd(addr, `$INSTANCE_NAME`_CMD_DISP_ON);
  error |= `$INSTANCE_NAME`_clearDisplay(addr);
  return error; 
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_clearDisplay()
****************************************************************************//**
* \brief
*  Turns off all segments of the display. Does not disable the system. 
*
* \param addr
*   I2C Address of the device 
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_clearDisplay(uint8_t addr) {
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Clear the display  */
    uint8_t clearArray[`$INSTANCE_NAME`_NUM_DIGITS] = {ZERO};
    return `$INSTANCE_NAME`_comms.i2c_writeArray(addr, `$INSTANCE_NAME`_ADDR_DISPLAY_DATA, clearArray, `$INSTANCE_NAME`_NUM_DIGITS);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeAllSegments()
****************************************************************************//**
* \brief
*  Writes all registers of the display to a given value
*
* \param addr
*   I2C Address of the device 
*
* \param val
*   Value to write to the registers
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeAllSegments(uint8_t addr, uint8_t val){
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Write the same value to all digits */
    uint8_t segArray[`$INSTANCE_NAME`_NUM_DIGITS];
    memset(segArray, val, `$INSTANCE_NAME`_NUM_DIGITS);
    return `$INSTANCE_NAME`_comms.i2c_writeArray(addr, `$INSTANCE_NAME`_ADDR_DISPLAY_DATA, segArray, `$INSTANCE_NAME`_NUM_DIGITS);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeDigitRaw()
****************************************************************************//**
* \brief
*  Writes a raw value to a single digit of the display
*
* \param addr
*   I2C Address of the device 
*
* \param position
*   Position of the digit on the display to write to
*
* \param val
*   Value to write to the registers
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeDigitRaw(uint8_t addr, uint8_t position, uint8_t val) {
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Write the raw digit value */
    return `$INSTANCE_NAME`_comms.i2c_write(addr, `$INSTANCE_NAME`_positionArray[position], val);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeDigitNum()
****************************************************************************//**
* \brief
*  Displays a decimal digit at the given position
*
* \param addr
*   I2C Address of the device 
*
* \param position
*   Position of the digit on the display to write to
*
* \param digit
*   Value of the digit to display
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeDigitNum(uint8_t addr, uint8_t position, uint8_t digit) {
      /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}

    /* Ensure valid position */
    if(position > `$INSTANCE_NAME`_POSITION_MAX) {
        return `$INSTANCE_NAME`_ERR_RANGE;
    }
    /* Ensure valid number */
    if(digit > `$INSTANCE_NAME`_DIGIT_MAX) {
        return `$INSTANCE_NAME`_ERR_RANGE;
    }
    return `$INSTANCE_NAME`_comms.i2c_write(addr,  `$INSTANCE_NAME`_positionArray[position], `$INSTANCE_NAME`_digitArray[digit]);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeDigitNum()
****************************************************************************//**
* \brief
*  Displays a decimal digit at the given position
*
* \param addr
*   I2C Address of the device 
*
* \param position
*   Position of the digit on the display to write to
*
* \param digit
*   Value of the digit to display
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeDigitChar(uint8_t addr, uint8_t position, uint8_t digit){
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Ensure valid position */
    if(position > `$INSTANCE_NAME`_POSITION_MAX) {
        return `$INSTANCE_NAME`_ERR_RANGE;
    }
    /* Ensure valid number */
    int8_t displayChar = digit - `$INSTANCE_NAME`_OFFSET_CHAR;
    if(displayChar > `$INSTANCE_NAME`_DIGIT_MAX || displayChar < `$INSTANCE_NAME`_DIGIT_MIN) {
        return `$INSTANCE_NAME`_ERR_RANGE;
    }
    return `$INSTANCE_NAME`_comms.i2c_write(addr,  `$INSTANCE_NAME`_positionArray[position], `$INSTANCE_NAME`_digitArray[displayChar]);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeDisplayString()
****************************************************************************//**
* \brief
*  Writes the display from a four character string
*
* \param addr
*   I2C Address of the device 
*
* \param array
*   Pointer to array containing the four digits to write
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeDisplayString(uint8_t addr, char* array) {
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Write the string to the displays */
    uint8_t i;
    for(i=ZERO; i< `$INSTANCE_NAME`_POSITION_MAX; i++) {
        error = `$INSTANCE_NAME`_writeDigitChar(addr, i, array[i]);
        if(error) {break;}
    }
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeDisplayNum()
****************************************************************************//**
* \brief
*  Writes the display based on a number between 0 and 9999
*
* \param addr
*   I2C Address of the device 
*
* \param array
*   Pointer to array containing the four digits to write
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeDisplayNum(uint8_t addr, uint16_t val) {
      /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}

    if(val > `$INSTANCE_NAME`_DISPLAY_VAL_MAX) {
        return `$INSTANCE_NAME`_ERR_RANGE;
    }
    uint8_t i;
    for(i = `$INSTANCE_NAME`_POSITION_MAX - INDEX_ZERO_CORRECT; i>=ZERO; i--) {
//        error = `$INSTANCE_NAME`_writeDigitNum(addr, `$INSTANCE_NAME`_positionArray[i], val % TEN);
        error = `$INSTANCE_NAME`_writeDigitNum(addr, i, val % TEN);
        
        val /= TEN;
        if(error) {break;}
    }
    return error;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_writeDisplayArray()
****************************************************************************//**
* \brief
*  Writes the display from an aray
*
* \param addr
*   I2C Address of the device 
*
* \param array
*   Pointer to array containing the four values to write
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_writeDisplayArray(uint8_t addr, uint8_t *array){
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Write the string to the displays */
    uint8_t i;
    for(i=ZERO; i< `$INSTANCE_NAME`_POSITION_MAX; i++) {
        error = `$INSTANCE_NAME`_writeDigitRaw(addr, i, array[i]);
        if(error) {break;}
    }
    return error;
    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_blinkState()
****************************************************************************//**
* \brief
*  Sets the blinking frequency of a display
*
* \param addr
*   I2C Address of the device 
*
* \param rate
*   Blink Rate
*
* \return
*  Result of the I2C Write operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_blinkState(uint8_t addr,`$INSTANCE_NAME`_BLINK_T rate) {
    uint8_t cmd = `$INSTANCE_NAME`_CMD_DISP_ON;
    switch(rate){
        case BLINK_SOLID: {
            cmd = `$INSTANCE_NAME`_CMD_DISP_ON;
            break;
        }
        case BLINK_2HZ: {
            cmd = `$INSTANCE_NAME`_CMD_DISP_BLINK_2HZ;
            break;
        }
        case BLINK_1HZ: {
            cmd = `$INSTANCE_NAME`_CMD_DISP_BLINK_1HZ;
            break;    
        }
        case BLINK_HALFHZ: {
            cmd = `$INSTANCE_NAME`_CMD_DISP_BLINK_HALF_HZ;
            break;    
        }
    }
    return `$INSTANCE_NAME`_comms.i2c_writeCmd(addr, cmd); 
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_readDigit()
****************************************************************************//**
* \brief
*  Read the value of a given digit from the display
*
* \param addr [in]
*   I2C Address of the device 
*
* \param position [in]
*   Position of the digit on the diplay
*
* \param result [out]
*   Pointer to the location to place the result
*
* \return
*  Result of the I2C read operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_readDigit(uint8_t addr, uint8_t position, uint8_t *result){
    /* validate the communication structure */
    uint32_t error = `$INSTANCE_NAME`_validateComms();
    if(error) {return error;}
    /* Ensure valid position */
    if(position > `$INSTANCE_NAME`_POSITION_MAX) {
        return `$INSTANCE_NAME`_ERR_RANGE;
    }
    uint8_t regAddr = `$INSTANCE_NAME`_positionArray[position];
    return `$INSTANCE_NAME`_comms.i2c_read(addr, regAddr, result);
        
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_readDisplay()
****************************************************************************//**
* \brief
*  Read the current value in the displays 
*
* \param displayAddr [in]
*   Address of display
* 
* \param resultArray [out]
*   Pointer to array of width 4 to place results
*
* \return
*  Error of the read procedure
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_readDisplay(uint8_t displayAddr, uint8_t *resultArray){
    uint32_t error = ZERO;
    uint8_t i;
    for(i=ZERO; i <= `$INSTANCE_NAME`_POSITION_MAX; i++){
       error |= HT16_readDigit(displayAddr, i, &resultArray[i]);
    }

    return error;
}

/* [] END OF FILE */
