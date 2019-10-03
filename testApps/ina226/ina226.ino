/***************************************************************************
*                                 MICA  © 2019
*
* File: INA226.ino
* Workspace: INA226
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   Testing of the INA226
*
* 2019.10.03 - Document Created
********************************************************************************/
#include "micaComms.h"
#include "Arduino_serial.h"
#include "Arduino_i2c.h"
#include "uartApi.h"
#include "INA226.h"

/* Communication structures */
COMMS_UART_S uart;
COMMS_I2C_S i2c = {0};
/* State structs */
INA226_STATE_S inaState = {0};


/* Uncomment TEST and one of the test cases at a time */
#define TEST
/***** Test Cases *****/
// #define TEST_I2C_COMMS
#define TEST_INA_START
// #define TEST_PRINT_STRING

/*******************************************************************************
* Function Name: setup()
****************************************************************************//**
* \brief
*   One time setup function 
* 
*******************************************************************************/
void setup(void){
  /* Configure states */
  inaState.i2c = &i2c;
  inaState.deviceAddr = 0x40;
  /* Start communications */
  uint32_t error = COMMS_ERROR_NONE; 
  error |= uartArduino_start(&uart, COMMS_DEFAULT_BAUD);
  error |= i2cArduino_start(&i2c);

  #ifdef TEST
    #ifdef TEST_I2C_COMMS /* Test the I2C functionality */
    printHeader(&uart, "TEST_I2C_COMMS");
    COMMS_I2C_S i2cTest = {0};
    uint32_t comError =Comms_validateI2C(&i2cTest);
    printErrorStatus(&uart, "I2C 0-Initialization (Should fail)", comError, 0);

    COMMS_I2C_S i2cTest2;
    comError =Comms_validateI2C(&i2cTest);
    printErrorStatus(&uart, "I2C non-Initialization (Should fail)", comError, 0);

    comError =Comms_validateI2C(0);
    printErrorStatus(&uart, "Null i2c (Should fail)", comError, 0);

    #elif defined TEST_INA_START /* test the starting the INA226 */
      printHeader(&uart, "TEST_INA_START");
      /* Start the device */
      error = INA226_start(&inaState);
      printErrorStatus(&uart, "INA226 Start", error, inaState.error);
      
      printLn(&uart, "Finished");

    #elif defined TEST_PRINT_STRING
      printHeader(&uart, "TEST_PRINT_STRING");

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
