# 1 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
# 1 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
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
# 14 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
// #include "micaComms.h"
# 16 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 2
# 17 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 2

COMMS_UART_S uart;


// #define TEST_PRINT
// #define TEST_PRINT_STRING
// #define TEST_PRINT_BOOL
// #define TEST_PRINT_INT
// #define TEST_PRINT_CHAR



// #define TEST_PRINT_HEX

/*******************************************************************************

* Function Name: setup()

****************************************************************************//**

* \brief

*   One time setup function 

* 

*******************************************************************************/
# 38 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void setup(void){
  uartArduino_start(&uart, (115200));
# 71 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
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
      uart_print(&uart, "0x01: 0x%X\r\n", (uint32_t) 0x01);
      uint16_t testVal2 = 0xCC;
      uart_print(&uart, "0xCC: 0x%x\r\n", testVal2);
      uint8_t testVal3 = 0xA1;
      uart_print(&uart, "0xA1: 0x%x\r\n", testVal3);
# 94 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
      uart_print(&uart, "End test");





}


/*******************************************************************************

* Function Name: loop()

****************************************************************************//**

* \brief

*   Main function loop 

* 

*******************************************************************************/
# 110 "c:\\Users\\ccheney\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void loop(void) {

}

/* [] END OF FILE */
