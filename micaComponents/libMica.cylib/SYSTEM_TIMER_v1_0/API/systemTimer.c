/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: systemtTimer.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Manages timing for system events
*
* 2019.01.10  - Document Created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$INSTANCE_NAME`_timer_interrupt.h"
#include <stdlib.h>

`$INSTANCE_NAME`_task_S scheduleQueue[`$INSTANCE_NAME`_TASKS_MAX];
uint8_t numTasks = ZERO;

volatile `$INSTANCE_NAME`_time_S systemTime;
volatile bool flag_systemTime_halfSec = false;

/*  Function declarations */
int `$INSTANCE_NAME`_compareTaskTime(const void *task1, const void *task2);
void `$INSTANCE_NAME`_ISR_incTime(void);


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_compareTaskTime()
****************************************************************************//**
* \brief
*  Compares two tasks together to see which one is due to expire first
*  
* \param tasks1 [in]
*   Pointer to task 1
*
* \param task2 [in]
*   Pointer to task 2
*
* \return
*   <0 task1 before task2
*   0 same time
*   >0 task2 before task1
*******************************************************************************/
int `$INSTANCE_NAME`_compareTaskTime(const void *task1, const void *task2) {
    /* Cast to tasks type */
    uint64_t exp1 = ((`$INSTANCE_NAME`_task_S *) task1)->exiprationTime;
    uint64_t exp2 = ((`$INSTANCE_NAME`_task_S *) task2)->exiprationTime;
    return exp1 - exp2;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start()
****************************************************************************//**
* \brief
*  Starts the system timer
*
* \return
*   Error code of the start procedure
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void){
    `$INSTANCE_NAME`_ResetTime();
    `$INSTANCE_NAME`_timer_interrupt_StartEx(`$INSTANCE_NAME`_ISR_incTime);
    `$INSTANCE_NAME`_timer_Start();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop()
****************************************************************************//**
* \brief
*  Stop the timer
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void){
    `$INSTANCE_NAME`_timer_Stop();
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ResetTime()
****************************************************************************//**
* \brief
*  Starts the system timer
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_ResetTime(void){
    systemTime.seconds = ZERO;
    systemTime.microSecs = ZERO;
    systemTime.count = ZERO;
    flag_systemTime_halfSec = false;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getSystemTime()
****************************************************************************//**
* \brief
*  Places the current system time into time structure passed in
*
* \param time [out]
*   Pointer to struct that the results are placed into
*
* \return
*   None
*******************************************************************************/
void `$INSTANCE_NAME`_getSystemTime(`$INSTANCE_NAME`_time_S *time){
    uint8_t intStatus = CyEnterCriticalSection();
    
    time->seconds = systemTime.seconds;
    uint32_t microSecs = `$INSTANCE_NAME`_timer_ReadCounter() * `$INSTANCE_NAME`_CLK_PERIOD_US;
    if ( flag_systemTime_halfSec) {
        microSecs += `$INSTANCE_NAME`_TIMER_PERIOD_US;
    }
    time->microSecs = microSecs;
    time->count = (systemTime.seconds *`$INSTANCE_NAME`_USEC_PER_SEC) + microSecs;
    
    CyExitCriticalSection(intStatus);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getSystemCount()
****************************************************************************//**
* \brief
*  Returns the current system count
*
* \return
*   Time count
*******************************************************************************/
uint64_t `$INSTANCE_NAME`_getSystemCount(void) {
    `$INSTANCE_NAME`_time_S time;
    `$INSTANCE_NAME`_getSystemTime(&time);
    return time.count;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getSystemTimeF()
****************************************************************************//**
* \brief
*  Returns a float containing the current system time in seconds
*
* \return
*   Time count
*******************************************************************************/
float `$INSTANCE_NAME`_getSystemTimeF(void){
    float timeF;
    uint8_t intStatus = CyEnterCriticalSection();
    
    timeF = (float) systemTime.seconds;
    uint32_t microSecs = `$INSTANCE_NAME`_timer_ReadCounter() * `$INSTANCE_NAME`_CLK_PERIOD_US;
    if ( flag_systemTime_halfSec) {
        microSecs += `$INSTANCE_NAME`_TIMER_PERIOD_US;
    }
    timeF += (microSecs * 0.000001);
    
    
    CyExitCriticalSection(intStatus);
    return timeF;
}


/*******************************************************************************
* ISR Name: `$INSTANCE_NAME`_ISR_incTime()
********************************************************************************
* Summary:
*  Triggers from the system timer component. Increments the stored time count
*
* Interrupt: 
*       timer_interupt
*
*******************************************************************************/
void `$INSTANCE_NAME`_ISR_incTime(void){
    if(flag_systemTime_halfSec) {
        flag_systemTime_halfSec = false;
        systemTime.seconds++;
    } else {
        flag_systemTime_halfSec = true;    
    }
    /* Clear the interrupt  */
    `$INSTANCE_NAME`_timer_ClearInterrupt(`$INSTANCE_NAME`_timer_INTR_MASK_TC);

}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_scheduleTaskMs()
****************************************************************************//**
* \brief
*  Place an item in the schedule Queue, and delay it for a given number of millis
*
* \param callback [in]
*   function to call when time elapses
*
* \param msDelay
*   Number of milliseconds to delay before execution
*
* \return
*   ID of the tasks
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_scheduleTaskMs(FUNCTION_VOID_T * callback, uint32_t msDelay){
    if(numTasks < `$INSTANCE_NAME`_TASKS_MAX) {
        /* Calculate current system time */
        `$INSTANCE_NAME`_time_S currentTime;
        `$INSTANCE_NAME`_getSystemTime(&currentTime);
        /* insert the tasks into the schedule queue */
        uint8_t taskId = numTasks++;
        scheduleQueue[taskId].callback = callback;
        scheduleQueue[taskId].exiprationTime = currentTime.count + ( msDelay *`$INSTANCE_NAME`_MSEC_PER_SEC);
        /* Sort the queue */
        qsort(scheduleQueue, numTasks, sizeof(`$INSTANCE_NAME`_task_S), `$INSTANCE_NAME`_compareTaskTime); 
        /* Return task ID */
        return taskId;
    }
    return ZERO;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_startTask()
****************************************************************************//**
* \brief
*  Queues a task to immediately begin
*
* \param callback [in]
*   function pointer to tasks. Must be of signature void/void
*
* \return
*   ID of the tasks
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_startTask(FUNCTION_VOID_T * task){
    return `$INSTANCE_NAME`_scheduleTaskMs(task, ZERO);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_processSystemTasks()
****************************************************************************//**
* \brief
*  Checks to see if the next item in the queue has expired
*
* \return
*   Number of tasks in the queue
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_processSystemTasks(void){
    /* Calculate current system time */
    `$INSTANCE_NAME`_time_S currentTime;
    `$INSTANCE_NAME`_getSystemTime(&currentTime);
    /* See if the task in the queue that has expired */
    `$INSTANCE_NAME`_task_S nextTask = scheduleQueue[ZERO];
    if(numTasks && currentTime.count >= nextTask.exiprationTime){
        /* Shift the schedule queue down */
        uint8_t i;
        numTasks--;
        for(i = ZERO; i<numTasks; i++){
            scheduleQueue[i] = scheduleQueue[i+ONE]; 
        }   
        /* Run the tasks */
        nextTask.callback();
    }
    
    return numTasks;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_unscheduleTask()
****************************************************************************//**
* \brief
*  Removes an item from the schedule Queue 
*
* \param taskId [in]
*   Id of the tasks to be removed
*
* \return
*   Number of tasks in the queue
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_unscheduleTask(uint8_t taskId){
//    /* Ensure the task exists */
//    if(taskId < numTasks) {
//        /* Shift tasks down */
//        uint8_t i;
//        for(i = --numTasks; i>taskId; i--){
//            scheduleQueue[i-ONE] = scheduleQueue[i]; 
//        } 
//    }
    return numTasks;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_getNumTasks()
****************************************************************************//**
* \brief
*  Returns the number of tasks currently in the queue
*
* \return
*   Number of tasks in the queue
*******************************************************************************/
uint8_t `$INSTANCE_NAME`_getNumTasks(void) {
    return numTasks;
}


/* [] END OF FILE */
