/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: PID.c
* Project: micaOS
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: Generic
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
    #include <stdint.h>
    /***************************************
    * Macro Definitions
    ***************************************/
    #define PID_ERROR_SHIFT_NAN     (0)   /* Not a number */
    #define PID_ERROR_SHIFT_WIND    (1)   /* Anti-windup was triggered*/
    
    
    #define PID_ERROR_NONE          (0)   /* No error (success) */
    #define PID_ERROR_NAN           (1u << PID_ERROR_SHIFT_NAN) /* NaN in control effort */
    #define PID_ERROR_WIND           (1u << PID_ERROR_SHIFT_WIND) /* Anti-windup was triggered*/
    
    
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

        uint32_t errorFlags;  /* Error flags of the system. NOT the controller error, rather an indicator something went wrong */
    } pidState_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    void PID_precomputeFactors(pidState_S *state);
    void PID_updateState(pidState_S *state);  

#endif /* PID_H */
/* [] END OF FILE */
