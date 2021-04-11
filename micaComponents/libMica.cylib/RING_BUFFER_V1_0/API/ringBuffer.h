/***************************************************************************
*                                 MICA  © 2018
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
*   Header for ringBuffer.c
*
* 2018.10.08  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef `$INSTANCE_NAME`_H
    #define `$INSTANCE_NAME`_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include <stdlib.h>
    /***************************************
    * Macro Definitions
    ***************************************/
    #define `$INSTANCE_NAME`_VERSION            (0x0100) /**< Internal Version (v1.0) */
    /* Error codes */
    #define  `$INSTANCE_NAME`_ERR_SUCCESS       (0x00)  /**< The error code indicating success */
    #define  `$INSTANCE_NAME`_ERR_MEMORY        (1u << `$INSTANCE_NAME`_SHIFT_MEMORY )  /**< The error code memory allocation failed */
    #define  `$INSTANCE_NAME`_ERR_SPACE         (1u << `$INSTANCE_NAME`_SHIFT_SPACE )  /**< There is no room in the buffer */
    #define  `$INSTANCE_NAME`_ERR_EMPTY         (1u << `$INSTANCE_NAME`_SHIFT_EMPTY )  /**< The allocated buffer does not have any elements in it */
    
    
    /* Error shifts */
    #define `$INSTANCE_NAME`_SHIFT_MEMORY       (0u)        /**< Shift of the memory allocation failed flag */
    #define `$INSTANCE_NAME`_SHIFT_SPACE        (1u)        /**< Shift of the space allocation failed flag */
    #define `$INSTANCE_NAME`_SHIFT_EMPTY        (2u)        /**< Shift of the space empty buffer flag */
    
    
    /***************************************
    * Enumerated Types
    ***************************************/
    
    /***************************************
    * Structures
    ***************************************/
    typedef struct {
        void *buffer;           /**< Data buffer */
        void *buffer_end;       /**< end of the data buffer */
        size_t capacity;       /**< Maximum number of items in the bvuffer */
        size_t count;          /**< Number of items currently in the buffer */
        size_t elemSize;             /**< size of each item in the buffer */
        void *head;             /**< Pointer to the head */
        void *tail;             /**< Pointer to the tail */
    }  `$INSTANCE_NAME`_S;
    
    /***************************************
    * Function declarations 
    ***************************************/
    uint32_t `$INSTANCE_NAME`_init(`$INSTANCE_NAME`_S *rb, size_t capacity, size_t sz);    
    uint32_t `$INSTANCE_NAME`_free(`$INSTANCE_NAME`_S *rb);
    uint32_t `$INSTANCE_NAME`_push(`$INSTANCE_NAME`_S *rb, const void *item);    
    uint32_t `$INSTANCE_NAME`_pop(`$INSTANCE_NAME`_S *rb, void *item);
    uint32_t `$INSTANCE_NAME`_clear(`$INSTANCE_NAME`_S *rb);
    
    
    uint32_t `$INSTANCE_NAME`_pushArray(`$INSTANCE_NAME`_S *rb, uint8_t *item, size_t len);
    
    
#endif /* `$INSTANCE_NAME`_H */
/* [] END OF FILE */
