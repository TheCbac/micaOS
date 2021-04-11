/***************************************************************************
*                                       MICA
* File: BMX055.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Header for interacting with the Bosch BMX055 IMU
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.13 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included Files
    ***************************************/
    #include "cytypes.h"
    #include "micaCommon.h"
    #include "`$INSTANCE_NAME`_Acc.h"
    #include "`$INSTANCE_NAME`_Gyr.h"
    #include "`$INSTANCE_NAME`_Mag.h"
    #include "`$INSTANCE_NAME`_Common.h"
    
    /***************************************
    * Enumerated Types
    ***************************************/
    
    /***************************************
    * Structs
    ***************************************/


    /***************************************
    * Macro Definitions
    ***************************************/
   
    /***************************************
    *        Function Prototypes
    ***************************************/
    /* Device wide Functions */
    uint32 `$INSTANCE_NAME`_Start(`$INSTANCE_NAME`_STATE_T* deviceState);        /**< Start the IMU (Acc, Gyr, Mag) */
    uint32 `$INSTANCE_NAME`_Stop(`$INSTANCE_NAME`_STATE_T* deviceState);         /**< Disable the IMU (Acc, Gyr, Mag)*/
    uint32 `$INSTANCE_NAME`_SetParameters(uint8 deviceAddr, uint8 numParams, uint8* registerList, uint8* registerVal); /**< Writes the parameters out to the device specified */

 

#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
