# 1 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
# 1 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
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
# 14 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
// #include "micaComms.h"
# 16 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 2
# 17 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 2
# 18 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 2
# 19 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 2

COMMS_UART_S uart;
TIMING_S timing;


// #define TEST_PRINT
// #define TEST_PRINT_STRING
// #define TEST_PRINT_BOOL
// #define TEST_PRINT_INT
// #define TEST_PRINT_CHAR
// #define TEST_PRINT_HEX
// #define TEST_PRINT_API

// #define TEST_UART_ECHO


// #define TEST_PRINT_HEX

/*******************************************************************************

* Function Name: setup()

****************************************************************************//**

* \brief

*   One time setup function 

* 

*******************************************************************************/
# 44 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void setup(void){
  uartArduino_start(&uart, (115200));
  timingArduino_start(&timing);
# 106 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
      printHeaderDT(&uart, "TEST_PRINT_FLOAT", "Oct  9 2019", "17:09:42");
      float val = 10.58;
      do {print(&uart, "10.58: %f", val); print(&uart, "\r\n"); } while(0);
      val = 
# 109 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino" 3
           __builtin_nan("")
# 109 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
              ;
      do {print(&uart, "NaN: %f", val); print(&uart, "\r\n"); } while(0);
      val = 1e10;
      do {print(&uart, "1E10: %f", val); print(&uart, "\r\n"); } while(0);
      val = -0.2565;
      do {print(&uart, "-0.256500: %f", val); print(&uart, "\r\n"); } while(0);
      do {print(&uart, "-0.26: %.2f", val); print(&uart, "\r\n"); } while(0);
      do {print(&uart, "-0.256: %.3f", val); print(&uart, "\r\n"); } while(0);
      val = 1050.025;
      do {print(&uart, "1050.025: %.3f", val); print(&uart, "\r\n"); } while(0);
      do {print(&uart, "1050.025000: %f", val); print(&uart, "\r\n"); } while(0);
# 131 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
}


/*******************************************************************************

* Function Name: loop()

****************************************************************************//**

* \brief

*   Main function loop 

* 

*******************************************************************************/
# 141 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
void loop(void) {
# 154 "c:\\Users\\ccheney\\Dropbox (MIT)\\git\\micaOS\\testApps\\serialArduino\\serialArduino.ino"
}

/* [] END OF FILE */
