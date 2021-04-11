/***************************************************************************
*                                 MICA  © 2018
*                           MIT BioInstrumentation Lab
*
* File: supportBleCallback.c
* Workspace: supportCube_v5
* Project: supportCube_v5.0
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB: supportCube v1.0.0
* PSoC: CYBLE-214015-01
*
* Brief:
*   BLE Callback application for the Support Cube
*
* 2018.10.19  - Document Created
********************************************************************************/
#include "supportBleCallback.h"

/*******************************************************************************
* Function Name: supportBleHandler()
****************************************************************************//**
* \brief
*  Bluetooth event handler for the support cube
*
* \param eventCode
*  The code indicating which event occured
*
* \param eventParam
*   Pointer to the parameters of the event. User must cast to the approprate type
*
* \return
*  None
*******************************************************************************/
void supportBleHandler(uint32_t eventCode, void *eventParam){
    /* Act depending on the event*/
    switch(eventCode){
        /**********************************************************
        *                       General Events
        ***********************************************************/
        /* Stack initialized */
        case CYBLE_EVT_STACK_ON:{
            break;
        }

        /**********************************************************
        *                       GAP Events
        ***********************************************************/
        /* A device was found from the scan */
        case CYBLE_EVT_GAPC_SCAN_PROGRESS_RESULT: {
            break;   
        }
        /* The scan was either started or stopped */
        case CYBLE_EVT_GAPC_SCAN_START_STOP: {
            break;    
        }
        /* Connected to the device */
        case CYBLE_EVT_GAP_DEVICE_CONNECTED: {
            break;   
        }
        /* A device was disconnected */
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:{
            break;   
        }
        /* Notification data received from server device */
        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF: {
            break;   
        }
        /* An unhandled event occured */
        default:{
            break;   
        }
    } /* End switch(eventCode) */
}
    

/* [] END OF FILE */
