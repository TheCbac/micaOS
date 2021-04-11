/***************************************************************************
*                                       MICA
* File: `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Prototype definitions for the test runner
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.09.07 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include <stdbool.h>
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_MSG_NONE       ""
    /***************************************
    * Function Prototypes 
    ***************************************/
    void `$INSTANCE_NAME`_run(bool testResult);
    void `$INSTANCE_NAME`_resetCount(void);
    void `$INSTANCE_NAME`_printCount(void);
    bool `$INSTANCE_NAME`_printResults(char* testName, uint32_t error, uint32_t expectedResult, char* optErr);
    void `$INSTANCE_NAME`_setPrintFunction( void (*fn)(char *pszFmt, ...) );

    
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */