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
    void `$INSTANCE_NAME`_getEncoderCounts(ENCODER_DUAL_T * encoderPtr) ;
    void `$INSTANCE_NAME`_resetEncoderCounts(ENCODER_DUAL_T * encoderPtr);

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
