/***************************************************************************
*                                       MICA
* File:  `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Definitions for encoders
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.07.25 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "micaCommon.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_COUNT_INITITAL     (0x8000) /* Initial midpoint of the count*/
    /***************************************
    * Enumerated Types
    ***************************************/

    /***************************************
    * Structures
    ***************************************/

    /***************************************
    * Function Prototype
    ***************************************/
    void `$INSTANCE_NAME`_Start(void);
    uint32_t `$INSTANCE_NAME`_getEncoderCount(void);
    uint32_t `$INSTANCE_NAME`_resetEncoderCount(void);
    

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
