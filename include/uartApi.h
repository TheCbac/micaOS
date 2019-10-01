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
  uint32_t uart_print(COMMS_UART_S* uart, uint8_t *pszFmt,...);
  uint32_t uart_printHeader(COMMS_UART_S* uart, uint8_t* name, uint8_t *date, uint8_t* time);
  uint32_t uart_compareReg(COMMS_UART_S* uart, uint8_t* name, uint16_t actual, uint16_t expected);
  uint32_t uart_printErrorStatus(COMMS_UART_S* uart, uint8_t* name, uint32_t error, uint32_t subError);
  uint32_t uart_hex2Ascii(uint8_t hex, uint8_t* ascii);
  


  #define uart_printLn(...) do {uart_print(__VA_ARGS__); uart_print("\r\n"); } while(0) 
    
#endif /* UART_API_H */
/* [] END OF FILE */
