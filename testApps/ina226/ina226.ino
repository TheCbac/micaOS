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
#define TEST_INA_ID
// #define TEST_INA_START_READBACK
// #define TEST_INA_WRITE
// #define TEST_PRINT_STRING
// #define TEST_INA_VBUS       /* Read and display the VBUS value  */
// #define TEST_INA_CURRENT       /* Read and display the Current value  */
// #define TEST_INA_FULL     /* Display all of the measurements for the device */



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
  inaState.maxCurrent = 0.5; 
  inaState.rShunt = 1.0;
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

    #elif defined TEST_INA_ID /* test the starting the INA226 */
      printHeader(&uart, "TEST_INA_ID");
      uint16_t readData = 0;
      error = INA226_readReg(&inaState, INA226_ADDR_ID_MFG, &readData); 
      printErrorStatus(&uart, "INA226 ID read", error, inaState.error);
      uart_compareReg(&uart, "MFG ID", readData, INA_ID_MFG_VAL);

      printLn(&uart, "Finished");

    #elif defined TEST_INA_START_READBACK /* test the starting the INA226 */
      printHeader(&uart, "TEST_INA_START_READBACK");
      /* Start the device */
      error = INA226_start(&inaState);
      printErrorStatus(&uart, "INA226 Start", error, inaState.error);

      /* Config value from the start function */
      uint16_t config = 0;
      config |= INA_CONFIG_AVG_16;
      config |= INA_CONFIG_VBUSCT_1100;
      config |= INA_CONFIG_VSHCT_1100;
      config |= INA_CONFIG_MODE_CONT_SH_BUS;
      config |= INA_CONFIG_MASK_RES1;

      uint16_t readData = 0;
      error = INA226_readReg(&inaState, INA226_ADDR_CONFIG, &readData);
      printErrorStatus(&uart, "Readback config", error, inaState.error);
      uart_compareReg(&uart, "Config Reg", readData, config);
      
      printLn(&uart, "Finished");

    #elif defined TEST_INA_WRITE
      printHeader(&uart, "TEST_INA_WRITE");

      error |= INA226_reset(&inaState);
      printErrorStatus(&uart, "Reset device", error, inaState.error);

      uint16_t readData = 0;
      error |= INA226_readReg(&inaState, INA226_ADDR_ID_DIE, &readData);
      printErrorStatus(&uart, "Read die ID", error, inaState.error);
      uart_compareReg(&uart, "Die ID", readData, INA_ID_DIE_VAL);

      error |= INA226_readReg(&inaState, INA226_ADDR_CALIBRATION, &readData);
      printErrorStatus(&uart, "Read calibration reg", error, inaState.error);
      uart_compareReg(&uart, "Calibration reg", readData, 0x00);

      error = INA226_writeReg(&inaState, INA226_ADDR_CALIBRATION, 0x0AA);
      printErrorStatus(&uart, "Write calibration reg", error, inaState.error);

      error |= INA226_readReg(&inaState, INA226_ADDR_CALIBRATION, &readData);
      printErrorStatus(&uart, "Readback calibration reg", error, inaState.error);
      uart_compareReg(&uart, "Calibration reg", readData, 0x00AA);

    #elif defined TEST_INA_VBUS       /* Read and display the VBUS value  */
      printHeader(&uart, "TEST_INA_VBUS");
      /* Start the device */
      error = INA226_start(&inaState);
      printErrorStatus(&uart, "INA226 Start", error, inaState.error);

    #elif defined TEST_PRINT_STRING
      printHeader(&uart, "TEST_PRINT_STRING");

    #elif defined TEST_INA_CURRENT       /* Read and display the Current value  */
      printHeader(&uart, "TEST_INA_VBUS");
      /* Start the device */
      error = INA226_start(&inaState);
      printErrorStatus(&uart, "INA226 Start", error, inaState.error);
    
    #elif defined TEST_INA_FULL     /* Display all of the measurements for the device */
      printHeader(&uart, "TEST_INA_FULL");
      /* Start the device */
      error = INA226_start(&inaState);
      printErrorStatus(&uart, "INA226 Start", error, inaState.error);
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
    uint32_t error;
    #ifdef TEST_INA_VBUS
      /* Read the bus Voltage */
      float vBus = 0;
      INA226_readVoltage_Bus(&inaState, &vBus);
      print(&uart, "BUS Voltage is: ");
      Serial.println(vBus);

      delay(1000);
    #elif defined TEST_INA_CURRENT       /* Read and display the Current value  */
      /* Read the Current */
      float current = 0;
      INA226_readCurrent(&inaState, &current);
      print(&uart, "BUS Current is: ");
      Serial.println(current, 4);

      delay(1000);

    #elif defined TEST_INA_FULL     /* Display all of the measurements for the device */
      float current, vBus, vShunt, power;
      INA226_readVoltage_Bus(&inaState, &vBus);
      INA226_readVoltage_Shunt(&inaState, &vShunt);
      INA226_readCurrent(&inaState, &current);
      INA226_readPower(&inaState, &power);

      print(&uart, "vBus: ");
      Serial.print(vBus, 6);
      Serial.println(" V");

      print(&uart, "vShunt: ");
      Serial.print(vShunt, 6);
      Serial.println(" V");

      print(&uart, "Current: ");
      Serial.print(current, 4);
      Serial.println(" A");

      print(&uart, "Power: ");
      Serial.print(power, 4);
      Serial.println(" W\r\n");

      delay(1000);
    #endif /* TEST_<case> */

  #endif /* TEST */

}

/* [] END OF FILE */
