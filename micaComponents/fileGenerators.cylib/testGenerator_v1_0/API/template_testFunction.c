/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: template_testFunction.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Specific test cases to run
*
* 2019.03.01  - Document Created
********************************************************************************/
#include "`$fileName`.h"
#include "`$testRunnerName`.h"
#include <stdio.h>
#include "project.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_<functionName>()
****************************************************************************//**
* \brief
*  <function description>
*
* \param <passed params>
*
* \param testName
*   Name of test
*
* \param expectedResult
*   The Error code of the expected result
*
* \return
*  Boolean indicating if the test passed
*******************************************************************************/
bool test_testName( char* testName, uint16 len, uint32_t expectedResult){
    /* Run Test */
//    uint32_t error = 
    /* Print results */
    bool result = testRunner_printResults(testName, error, expectedResult, testRunner_MSG_NONE);
    /* Destroy buffers */
    if(!error){
        // CleanUp
    }
    return result;
}

/* [] END OF FILE */
