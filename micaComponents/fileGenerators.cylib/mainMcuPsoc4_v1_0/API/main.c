/***************************************************************************
*                                 MICA  © `$year`
*                           MIT BioInstrumentation Lab
*
* File: main.c
* Workspace: `$workspaceName`
* Project: `$projectName`
* Version: `$fileVersion`
* Authors: `$author`
* 
* PCB: `$pcbName` `$pcbVersion`
* PSoC: `$psocPartNumber`
*
* Brief:
*   This is the top-level application file for `$pcbName`.
*
* `$year`.`$month`.`$day` `$initials` - Document Created
********************************************************************************/
#include <stdbool.h>
#include "project.h"


/* ####################### BEGIN PROGRAM CONFIGURATION ###################### */

//#define MICA_DEBUG
/* ---------------- DEBUG CASE ----------------
* Uncomment ONE of the following
* Debugging will only occur when MICA_DEBUG is defined
*/
#ifdef MICA_DEBUG
//    #define MICA_DEBUG_LEDS           /* Test the onboard RGB LED */
//    #define MICA_UART_USB_TX        /* Send data through the UART to test connectivity */
//    #define MICA_DEBUG_ECHO           /* Echo to the USB UART */
//    #define MICA_DEBUG_BTN            /* Check the user button */
    #define MICA_DEBUG_MCUPSOC4         /* Run the full hardware testing suite */
#endif
/* -------------- END DEBUG CASE --------------  */
   

//#define MICA_TEST
/* ---------------- TEST CASE -----------------
* Uncomment ONE of the following
* Testing will only occur when MICA_TEST is defined
*/
#ifdef MICA_TEST
    #define MICA_TEST_case      /* Test Description */
#endif
/* -------------- END TEST CASE ---------------  */


/* ############################# BEGIN PROGRAM ############################## */
/* Interrupt Service Routines */
void ISR_isrName(void);

/* Global Variables */
volatile bool flag_isrFlag = false;

/* Main Program */
#if !defined(MICA_DEBUG) && !defined(MICA_TEST)
/*******************************************************************************
* Function Name: main()
********************************************************************************
* Summary:
*   The top-level application function for the project.
*
*******************************************************************************/
int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /* Infinite Loop */
    for(;;) {
        
    }
}
#endif /* !defined(MICA_DEBUG) && !defined(MICA_TEST) */
/* End Main Program */

/* ############################ BEGIN DEBUGGER ############################## */
#ifdef MICA_DEBUG
/*******************************************************************************
* DEBUGGER: main()
********************************************************************************
* Summary:
*   Debugging function for the PCB hardware
*******************************************************************************/
int main(void){
    #warning "MICA_DEBUG is enabled"
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    #ifdef MICA_DEBUG_LEDS
        /* Test the onboard LEDs
        Expeted outcome: 
        0. All LEDs off
        1. Red LED on
        2. Green LED on
        3. Blue LED on
        4. Yellow (RB)
        5. Cyan (BG)
        6. Magenta (RG)
        7. White (RGB) LEDs on
        */
        /* Infinite loop */
        LEDS_Test(MICA_TEST_INFINITE);
    /* End MICA_DEBUG_LEDS */
    #elif defined MICA_UART_USB_TX
        /* Test the Transmit portion of the UART
        Expected outcome:
        UART constantly writes out the compile date 
        and time. 
        */
        /* Start the UART */
        UART_USB_Start();
        /* Turn on the Green LED */
        LEDS_Write(LEDS_ON_GREEN);
        /* Loop count */
        uint8 i = ZERO;
        /* Run the transmit test indefinitely */
        for(;;){
            /* Log, if eneabled */
            usbUart_log("Log: %x ", i++);
            /* Display the compile date and time */
            usbUart_txTest(MICA_TEST_ONCE);
            /* Toggle Blue LED */
            LEDS_B_Toggle();
        }
    /* End MICA_UART_USB_TX */
    #elif (defined MICA_DEBUG_ECHO)
        /* Echo by polling the USB UART. Excpected outcome:
        *  0. Byte written via USB are echoed back
        *  1. Blue Led Toggles on each key press */
        LEDS_Write(LEDS_ON_GREEN);
        /* Start the component */
        UART_USB_Start();
        /* Infinite Loop */
        uint8 i = ZERO;
        for(;;) {
            /* Check the buffer for data */
            char data = usbUart_getChar();
            if(data) {
                /* Echo Data back */
                usbUart_putChar(data);
                /* Log if enabled */
                usbUart_log("\r\nThis is a log:%x\r\n", i++);
                /* Toggle the Blue led */
                LEDS_B_Toggle();  
            }
        }
    /* End MICA_DEBUG_ECHO */
    #elif defined MICA_DEBUG_BTN
        /* Test the user push button
        Expected outcome: 
        0. Green LED on
        1. User depresses button
        2. R+G LEDs on 
        3. User releases button
        4. Green LED on */
        LEDS_G_Write(LEDS_ON);
        /* Infinite Loop */
        for(;;) {
            /* Test the user push button */
            bool btnPressed = button_pin_Read();
            /* Check if Btn was pressed */
            if (btnPressed) {
                /* R+G on if pressed */
                LEDS_R_Write(LEDS_ON);
            } else{
                /* G on if not pressed */
                LEDS_R_Write(LEDS_OFF);
            }
        }
    /* end MICA_DEBUG_BTN */
    #elif defined MICA_DEBUG_MCUPSOC4         
        /* Run the full hardware testing suite */
       
        /* Startup sequence */
        LEDS_Write(LEDS_ON_WHITE);
        Button_EnableBtnInterrupts();
        usbUart_Start();
        MICA_delayMs(MICA_DELAY_MS_SEC_HALF);
        LEDS_Write(LEDS_ON_BLUE);
        
        /* Print Welcome message */
        usbUart_clearScreen();
        usbUart_printHeader(__TIME__, __DATE__, "mcuPSoC4 Board Testing");
        
        /* Infinite Loop */
        for(;;) {
            uint8_t data = usbUart_getChar();
            if(data) {
                usbUart_putChar(data);
                LEDS_R_Toggle();
            }
            if(data==' ' || Button_wasButtonReleased() ){
                usbUart_print("Resetting...");
                MICA_delayMs(MICA_DELAY_MS_SEC_TENTH);
                MICA_softwareReset();  
            }
        }
    #else
        #error "At least ONE MICA_DEBUG_<case> must be defined if MICA_DEBUG is defined"
    #endif /* End MICA_DEBUG_<case> */
    /* Infinite loop */
    for(;;){}
}
#endif /* MICA_DEBUG */

/* ############################# BEGIN TESTER ############################### */
#ifdef MICA_TEST
/*******************************************************************************
* TESTER: main()
********************************************************************************
* Summary:
*   Test functions for features and algorithms
*******************************************************************************/
int main (void) {
    #warning "MICA_TEST is enabled"
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    #ifdef MICA_TEST_case
        /* Test descriptions */
    /* End MICA_TEST_case*/
    #else 
        #error "At least ONE MICA_TEST_<case> must be defined if MICA_TEST is defined"
    #endif /* End MICA_TEST_<case> */    
    for(;;){}
}    
#endif /* MICA_TEST */

/* ####################### BEGIN FUNCTION DEFINITIONS ####################### */

/*******************************************************************************
* ISR Name: ISR_isrName()
********************************************************************************
* Summary:
*   <isrUserCase>
* Interrupt: 
*   <nameOfInterruptComponent>
*
*******************************************************************************/
void ISR_isrName(void){
    /* Clear the Interrupt */
    
    /* Set the flag */
    flag_isrFlag = true;
}

/* [] END OF FILE */
