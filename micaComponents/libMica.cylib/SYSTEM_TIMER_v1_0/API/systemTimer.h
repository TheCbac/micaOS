/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`.h
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
*
* Brief:
*   Header for systemtTimer.c
*
* 2019.01.10  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include <stdbool.h>
    #include "micaCommon.h"
    #include "`$INSTANCE_NAME`_timer.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_CLK_PERIOD_US              (10)        /**< Period of one clock in microseconds */
    #define `$INSTANCE_NAME`_TIMER_PERIOD_US            (500000)    /**< Period of one timer count in microseconds */
    
    #define `$INSTANCE_NAME`_MSEC_PER_SEC               (1000)      /**< Number of milliseconds per second */    
    #define `$INSTANCE_NAME`_USEC_PER_SEC               (1000000)   /**< Number of microseconds per second */    
    #define `$INSTANCE_NAME`_TASKS_MAX                  (32)        /**< Maximum number of tasks that can be stored in the schedule queue */
    /***************************************
    * Enumerated Types
    ***************************************/

    
    /***************************************
    * Structures
    ***************************************/
    typedef struct {
        uint32_t seconds;            /**< Number of seconds the timer has been running */
        uint32_t microSecs;         /**< number of microseconds elapsed */
        uint64_t count;             /**< running count of the time in microseconds */
    }  `$INSTANCE_NAME`_time_S;
    
    typedef struct {
        uint64_t exiprationTime;    /**< System time when the task should be executed */
        FUNCTION_VOID_T* callback;   /**< Function to execute when task has expired */
    } `$INSTANCE_NAME`_task_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    void `$INSTANCE_NAME`_ResetTime(void);
    void `$INSTANCE_NAME`_Start(void);
    void `$INSTANCE_NAME`_Stop(void);
    void `$INSTANCE_NAME`_getSystemTime(`$INSTANCE_NAME`_time_S *time);
    uint64_t `$INSTANCE_NAME`_getSystemCount(void);
    uint8_t `$INSTANCE_NAME`_scheduleTaskMs(FUNCTION_VOID_T * callback, uint32_t msDelay);
    uint8_t `$INSTANCE_NAME`_startTask(FUNCTION_VOID_T * task);
    uint8_t `$INSTANCE_NAME`_unscheduleTask(uint8_t taskId); 
    uint8_t `$INSTANCE_NAME`_processSystemTasks(void);
    uint8_t `$INSTANCE_NAME`_getNumTasks(void);
    float `$INSTANCE_NAME`_getSystemTimeF(void);

    

#endif /* `$INSTANCE_NAME`_H */

/* [] END OF FILE */
