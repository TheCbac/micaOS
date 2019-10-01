/***************************************************************************
*                                 MICA  © 2019
*
* File: uartApi.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   Conversions for writing out over the serial port
*
* 2019.10.01  - Document Created
********************************************************************************/
#include "uartApi.h"
#include "stdbool.h"

uint8_t hexAscii[HEX_VAL_MAX] = "0123456789ABCDEF";
/*******************************************************************************
* Function Name: uart_changeBase()
****************************************************************************//**
* \brief Changes a binary value to a hex ascii character 
*
* \param hex [in]
*  binary value of the hex digit (0-15)
*
* \param ascii [out]
*  Ascii value of the hex digit ('0' - 'F')
*
* \return
*   The error code of the operation
 *******************************************************************************/
uint32_t uart_hex2Ascii(uint8_t hex, uint8_t* ascii){
  uint32_t error = COMMS_ERROR_NONE;
  if(hex > HEX_VAL_MAX){
    error = COMMS_ERROR_VAL;
  } else {
    *ascii = hexAscii[hex];
  }
  return error;
}

/*******************************************************************************
* Function Name: uart_print()
****************************************************************************//**
*
* \brief Prints out the string
*
* \param pszFmt
*   Pointer to string, zero formatted. String to print out, accepts %d, %s, %x, %c
*
* \return
* The error code of the operation
 *******************************************************************************/
uint32_t uart_print(COMMS_UART_S* uart, uint8_t *pszFmt,...){
  uint32_t error = COMMS_ERROR_NONE;
  /* Validate  state */
  error = Comms_validateUart(uart);
  if(!error) {
    uint8_t *pszVal;
    uint32_t iVal, xVal, i = 0, buffer[12], index = 1;
    uint8_t cVal;
    uint32_t *pArg;
    pArg =(uint32_t *)&pszFmt;
    /* Iterate through string */
    while(*pszFmt) {
      /* Regular Character */
      if('%' != *pszFmt) {
        error |= uart->write(*pszFmt);
        pszFmt++;
        continue;
      }
      pszFmt++;
      /* Format a string */
      if(*pszFmt == 's') {
        pszVal = (uint8_t*)pArg[index++];
        for(; *pszVal != '\0'; pszVal++){
          error |= uart->write(*pszVal);
        }
        pszFmt++;
        continue;
      }
      /* Boolean */
      if(*pszFmt == 'b'){
        bool bVal = (bool) pArg[index++];
        if(bVal){
            uart->print("True");
        } else {
            uart->print("False");
        }
        pszFmt++;
        continue;
      }
      /* Format integer */
      if(*pszFmt == 'd' || *pszFmt == 'i') {
        iVal = pArg[index++];
        i = 0;
        do{
          buffer[i++] = iVal % 10;
          iVal /= 10;
        }while(iVal);
        while(i > 0){
          i--;
          uint8_t ascii = 0;
          error |= uart_hex2Ascii(buffer[i], &ascii);
          error |= uart->write(ascii);
        }
        pszFmt++;
        continue;
      }
      /* Character */
      if(*pszFmt == 'c') {
        cVal = (uint8_t)pArg[index++];
        error |= uart->write(cVal);
        pszFmt++;
        continue;
      }
      /* Hex val */
      if(*pszFmt == 'x') {
        xVal = pArg[index++];
        i = 0;
        do{
          buffer[i++] = xVal % HEX_VAL_MAX;
          xVal /= HEX_VAL_MAX;
        }while(xVal);
        if(i%2!=0){
          buffer[i++]=0;
        }
        if(i<2) {
          buffer[i++]=0;
        }

        while(i > 0){
          i--;
          uint8_t ascii = 0;
          error |= uart_hex2Ascii(buffer[i], &ascii);
          error |= uart->write(ascii);
        }
        pszFmt++;
        continue;
      }
      if(pszFmt == '\0'){
          break;
      }
    }
  }
  return error;
}



/*******************************************************************************
* Function Name: uart_printHeader()
****************************************************************************//**
*
* \brief Displays the program header
* 
* \param name
*    Name of the program to display 
*
* \param time
*    Pass in __TIME__ macro
*
* \param date
*    Pass in __DATE__ macro
*

*
* \return
* The error code of the operation
*******************************************************************************/
uint32_t uart_printHeader(COMMS_UART_S* uart, uint8_t* name, uint8_t *date, uint8_t* time){
  uint32_t error = COMMS_ERROR_NONE;
  error |= uart_print(uart, CLEAR_SCREEN_CMD);
  error |= uart_print(uart, "**************************************\r\n*");
  error |= uart_print(uart, "%s\r\n*\r\n* Compiled at: %s on %s", name, time, date);
  error |= uart_print(uart, "\r\n**************************************\r\n");
  return error;
}

/*******************************************************************************
* Function Name: uart_compareReg()
****************************************************************************//**
*
* \brief Prints the results of a register comparison
* 
* \param name
*    Name of the program to display 
*
* \param time
*    Pass in __TIME__ macro
*
* \param date
*    Pass in __DATE__ macro
*
*
* \return
* The error code of the operation
*******************************************************************************/
uint32_t uart_compareReg(COMMS_UART_S* uart, uint8_t* name, uint16_t actual, uint16_t expected){
  return uart_print(uart, "%s: Received: 0x%x; Expected: 0x%x", name, actual, expected);
}

/*******************************************************************************
* Function Name: uart_printErrorStatus()
****************************************************************************//**
*
* \brief Prints the results of a test
* 
* \param name [in]
*    Name of the program to display 
*
* \param error [in]
*    Possible error 
*
* \param subError [in]
*    Sub error code 
*
*
* \return
* The error code of the operation
*******************************************************************************/
uint32_t uart_printErrorStatus(COMMS_UART_S* uart, uint8_t* name, uint32_t error, uint32_t subError) {
  uint32_t e = COMMS_ERROR_NONE;
  if(error){
    e |= uart_print(uart, "Error %s: 0x%x suberror: 0x%x", name, error, subError);
  } else {
    e |= uart_print(uart, "Success: %s", name);
  }
  return e;
}


/* [] END OF FILE */
