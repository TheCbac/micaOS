/***************************************************************************//**
* \file `$INSTANCE_NAME`.h
* \version 0.1.0
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
    /***************************************
    * Function declarations 
    ***************************************/
    void `$INSTANCE_NAME`_print(char8 *pszFmt,...);
    void `$INSTANCE_NAME`_txTest(uint8 runs);
    void `$INSTANCE_NAME`_putString(char * str);
    void `$INSTANCE_NAME`_putArray(uint8 * array, uint16 length);
    void `$INSTANCE_NAME`_printHeader(char* time, char* date, char * name);
    void `$INSTANCE_NAME`_dummyTxArray(uint8 * array, uint16 len);
    
    /***************************************
    * Macro Definitions
    ***************************************/
//    @TODO
    // #define  `$INSTANCE_NAME`_Start()
    #define `$INSTANCE_NAME`_clearScreen()  `$INSTANCE_NAME`_print("\033[2J\033[1;1H")    /**< Clear the terminal screen */
    /* TX Functions */
    #define `$INSTANCE_NAME`_putChar(ch) `$txFunction`(ch)  /**< Wrapper for UART TX function */
    
    /* RX functions */
    #define `$INSTANCE_NAME`_RX_EN  `$rxEnabled`        /**< Is receiving enabled? */
    #if `$INSTANCE_NAME`_RX_EN
        #define `$INSTANCE_NAME`_getChar() `$rxFunction`() /**< Wrapper for UART RX function */
    #endif /* `$INSTANCE_NAME`_RX_EN */
    
    /* Logging */ 
    #define `$INSTANCE_NAME`_DEBUG_EN `$enableLogging`   /**< Is log printing enabled? */
    #if `$INSTANCE_NAME`_DEBUG_EN
        #define `$INSTANCE_NAME`_log(...) `$INSTANCE_NAME`_print(__VA_ARGS__)  /**< Log Function */
    #else
        #define `$INSTANCE_NAME`_log(...) do { (void)0; } while(0) /**< Without logging */
    #endif /*  */

    
#endif /* (`$INSTANCE_NAME`_H) */
/* [] END OF FILE */
