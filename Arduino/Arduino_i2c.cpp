/***************************************************************************
*                                 MICA  © 2019
*
* File: i2c_Arduino.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
* 
*
* Brief:
*   Wrapper class that provides a generic I2C interface for Arduino,
*   using the Wire library.
*
* 2019.04.22  - Document Created
********************************************************************************/
#include "Arduino_i2c.h"
#include "Wire.h"


/*******************************************************************************
* Function Name: i2cArduino_start()
****************************************************************************//**
* \brief
*  Wire to generic I2C Start Wrapper
*  Starts the I2C bus
*
* \param i2c
*   Pointer to the generic COMMS_I2C_S to register the functions.
*
* \return
* An error code with the result of the start procedure 
*******************************************************************************/
uint32_t i2cArduino_start(COMMS_I2C_S *i2c){
  /* Register the Arduino commands with the COMMS struct */
  i2c->write = i2cArduino_write;
  i2c->writeCmd = i2cArduino_writeCmd;
  i2c->writeArray = i2cArduino_writeArray;
  i2c->read = i2cArduino_read;
  i2c->readArray = i2cArduino_readArray;
  /* Start the bus */
  Wire.begin();
  return COMMS_ERROR_NONE;
}


/*******************************************************************************
* Function Name: i2cArduino_write()
****************************************************************************//**
* \brief
*  Wire to generic I2C Write Wrapper
*  Writes a byte to data to a given register of the target I2C slave 
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param regAddr
*  Address of register to write to for the slave device  
*       
* \param val
*  Byte of data to be written the slave's register
*
* \return
* An error code with the result of the Write procedure. 
*******************************************************************************/
uint32_t i2cArduino_write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val) {
  Wire.beginTransmission(deviceAddr);
  Wire.write(regAddr);
  Wire.write(val);
  Wire.endTransmission();
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name:  i2cArduino_writeCmd()
****************************************************************************//**
* \brief
*  Wire to generic I2C WriteCmd Wrapper 
*  Sends a command to the target device, with no corresponding data
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param cmd
*  Command to write
*       
* \return
* An error code with the result of the Write procedure. 
*
*******************************************************************************/
uint32_t i2cArduino_writeCmd(uint8_t deviceAddr, uint8_t cmd){
  Wire.beginTransmission(deviceAddr);
  Wire.write(cmd);
  Wire.endTransmission();
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name:  i2cArduino_writeArray()
****************************************************************************//**
* \brief
*  Wire to generic I2C Write array Wrapper
*  Writes multiple bytes of data out the a specified device
*   Buffer size is limited to 32 Bytes -> need to do multiple calls
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param regAddr
*  The starting address of the registers to write to
*
* \param array
*   Pointer to the array that contains the data to write
*
* \param len
*   The length of data to write out
*       
* \return
* An error code with the result of the Write procedure. 
*******************************************************************************/
uint32_t i2cArduino_writeArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len){
  uint32_t error = COMMS_ERROR_NONE;
  // if(len >= I2C_ARDUINO_LEN_ARRAY){
  //   error = COMMS_ERROR_RANGE;
  // } else {
    // Wire.beginTransmission(deviceAddr);
    // Wire.write(regAddr);
    // Wire.write(array, len);
    // Wire.endTransmission();
  // }
  return error;
}

/*******************************************************************************
* Function Name:  i2cArduino_read()
****************************************************************************//**
* \brief 
*   Wire to generic I2C Read Wrapper
*   Read a byte of data from a slave
*
* \param deviceAddr [in]
*   Address of the slave device
*
* \param regAddr [in]
*   Memory address of the register to be read
*
* \param readVal [out]
*   Pointer to varable to place result into. If the command fails this will be 
*   the I2C opcode associated with the error.
*
* \Return
*   Error associated with the read value
*******************************************************************************/
uint32_t i2cArduino_read(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result){
  Wire.beginTransmission(deviceAddr);
  Wire.write(regAddr);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddr, (uint8_t) 1);
  *result = Wire.read();
  return COMMS_ERROR_NONE;
}


/*******************************************************************************
* Function Name:  i2cArduino_readArray()
****************************************************************************//**
* \brief 
*   Wire to generic I2C Read Wrapper
*   Read a byte of data from a slave
*
* \param deviceAddr [in]
*   Address of the slave device
*
* \param regAddr [in]
*   Memory address of the register to be read
*
* \param resultArray [out]
*   Pointer to array to place result into. If the command fails this will be 
*   the I2C opcode associated with the error.
*
* \param len [in]
*   Number of bytes to read
*
* \Return
*   Error associated with the read value
*******************************************************************************/
uint32_t i2cArduino_readArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len){
  uint32_t error = 0;
  if(len >= I2C_ARDUINO_LEN_ARRAY){
    error = COMMS_ERROR_RANGE;
  } else {
    Wire.beginTransmission(deviceAddr);
    Wire.write(regAddr);
    Wire.endTransmission();
    Wire.requestFrom(deviceAddr, (uint8_t) len);
    uint16_t i;
    for(i=0; i<len; i++){
      resultArray[i] = Wire.read();
    }
  }{}
  return error;
}
/* [] END OF FILE */
