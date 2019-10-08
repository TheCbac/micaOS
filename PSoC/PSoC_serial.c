/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: PSoC_serial.c
* Workspace: micaOS
* Project: micaOS
* Version: 5.0.0
* Authors: C. Cheney
* 
* PCB: N/A N/A
* mcuType: PSoC
* partNumber:N/A
*
* Brief:
*   API Wrapper for using a serial port on the PSoC
*
* 2019.10.08  - Document Created
********************************************************************************/
#include "PSoC_serial.h"
#include "micaCommon.h"
#include "project.h"

/*******************************************************************************
* Function Name: uartPsoc_start()
****************************************************************************//**
* \brief Registers Serial functions
*
* \param uart [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_start(COMMS_UART_S* uart, uint32_t baud) {
  /* Baud rate set at compile time */
  (void) baud;
  /* Register the Arduino commands and start */
  uart->write = uartPsoc_write;
  uart->print = uartPsoc_print;
  uart->writeArray = uartPsoc_writeArray;
  uart->read = uartPsoc_read;
  uart->readArray = uartPsoc_readArray;
  uart->getRxBufferSize = uartPsoc_getRxBufferSize;
  uart->getTxBufferSize = uartPsoc_getTxBufferSize;
  /* Start the serial port */
  uartUsb_Start();
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartPsoc_write()
****************************************************************************//**
* \brief Registers Write out a byte of data via UART
*
* \param val [in]
*  Value to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_write(uint8_t val){
  uartUsb_UartPutChar(val);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartPsoc_print()
****************************************************************************//**
* \brief Write out a null-pointer string 
*
* \param str [in]
*  String to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_print(const char* str){
  uartUsb_UartPutString(str);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartPsoc_writeArray()
****************************************************************************//**
* \brief Write out an array of data
*
* \param str [in]
*  String to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_writeArray(uint8_t *array, uint16_t len){
    uartUsb_SpiUartPutArray(array, len);
  return COMMS_ERROR_NONE;
}


/*******************************************************************************
* Function Name: uartPsoc_read()
****************************************************************************//**
* \brief Returns a byte of data from the RX buffer
*
* \param result [out]
*  Pointer to the results structure
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_read(uint8_t *result){
  uint32_t error = COMMS_ERROR_NONE;
  uint32_t read = uartUsb_UartGetChar();
  /* See if error flag is set */
  if(read & 0xFFFFFF00){
    error = COMMS_ERROR_READ;
    *result = 0;
  } else {
    *result = (uint8_t) read;
  }
  return error;
}


/*******************************************************************************
* Function Name: uartPsoc_readArray()
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
uint32_t uartPsoc_readArray(uint8_t *resultArray, uint16_t len){ 
  uint32_t error = COMMS_ERROR_NONE;
  uint16_t i;
  for(i = 0; i < len; i++){
    uint8_t readVal;
    error = uartPsoc_read(&readVal);
    if(error) {
      break;
    } else {
      resultArray[i] = readVal;
    }
  }
  return error;
}

/*******************************************************************************
* Function Name: uartPsoc_getRxBufferSize()
****************************************************************************//**
* \brief Gets the number of bytes in the RX buffer
*
* \param resultArray [out]
*  Pointer to the results vale
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_getRxBufferSize(uint8_t *result) {
  uint32_t error = COMMS_ERROR_NONE;
  *result = uartUsb_SpiUartGetRxBufferSize();
  return error;
}

/*******************************************************************************
* Function Name: uartPsoc_getTxBufferSize()
****************************************************************************//**
* \brief Gets the number of bytes in the TX buffer
*
* \param resultArray [out]
*  Pointer to the results vale
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsoc_getTxBufferSize(uint8_t *result){
  uint32_t error = COMMS_ERROR_NONE;
  *result = uartUsb_SpiUartGetTxBufferSize();
  return error;
}


/* [] END OF FILE */
