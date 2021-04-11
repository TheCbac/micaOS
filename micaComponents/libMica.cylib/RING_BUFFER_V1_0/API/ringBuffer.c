/***************************************************************************
*                                 MICA  © 2018
*                           MIT BioInstrumentation Lab
*
* File: ringBuffer.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* Prb:  
* PSoC: 
*
* Brief:
*   Generic implementation for a ring buffer
*
* 2018.10.08  - Document Created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_init()
****************************************************************************//**
* \brief
*  Allocates memory for an ring buffer
*
* \param rb [in]
*  Pointer to the handle for the ring buffer
*
* \param capacity [in]
*   Number of elements the buffer should be able to hold
*
* \param sz [in]
*   Size of each element
*
* \return
*  An error of the initialization operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_init(`$INSTANCE_NAME`_S *rb, size_t capacity, size_t sz){
    /* Allocate from the heap */
    rb->buffer = malloc(capacity * sz);    
    if(rb->buffer == NULL) {
        return `$INSTANCE_NAME`_ERR_MEMORY;    
    }
    rb->buffer_end = (uint8_t *)rb->buffer + capacity * sz;
    rb->capacity = capacity;
    rb->count = ZERO;
    rb->elemSize = sz;
    rb->head = rb->buffer;
    rb->tail = rb->buffer;
    return `$INSTANCE_NAME`_ERR_SUCCESS;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_free()
****************************************************************************//**
* \brief
*  frees memory allocated for an ring buffer
*
* \param rb [in]
*  Pointer to the ring buffer
*
* \return
*  An error of the free operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_free(`$INSTANCE_NAME`_S *rb){
    /* Deallocate heap memory */
    if(rb->buffer != NULL){
        free(rb->buffer);
    } else {
        return `$INSTANCE_NAME`_ERR_MEMORY;      
    }
    /* Clear the fields */
    rb->buffer_end = NULL;
    rb->capacity = ZERO;
    rb->count = ZERO;
    rb->elemSize = ZERO;
    rb->head = NULL;
    rb->tail = NULL;
    return `$INSTANCE_NAME`_ERR_SUCCESS;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_push()
****************************************************************************//**
* \brief
*  Pushes an element to the end of the queue
*
* \param rb [in]
*  Pointer to the ring buffer
*
* \param item [in]
*  Pointer to item to push
*
* \return
*  An error of the push operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_push(`$INSTANCE_NAME`_S *rb, const void *item){
    /* ensure buffer has been allocated */
    if(rb->buffer == NULL || rb->head == NULL || rb->tail == NULL){
        return `$INSTANCE_NAME`_ERR_MEMORY;    
    }
    /* Ensure there is enough space in the buffer */
    if(rb->count == rb->capacity){
        return `$INSTANCE_NAME`_ERR_SPACE;    
    }
    /* Copy the element */
    memcpy(rb->head, item, rb->elemSize);
    /* Udpate head location */
    rb->head += rb->elemSize;
    /* Handle buffer wrap around */
    if(rb->head == rb->buffer_end){
        rb->head = rb->buffer;    
    }
    /* Increase current location */
    rb->count++;
    return `$INSTANCE_NAME`_ERR_SUCCESS;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_pop()
****************************************************************************//**
* \brief
*  Pops an element from the beginging of the queue
*
* \param rb [in]
*  Pointer to buffer
*
* \param item [out]
*  Pointer to where to place the item
*
* \return
*  An error of the pop operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_pop(`$INSTANCE_NAME`_S *rb, void *item){
    /* ensure buffer has been allocated */
    if(rb->buffer == NULL || rb->head == NULL || rb->tail == NULL){
        return `$INSTANCE_NAME`_ERR_MEMORY;    
    }
    if(rb->count == ZERO){
        return `$INSTANCE_NAME`_ERR_EMPTY;
    }
    /* Copy the element out */
    memcpy(item, rb->tail, rb->elemSize);
    rb->tail += rb->elemSize;
    /* Handle wrap around */
    if(rb->tail == rb->buffer_end){
        rb->tail = rb->buffer;
    }
    /* Decrease count */
    rb->count--;
    return `$INSTANCE_NAME`_ERR_SUCCESS;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_clear()
****************************************************************************//**
* \brief
*  Resets the array
*
* \param rb [in]
*  Pointer to buffer
*
* \return
*  An error of the clear operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_clear(`$INSTANCE_NAME`_S *rb){
    rb->count = ZERO;    
    rb->head = rb->buffer;
    rb->tail = rb->buffer;
    return `$INSTANCE_NAME`_ERR_SUCCESS;
}
    

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_pushArray()
****************************************************************************//**
* \brief
*  Pushes an element to the end of the queue
*
* \param rb [in]
*  Pointer to the ring buffer
*
* \param arr [in]
*  Pointer to array to push from
*
* \param len [in]
*   Length of the array
*
* \return
*  An error of the push operation
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_pushArray(`$INSTANCE_NAME`_S *rb, uint8_t *arr, size_t len){
    /* ensure buffer has been allocated */
    if(rb->buffer == NULL || rb->head == NULL || rb->tail == NULL){
        return `$INSTANCE_NAME`_ERR_MEMORY;    
    }
    /* Ensure there is enough space in the buffer */
    size_t avail = rb->capacity - rb->count;
    uint32_t err = `$INSTANCE_NAME`_ERR_SUCCESS;
    if(len > avail){
        return `$INSTANCE_NAME`_ERR_SPACE;    
    } else {
        /* Queue each element */
        uint8_t i;
        for(i=ZERO; i < len; i++){
            err |= `$INSTANCE_NAME`_push(rb, &arr[i]);
            if(err){
                break;
            }
        }
    }
    return err;
}
/* [] END OF FILE */
