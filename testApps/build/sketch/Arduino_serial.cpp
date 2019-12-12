/***************************************************************************
*                                 MICA  © 2019
*
* File: Arduino_serial.cpp
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   
*
* <date>  - Document Created
********************************************************************************/
#include "Arduino_serial.h"
#include "Arduino.h"

/*******************************************************************************
* Function Name: uartArduino_start()
****************************************************************************//**
* \brief Registers Serial functions
*
* \param uart [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_start(COMMS_UART_S* uart, uint32_t baud) {
  /* Register the Arduino commands and start */
  uart->write = uartArduino_write;
  uart->print = uartArduino_print;
  uart->writeArray = uartArduino_writeArray;
  uart->read = uartArduino_read;
  uart->readArray = uartArduino_readArray;
  uart->getRxBufferSize = uartArduino_getRxBufferSize;
  uart->getTxBufferSize = uartArduino_getTxBufferSize;
  Serial.begin(baud);
  return COMMS_ERROR_NONE;
}



/*******************************************************************************
* Function Name: uartArduino_write()
****************************************************************************//**
* \brief Registers Write out a byte of data via UART
*
* \param val [in]
*  Value to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_write(uint8_t val){
  Serial.write(val);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartArduino_print()
****************************************************************************//**
* \brief Write out a null-pointer string 
*
* \param str [in]
*  String to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_print(const char* str){
  Serial.print(str);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartArduino_writeArray()
****************************************************************************//**
* \brief Write out an array of data
*
* \param str [in]
*  String to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_writeArray(uint8_t *array, uint16_t len){
  Serial.write(array, len);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartArduino_read()
****************************************************************************//**
* \brief Returns a byte of data from the RX buffer
*
* \param result [out]
*  Pointer to the results structure
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_read(uint8_t *result){
  uint32_t error = COMMS_ERROR_NONE;
  int read = Serial.read();
  if(read < 0 ){
    error = COMMS_ERROR_READ;
    *result = 0;
  } else {
    *result = (uint8_t) read;
  }
  return error;
}


/*******************************************************************************
* Function Name: uartArduino_readArray()
****************************************************************************//**
* \brief Reads a specified number of bytes into the array
*
* \param resultArray [out]
*  Pointer to the results array
*
* \param len [in]
* Number of bytes to read
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_readArray(uint8_t *resultArray, uint16_t len){ 
  uint32_t error = COMMS_ERROR_NONE;
  Serial.readBytes(resultArray, len);
  return error;
}

/*******************************************************************************
* Function Name: uartArduino_getRxBufferSize()
****************************************************************************//**
* \brief Gets the number of bytes in the RX buffer
*
* \param resultArray [out]
*  Pointer to the results vale
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_getRxBufferSize(uint8_t *result) {
  uint32_t error = COMMS_ERROR_NONE;
  *result = Serial.available();
  return error;
}

/*******************************************************************************
* Function Name: uartArduino_getTxBufferSize()
****************************************************************************//**
* \brief Gets the number of bytes in the TX buffer
*
* \param resultArray [out]
*  Pointer to the results vale
*
* \return
*  Success
*******************************************************************************/
uint32_t uartArduino_getTxBufferSize(uint8_t *result){
  uint32_t error = COMMS_ERROR_NONE;
  *result = Serial.availableForWrite();
  return error;
}

/* [] END OF FILE */
