/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: template_testCase.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Starter code for creating test cases with MICA_TESTT
*
* 2019.03.01  - Document Created
********************************************************************************/


        /* Unit tests for MICA Errors */
        LEDS_Write(LEDS_ON_GREEN);
        usbUart_Start();
        usbUart_clearScreen();

        /* Print Program Header */
        usbUart_printHeader(__TIME__, __DATE__, "      `$testDescription` ");
        /* Set the Print function */
        testRunner_setPrintFunction(usbUart_print);
        /* ### Buffer Generate Test Suite ### */
        {

            /* Initialize test objects */
            usbUart_print("\r\n*** `$testSuiteName` ***\r\n");
            
            /* Run tests */
    //        testRunner_run(bool testResults) 

          
            /* Clean Up */
        }
        
        /* Display test suite results */
        testRunner_printCount();
        /* Enable the button */
        usbUart_print("Press any key to re-run tests\r\n");
        /* Infinite loop */
        for(;;) {
            /* Reset on buton press */
            if(usbUart_getChar()){
                /*Reset the device*/
                MICA_softwareReset();   
            }
        }
        
       

/* [] END OF FILE */
