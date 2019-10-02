/***************************************************************************
*                                 MICA  © 2019
*
* File: serialArduino.ino
* Workspace: serialArduino
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   Testing of the micaOS Serial functions
*
* 2019.10.02 - Document Created
********************************************************************************/
// #include "micaComms.h"
#include "Arduino_serial.h"
#include "uartApi.h"

COMMS_UART_S uart;

#define TEST
// #define TEST_PRINT
// #define TEST_PRINT_STRING
// #define TEST_PRINT_BOOL
// #define TEST_PRINT_INT
// #define TEST_PRINT_CHAR
// #define TEST_PRINT_HEX
#define TEST_PRINT_API


// #define TEST_PRINT_HEX

/*******************************************************************************
* Function Name: setup()
****************************************************************************//**
* \brief
*   One time setup function 
* 
*******************************************************************************/
void setup(void){
  uartArduino_start(&uart, COMMS_DEFAULT_BAUD);

  #ifdef TEST
    #ifdef TEST_PRINT
      uart_print(&uart, "TEST_PRINT");

    #elif defined TEST_PRINT_STRING
      Serial.println("TEST_PRINT_STRING");
      uart_print(&uart, "basic string\r\n");
      uart_print(&uart, "ignore Percent: %\r\n");
      uart_print(&uart, "String: %s", "test");
      uart_print(&uart, "\r\nEnd test");

    #elif defined TEST_PRINT_BOOL
      Serial.println("TEST_PRINT_BOOL");
      uart_print(&uart, "False: %b\r\n", false);
      uart_print(&uart, "true: %b\r\n", true);
      uart_print(&uart, "End test");

    #elif defined TEST_PRINT_INT
      Serial.println("TEST_PRINT_INT");
      uart_print(&uart, "one: %i\r\n", 1);
      uart_print(&uart, "eleven: %i\r\n", 11);
      uart_print(&uart, "one hundred: %d\r\n", 121);
      uart_print(&uart, "End test");

    #elif defined TEST_PRINT_CHAR
      Serial.println("TEST_PRINT_CHAR");
      uart_print(&uart, "\'C\': %c\r\n", 'C');
      uart_print(&uart, "End test");

    #elif defined TEST_PRINT_HEX
      Serial.println("TEST_PRINT_HEX");
      uart_print(&uart, "0x01: 0x%x\r\n", 0x01);
      uart_print(&uart, "0xAA: 0x%x\r\n", 0xAA);
      uart_print(&uart, "0xF10C: 0x%x\r\n", 0xF10C);
      uart_print(&uart, "0xABC123: 0x%X\r\n", 0xABC123);
      uart_print(&uart, "0xABC123: 0x%X\r\n", 0xABC123);
      uint32_t testVal = 0x01;
      uart_print(&uart, "0x01: 0x%x\r\n", testVal);
      uart_print(&uart, "0x01: 0x%X\r\n", testVal);
      uart_print(&uart, "0x01: 0x%x\r\n", 0x01);
      uart_print(&uart, "0x01: 0x%X\r\n",  (uint32_t) 0x01);
      uint16_t testVal2 = 0xCC;
      uart_print(&uart, "0xCC: 0x%x\r\n",  testVal2);
      uint8_t testVal3 = 0xA1;
      uart_print(&uart, "0xA1: 0x%x\r\n",  testVal3);
      uart_print(&uart, "End test");
    #elif defined TEST_PRINT_API
      Serial.println("TEST_PRINT_API");
      

    #else 
      #error "Must have a test case selected" 
    #endif
  #endif /* TEST */

}


/*******************************************************************************
* Function Name: loop()
****************************************************************************//**
* \brief
*   Main function loop 
* 
*******************************************************************************/
void loop(void) {

}

/* [] END OF FILE */
