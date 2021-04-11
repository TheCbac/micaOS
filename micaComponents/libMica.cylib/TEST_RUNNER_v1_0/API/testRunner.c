/***************************************************************************
*                                       MICA
* File: `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Source for the test runner to run unit test
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.09.07 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"


static uint16_t passCount = ZERO;
static uint16_t testCount = ZERO;
void (*printFunction)(char *pszFmt, ...) = NULL;

/* Macro to test that print function has been set  */
#define `$INSTANCE_NAME`_print(...) do {\
        if(printFunction != NULL){\
            printFunction(__VA_ARGS__);\
        }\
    } while(0)


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_run()
****************************************************************************//**
* \brief
*  Records the results of a unit test
*
* \param passCount
*   Pointer to the number of test that have passed
*
* \param testCount
*   Pointer to the number of test run
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_run(bool testResult) {
    testCount++;
    passCount += testResult;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_resetCount()
****************************************************************************//**
* \brief
*  Resets the recorded values of the test
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_resetCount(void) {
    testCount = ZERO;
    passCount = ZERO;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_printCount()
****************************************************************************//**
* \brief
*  Displays the results of the testing suite
*
* \param testName
*   Name of the test in question
*
* \param error
*   Actual value of error
*
* \param expectedResult, 
*   Expected value of the error
*
* \param optErr
*   An optional Error to display if the test failed for reasons other
*   than a non-zero error code
*
* \return
*   Whether of not the test passed
*******************************************************************************/
void `$INSTANCE_NAME`_printCount(void){
    `$INSTANCE_NAME`_print("\r\n\n> Passed %d/%d tests\r\n", passCount, testCount);
    /* Reset count */
    `$INSTANCE_NAME`_resetCount();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_printResults()
****************************************************************************//**
* \brief
*  Displays the results of the test
*
* \param testName
*   Name of the test in question
*
* \param error
*   Actual value of error
*
* \param expectedResult, 
*   Expected value of the error
*
* \param optErr
*   An optional Error to display if the test failed for reasons other
*   than a non-zero error code
*
* \return
*   Whether of not the test passed
*******************************************************************************/
bool `$INSTANCE_NAME`_printResults(char* testName, uint32_t error, uint32_t expectedResult, char* optErr){
    bool result = false;
    /* Print results */
    `$INSTANCE_NAME`_print(testName);
    `$INSTANCE_NAME`_print(": ");
    if(error != expectedResult){
        `$INSTANCE_NAME`_print("Failed, Expected: 0x%x, Got: 0x%x\r\n", expectedResult, error);   
    } else if(optErr[0] != ZERO){
        `$INSTANCE_NAME`_print("Failed: ");
        `$INSTANCE_NAME`_print(optErr);
        `$INSTANCE_NAME`_print("\r\n");
    } else {
        `$INSTANCE_NAME`_print("Passed\r\n");   
        result = true;
    }
    return result;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_setPrintFunction()
****************************************************************************//**
* \brief
*  Sets the function to use when printing the test results
*
* \param fn
*   Pointer to the function to use
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_setPrintFunction( void (*fn)(char *pszFmt, ...) ) {
    printFunction = fn;
}


/* [] END OF FILE */
