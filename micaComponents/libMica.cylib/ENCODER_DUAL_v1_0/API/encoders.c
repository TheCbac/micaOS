/***************************************************************************
*                                       MICA
* File:  `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*  API for encoders
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.07.25 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_encoder_L.h"
#include "`$INSTANCE_NAME`_encoder_R.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
********************************************************************************
* Summary:
*   Starts the Dual quadrature component
*
* \return
*   None
*******************************************************************************/
void  `$INSTANCE_NAME`_Start(void) {
    /* Start the indicidual components */
    `$INSTANCE_NAME`_encoder_L_Start();
    `$INSTANCE_NAME`_encoder_R_Start();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getEncoderCounts()
********************************************************************************
* Summary:
*   Places the encoder counts into the specified struct
*
* \param encoderPtr
*   Pointer to the struct to place the reult in
*
* \return
*   None
*******************************************************************************/
void  `$INSTANCE_NAME`_getEncoderCounts(ENCODER_DUAL_T * encoderPtr) {
    /* Read the encoders and write to the pointer passed in */
    encoderPtr->leftCount = `$INSTANCE_NAME`_encoder_L_ReadCounter();
    encoderPtr->rightCount = `$INSTANCE_NAME`_encoder_R_ReadCounter();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_resetEncoderCounts()
********************************************************************************
* Summary:
*   Places the encoder counts into the specified struct
*
* \param encoderPtr
*   Pointer to the struct to place the reult in
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_resetEncoderCounts(ENCODER_DUAL_T * encoderPtr) {
    /* Reset hardware counter */
    `$INSTANCE_NAME`_encoder_L_WriteCounter(ZERO);
    `$INSTANCE_NAME`_encoder_R_WriteCounter(ZERO);  
    /* Reset the local count */
    encoderPtr->leftCount = ZERO;
    encoderPtr->rightCount = ZERO;
}

/* [] END OF FILE */
