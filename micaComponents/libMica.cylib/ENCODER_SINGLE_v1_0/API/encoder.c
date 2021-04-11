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
#include "`$INSTANCE_NAME`_encoder.h"

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
    `$INSTANCE_NAME`_encoder_Start();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getEncoderCount()
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
uint32_t `$INSTANCE_NAME`_getEncoderCount(void) {
    /* Read the encoders and write to the pointer passed in */
    return `$INSTANCE_NAME`_encoder_ReadCounter();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_resetEncoderCount()
********************************************************************************
* Summary:
*   Places the encoder counts into the specified struct
*
* \return
*   Value of new encoder (0)
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_resetEncoderCount(void) {
    /* Reset hardware counter */
    `$INSTANCE_NAME`_encoder_WriteCounter(ZERO);
    /* Reset the local count */
    return ZERO;
}

/* [] END OF FILE */
