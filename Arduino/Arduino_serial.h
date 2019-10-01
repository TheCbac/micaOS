/***************************************************************************
*                                 MICA  © 2019
*
* File: Arduino_serial.h
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   
*
* <date>  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef ARDUINO_SERIAL_H
  #define ARDUINO_SERIAL_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaComms.h"
  /***************************************
  * Macro Definitions
  ***************************************/

  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t uartArduino_start(COMMS_UART_S* uart, uint32_t baud);
  uint32_t uartArduino_write(uint8_t val);                         /**< Write out a byte of data via UART */
  uint32_t uartArduino_print(uint8_t* str);                  /**< Write out a null-pointer string */
  uint32_t uartArduino_writeArray(uint8_t *array, uint16_t len);  /**< Write multiple registers */
  uint32_t uartArduino_read(uint8_t *result);                      /**< Read data from RX buffer */
  uint32_t uartArduino_readArray(uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */
  uint32_t uartArduino_getRxBufferSize(uint8_t *result);           /**< Retrieve number of bytes pending in RX buffer*/
  uint32_t uartArduino_getTxBufferSize(uint8_t *result); 
#endif /* ARDUINO_SERIAL_H */
/* [] END OF FILE */
