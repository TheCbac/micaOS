#include <Arduino.h>
#line 1 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
#line 1 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
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
#include "Arduino_timing.h"
#include "uartApi.h"
#include "micaTiming.h"

COMMS_UART_S uart;
TIMING_S timing;

#define TEST
// #define TEST_PRINT
// #define TEST_PRINT_STRING
// #define TEST_PRINT_BOOL
// #define TEST_PRINT_INT
// #define TEST_PRINT_CHAR
// #define TEST_PRINT_HEX
// #define TEST_PRINT_API
#define TEST_PRINT_FLOAT
// #define TEST_UART_ECHO


// #define TEST_PRINT_HEX

/*******************************************************************************
* Function Name: setup()
****************************************************************************//**
* \brief
*   One time setup function 
* 
*******************************************************************************/
#line 44 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void setup(void);
#line 141 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void loop(void);
#line 44 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void setup(void){
  uartArduino_start(&uart, COMMS_DEFAULT_BAUD);
  timingArduino_start(&timing);

  #ifdef TEST
    #ifdef TEST_PRINT
      printHeader(&uart, "TEST_PRINT");

    #elif defined TEST_PRINT_STRING
      printHeader(&uart, "TEST_PRINT_STRING");

      print(&uart, "basic string\r\n");
      print(&uart, "ignore Percent: %\r\n");
      print(&uart, "String: %s", "test");
      print(&uart, "\r\nEnd test");

    #elif defined TEST_PRINT_BOOL
      printHeader(&uart, "TEST_PRINT_BOOL");

      print(&uart, "False: %b\r\n", false);
      print(&uart, "true: %b\r\n", true);
      print(&uart, "End test");

    #elif defined TEST_PRINT_INT
      printHeader(&uart, "TEST_PRINT_INT");

      print(&uart, "one: %i\r\n", 1);
      print(&uart, "eleven: %i\r\n", 11);
      print(&uart, "one hundred: %d\r\n", 121);
      print(&uart, "End test");

    #elif defined TEST_PRINT_CHAR
      printHeader(&uart, "TEST_PRINT_CHAR");

      print(&uart, "\'C\': %c\r\n", 'C');
      print(&uart, "End test");

    #elif defined TEST_PRINT_HEX
      printHeader(&uart, "TEST_PRINT_HEX");
      printLn(&uart, "0x01: 0x%x", 0x01);
      printLn(&uart, "0xAA: 0x%x", 0xAA);
      printLn(&uart, "0xF10C: 0x%x", 0xF10C);
      printLn(&uart, "0xABC123: 0x%X", 0xABC123);
      printLn(&uart, "0xABC123: 0x%X", 0xABC123);
      uint32_t testVal = 0x01;
      printLn(&uart, "0x01: 0x%x", testVal);
      printLn(&uart, "0x01: 0x%X", testVal);
      printLn(&uart, "0x01: 0x%x", 0x01);
      printLn(&uart, "0x10: 0x%X",  (uint32_t) 0x10);
      uint16_t testVal2 = 0xCC;
      printLn(&uart, "0xCC: 0x%x",  testVal2);
      uint8_t testVal3 = 0xA2;
      printLn(&uart, "0xA2: 0x%x",  testVal3);
      printLn(&uart, "Val 1: 0x%x, val2: 0x%x", 0x01, 0x02);

      printLn(&uart, "End test");

    #elif defined TEST_PRINT_API
      printHeader(&uart, "TEST_PRINT_API");
      uart1.uartState = &uart;
      uart1.print
    #elif defined TEST_PRINT_FLOAT
      printHeader(&uart, "TEST_PRINT_FLOAT");
      float val = 10.58;
      printLn(&uart, "10.58: %f", val);
      val = NAN;
      printLn(&uart, "NaN: %f", val);
      val = 1e10;
      printLn(&uart, "1E10: %f", val);
      val = -0.2565;
      printLn(&uart, "-0.256500: %f", val);
      printLn(&uart, "-0.26: %.2f", val);
      printLn(&uart, "-0.256: %.3f", val);
      val = 1050.025;
      printLn(&uart, "1050.025: %.3f", val);
      printLn(&uart, "1050.025000: %f", val);



    #elif defined TEST_UART_ECHO
      printHeader(&uart, "TEST_UART_ECHO");

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
  #ifdef TEST
    #if defined TEST_UART_ECHO
      uint8_t numAvail;
      uart.getRxBufferSize(&numAvail);
      if(numAvail) {
        uint8_t data;
        uart.read(&data);
        uart.write(data);
      }
      timing.delayMs(10);
    #endif /* TEST_CASE */
  #endif /* TEST */
}

/* [] END OF FILE */

