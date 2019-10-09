/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: PSoC_serial_swTx.c
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
*   API Wrapper for using a serial port on the PSoC using software transmit UART
*
* 2019.10.08  - Document Created
********************************************************************************/
#include "PSoC_serial_swTx.h"
#include "micaCommon.h"
#include "project.h"

/*******************************************************************************
* Function Name: uartPsocTx_start()
****************************************************************************//**
* \brief Registers Serial functions
*
* \param uart [in/out]
*  Pointer to the state struct
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_start(COMMS_UART_S* uart, uint32_t baud) {
  /* Baud rate set at compile time */
  (void) baud;
  /* Register the Arduino commands and start */
  uart->write = uartPsocTx_write;
  uart->print = uartPsocTx_print;
  uart->writeArray = uartPsocTx_writeArray;
  uart->read = uartPsocTx_read;
  uart->readArray = uartPsocTx_readArray;
  uart->getRxBufferSize = uartPsocTx_getRxBufferSize;
  uart->getTxBufferSize = uartPsocTx_getTxBufferSize;
  /* Start the serial port */
  uartUsb_Start();
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartPsocTx_write()
****************************************************************************//**
* \brief Registers Write out a byte of data via UART
*
* \param val [in]
*  Value to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_write(uint8_t val){
  uartUsb_PutChar(val);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartPsocTx_print()
****************************************************************************//**
* \brief Write out a null-pointer string 
*
* \param str [in]
*  String to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_print(const char* str){
  uartUsb_PutString(str);
  return COMMS_ERROR_NONE;
}

/*******************************************************************************
* Function Name: uartPsocTx_writeArray()
****************************************************************************//**
* \brief Write out an array of data
*
* \param str [in]
*  String to write out
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_writeArray(uint8_t *array, uint16_t len){
  uartUsb_PutArray(array, len);
  return COMMS_ERROR_NONE;
}


/*******************************************************************************
* Function Name: uartPsocTx_read()
****************************************************************************//**
* \brief Returns a byte of data from the RX buffer. Does nothing for 
* the Software TX UART
*
* \param result [out]
*  Pointer to the results structure
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_read(uint8_t *result){
  (void) result;
  return COMMS_ERROR_READ;
}


/*******************************************************************************
* Function Name: uartPsocTx_readArray()
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
uint32_t uartPsocTx_readArray(uint8_t *resultArray, uint16_t len){ 
  (void) resultArray;
  (void) len;
  return COMMS_ERROR_READ_ARRAY;
}

/*******************************************************************************
* Function Name: uartPsocTx_getRxBufferSize()
****************************************************************************//**
* \brief Gets the number of bytes in the RX buffer
*
* \param resultArray [out]
*  Pointer to the results vale
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_getRxBufferSize(uint8_t *result) {
  (void) result;
  return COMMS_ERROR_RXBUFFER;
}

/*******************************************************************************
* Function Name: uartPsocTx_getTxBufferSize()
****************************************************************************//**
* \brief Gets the number of bytes in the TX buffer
*
* \param resultArray [out]
*  Pointer to the results vale
*
* \return
*  Success
*******************************************************************************/
uint32_t uartPsocTx_getTxBufferSize(uint8_t *result){
  (void) result;
  return COMMS_ERROR_TXBUFFER;
}


/* [] END OF FILE */
