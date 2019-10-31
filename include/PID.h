/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: PID.h
* Workspace: gameBoard
* Project: orbiter_v1
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: mcuPsoc4 5.2.1
* PSoC: CY8C4245LQI-483
*
* Brief:
*   Header for PID.c
*
* 2019.04.16  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef PID_H
    #define PID_H
    /***************************************
    * Included files
    ***************************************/
   
    /***************************************
    * Macro Definitions
    ***************************************/
    
    /***************************************
    * Enumerated Types
    ***************************************/
    typedef float FUNCTION_GET_FLOAT_T(void);       /**< Float/void function type for sampling new data points */
    typedef void FUNCTION_SET_FLOAT_T(float out);   /**< void/float function type for command new control effort */
    /***************************************
    * Structures
    ***************************************/
    typedef struct {
        float Kp;               /**< [Input] Proportional gain */
        float Ki;               /**< [Input] Integral gain */
        float Kd;               /**< [Input] Derivative gain */
        
        float period;           /**< [Input] Update time in seconds */
        float beta;             /**< [Input] Refrerence Weight [0-1] (see 10.16) */
        
        float Tt;               /**< [Input] Filter time constant for the integral filter - see (10.19) */
        float Tf;               /**< [Input] Filter time constant for the Derivative filter See (10.13) */
        
        float setpoint;         /**< [Input] Reference input */
        float processVal;       /**< [Input] Current value of the system */
        float effort;           /**< [Output] Control effort to be written out */
        
        float uMax;             /**< [Input] Maximum control effort */
        float uMin;             /**< [Input] Minimum control effort */
        
        float Ai;               /**< [Internal] Precomputed integral factor of Ki * h (see 10.19) */
        float Bi;               /**< [Internal] Precomputed integral factor of h/Tt (see 10.19) */
        float Ad;               /**< [Internal] Precomputed derivative factor of Tf/(Tf+h) (see 10.20) */
        float Bd;               /**< [Internal] Precomputed derivative factor of Kd/(Tf + h) (see 10.20) */
        float I;                /**< [Internal] Integral Term */
        float D;                /**< [Internal] Derivate term */
        float yPrev;            /**< [Internal] The last output */

//        FUNCTION_GET_FLOAT_T *getReferenceVal;      /**< [Input] Function to call when updating the reference variable */
//        FUNCTION_GET_FLOAT_T *getProcessVal;        /**< [Input] Function to call when updating the process variable */
//        FUNCTION_SET_FLOAT_T *setControlEffort;     /**< [Input] Function to call when commanding out new effor */
    } pidState_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    void PID_precomputeFactors(pidState_S *state);
    void PID_updateState(pidState_S *state);  

#endif /* PID_H */
/* [] END OF FILE */
