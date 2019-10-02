/***************************************************************************
*                                 MICA  © 2019
*
* File: uartApi.h
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   
*
* 2019.10.01  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef UART_API_H
  #define UART_API_H
  /***************************************
  * Included files
  ***************************************/
  #include <stdint.h>
  #include "micaComms.h"
  /***************************************
  * Macro Definitions
  ***************************************/
  #define CLEAR_SCREEN_CMD    "\033[2J\033[1;1H"

  /***************************************
  * Enumerated Types
  ***************************************/

  
  /***************************************
  * Structures
  ***************************************/
  
  /***************************************
  * Function declarations 
  ***************************************/
  uint32_t print(COMMS_UART_S* uart, const char *pszFmt,...);
  uint32_t printHeaderDT(COMMS_UART_S* uart, const char* name, const char *date, const char* time);
  uint32_t printErrorStatus(COMMS_UART_S* uart, const char* name, uint32_t error, uint32_t subError);
  uint32_t uart_hex2Ascii(uint8_t hex, uint8_t* ascii);
  uint32_t uart_compareReg(COMMS_UART_S* uart, const char* name, uint16_t actual, uint16_t expected);

  


  #define printLn(uart, ...) do {print(uart, __VA_ARGS__); print(uart, "\r\n"); } while(0) 
  #define printHeader(uart, name) printHeaderDT(uart, name, __DATE__, __TIME__)
    
#endif /* UART_API_H */
/* [] END OF FILE */
