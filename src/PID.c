/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: PID.c
* Workspace: gameBoard
* Project: orbiter_v1
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: mcuPsoc4 5.2.1
* PSoC: CY8C4245LQI-483
*
* Brief:
*   Discrete PID controller. See http://www.cds.caltech.edu/~murray/books/AM08/pdf/am06-pid_16Sep06.pdf
*
* 2019.04.16  - Document Created
********************************************************************************/
#include "PID.h"

/*******************************************************************************
* Function Name: PID_precomputeFactors()
****************************************************************************//**
* \brief
*  Precomputes factors to save time during the update loop. Only needs to be
*   run once unless parameters change.
*   The following values must be present: Ki, Kd, period, Tt, Tf
*
* \param state [in/out]
*  Pointer to the Controller state structure
*
* \return
*  None
*******************************************************************************/
void PID_precomputeFactors(pidState_S *state){
    /* integral terms */   
    state->Ai = state->Ki * state->period;
    state->Bi = state->period / state->Tt;
    /* Derivative terms */
    float denom = state->Tf + state->period;
    state->Ad = state->Tf / denom;
    state->Bd = state->Kd / denom;
}

    
/*******************************************************************************
* Function Name: PID_updateState()
****************************************************************************//**
* \brief
*  Updates the PID control structure
*
* \param state [in/out]
*  Pointer to the Controller state structure
*
* \return
*  None
*******************************************************************************/
void PID_updateState(pidState_S *state) {
    float y = state->processVal;
    /* Compute the proportional term (see 10.18) */
    float P = state->Kp * ((state->beta * state->setpoint) - y);
    /* Compute and store the derivative term (see 10.20) */
    state->D = state->Ad*state->D - state->Bd*(y - state->yPrev);
    /* Compute intermediate output */
    float v = P + state->I + state->D;
    /* Anti-windup */
    float u = v < state->uMin ? state->uMin : v;
    u = u > state->uMax ? state->uMax : u;
    /* Write out the control effort */
    state->effort = u;
    /* Update the integral term (see 10.19) */
    state->I = state->I + state->Ai*(state->setpoint-y) + state->Ai*(u-v);
    /* Store the previous process variable */
    state->yPrev = y;
}


/* [] END OF FILE */
