/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version 2.0
*
* \brief
*   Simple print functionality
*
* \date Date Created:  2017.12.19
* \date Last Modified: 2017.12.19
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include "cytypes.h"
    
    #define `$INSTANCE_NAME`_SCB_STATUS     (`$isScb`)
    
    #if (`$INSTANCE_NAME`_SCB_STATUS)
        #include "`$componentName`_SPI_UART.h"
    #else
        #include "`$componentName`.h"
    #endif /* End `isScb` */ 
    /***************************************
    * Function declarations 
    ***************************************/
    void `$INSTANCE_NAME`_print(char8 *pszFmt,...);
    void `$INSTANCE_NAME`_txTest(uint8 runs);
    void `$INSTANCE_NAME`_putString(char * str);
    void `$INSTANCE_NAME`_putChar(uint8_t byte);
    void `$INSTANCE_NAME`_putArray(uint8 * array, uint16 length);
    void `$INSTANCE_NAME`_printHeader(char* time, char* date, char * name);
    void `$INSTANCE_NAME`_dummyTxArray(uint8 * array, uint16 len);
    
    
    /* RX functions */
    #define `$INSTANCE_NAME`_RX_EN  `$rxEnabled`        /**< Is receiving enabled? */
    #if `$INSTANCE_NAME`_RX_EN
        uint32_t `$INSTANCE_NAME`_getRxBufferSize(void);
        uint8_t `$INSTANCE_NAME`_getChar(void);
    #endif /* `$INSTANCE_NAME`_RX_EN */
   
    
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_Start()            `$componentName`_Start()
    #define `$INSTANCE_NAME`_clearScreen()      `$INSTANCE_NAME`_log("\033[2J\033[1;1H")    /**< Clear the terminal screen */
    #define `$INSTANCE_NAME`_clearLine()        `$INSTANCE_NAME`_log("\033[1K\r")    /**< Clear the terminal screen */
    
    
    
    
    /* Logging */ 
    #define `$INSTANCE_NAME`_DEBUG_EN `$enableLogging`   /**< Is log printing enabled? */
    #if `$INSTANCE_NAME`_DEBUG_EN
        #define `$INSTANCE_NAME`_log(...) `$INSTANCE_NAME`_print(__VA_ARGS__)  /**< Log Function */
    #else
        #define `$INSTANCE_NAME`_log(...) do { (void)0; } while(0) /**< Without logging */
    #endif /* End `$INSTANCE_NAME`_DEBUG_EN  */

    
    #define `$INSTANCE_NAME`_printLn(...) do {`$INSTANCE_NAME`_print(__VA_ARGS__); `$INSTANCE_NAME`_print("\r\n"); } while(0)
    #define `$INSTANCE_NAME`_logLn(...) do {`$INSTANCE_NAME`_log(__VA_ARGS__); `$INSTANCE_NAME`_log("\r\n"); } while(0)
    
    
    /***************************************
    * Structures
    ***************************************/

    
    
#endif /* (`$INSTANCE_NAME`_H) */
/* [] END OF FILE */
