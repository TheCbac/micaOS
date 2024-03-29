/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: PSoC_serial.h
* Workspace: micaOS
* Project: micaOS
* Version: 5.0.0
* Authors: C. Cheney
* 
* PCB: N/A N/A
* PSoC: 
*
* Brief:
*   Header for PSoC_serial.c
*
* 2019.10.08  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef PSOC_SERIAL_H
  #define PSOC_SERIAL_H
  /***************************************
  * Included files
  ***************************************/
  #include "micaCommon_comms.h"    
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
  uint32_t uartPsoc_start(COMMS_UART_S* uart, uint32_t baud);
  uint32_t uartPsoc_write(uint8_t val);                         /**< Write out a byte of data via UART */
  uint32_t uartPsoc_print(const char* str);                  /**< Write out a null-pointer string */
  uint32_t uartPsoc_writeArray(uint8_t *array, uint16_t len);  /**< Write multiple registers */
  uint32_t uartPsoc_read(uint8_t *result);                      /**< Read data from RX buffer */
  uint32_t uartPsoc_readArray(uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */
  uint32_t uartPsoc_getRxBufferSize(uint8_t *result);           /**< Retrieve number of bytes pending in RX buffer*/
  uint32_t uartPsoc_getTxBufferSize(uint8_t *result); 
  
#endif /* PSOC_SERIAL_H */
/* [] END OF FILE */
