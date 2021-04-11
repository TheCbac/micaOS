/***************************************************************************
*                                       MICA
* File: OTA_Updates.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for executing Over the Air Updates (OTA)
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.01 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$BOOTLOADABLE_NAME`.h"
/* OTA_TYPE == STACK_PROJECT */
#if (`$OTA_TYPE` == `$INSTANCE_NAME`__STACK_PROJECT)
    #include "`$BOOTLOADER_NAME`.h"
#endif
#include "micaCommon.h"

/* Ensure memory is of proper size */
#if CYDEV_FLASH_SIZE != 0x00040000u
 #error "This design is specifically targeted to parts with 256k of flash."
#endif


/* OTA_TYPE */
#if (`$OTA_TYPE` == `$INSTANCE_NAME`__APP_PROJECT)
    /* Private Functions prototypes */
    static cystatus `$INSTANCE_NAME`_writeFlashByte(const uint32 address, const uint8 inputValue);

    /*******************************************************************************
    * Following code implements re-initialization of separate RAM segment containing
    * data that is required for BLE Stack operation.
    * This code is used in case of GCC compiler
    *******************************************************************************/
    extern void Bootloader___libc_init_array(void);
    typedef unsigned char __cy_byte_align8 __attribute ((aligned (8)));
    struct __cy_region
    {
        __cy_byte_align8 *init; /* Initial contents of this region.  */
        __cy_byte_align8 *data; /* Start address of region.  */
        size_t init_size;       /* Size of initial data.  */
        size_t zero_size;       /* Additional size to be zeroed.  */
    };
    extern const struct __cy_region Bootloader___cy_regions[];
    extern const char Bootloader___cy_region_num __attribute__((weak));
    #define Bootloader___cy_region_num ((size_t)&Bootloader___cy_region_num)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_InitializeCodeSharing()
    ********************************************************************************
    *
    * Summary:
    *   This function triggers initialization of bootloader RAM .bss section.
    *   It is required for BLE Stack operation. This function should be called from
    *   main() prior BLE component start.
    *
    *
    * Parameters:
    *   None
    *
    * Return:
    *   None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_InitializeCodeSharing(void){
        unsigned regions = Bootloader___cy_region_num;
        const struct __cy_region *rptr = Bootloader___cy_regions;
        /* Initialize memory */
        for( regions = Bootloader___cy_region_num; regions != ZERO; regions--){
            uint32 *src = (uint32 *)rptr->init;
            uint32 *dst = (uint32 *)rptr->data;
            unsigned limit = rptr->init_size;
            unsigned count;
            /* Copy the contents src address to the dst addresses */
            for(count = ZERO; count != limit; count += sizeof (uint32)){
                *dst = *src;
                dst++;
                src++;
            }
            /* Zero the folowing sections */
            limit = rptr->zero_size;
            for(count = ZERO; count != limit; count += sizeof (uint32)){
                *dst = ZERO;   
                dst++;
            }
            rptr++;
        }
        `$INSTANCE_NAME`_DBG_PRINT("> Code sharing initialized\r\n");
    }





    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_writeFlashByte()
    ********************************************************************************
    *
    * Summary:
    *   This API writes to flash the specified data. This over
    *
    *
    * Parameters:
    *    address    - The address in flash.
    *    inputValue - One-byte data.
    *
    * Return:
    *   A status of the writing to flash procedure.
    *
    *******************************************************************************/
    cystatus `$INSTANCE_NAME`_writeFlashByte(const uint32 address, const uint8 inputValue){
        /* intialize private variables */
        cystatus result = CYRET_SUCCESS;
        uint8 rowData[CYDEV_FLS_ROW_SIZE];
        /* Calculate the flash address */
        uint32 flsAddr = address - CYDEV_FLASH_BASE;
        /* Calculate the row number */
        uint16 rowNum = (uint16) (flsAddr / CYDEV_FLS_ROW_SIZE);
        /* Calculate the base address */
        uint32 baseAddr = address - (address % CYDEV_FLS_ROW_SIZE);
        uint16 idx;
        /* Get the row data */
        for(idx = ZERO; idx < CYDEV_FLS_ROW_SIZE; idx++){
            rowData[idx] = (uint8)`$BOOTLOADABLE_NAME`_GET_CODE_DATA(baseAddr + idx);   
        }
        /* Set the new value */
        rowData[address % CYDEV_FLS_ROW_SIZE] = inputValue;
        /* Write the data */
        result = CySysFlashWriteRow((uint32) rowNum, rowData);
        /* Return the result */
        return result;
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_AfterAppImageUpdate()
    ********************************************************************************
    *
    * Summary:
    *   This functions checks if the Application Self Project Image has been Updated and is 
    *   Running for the first time. If so, it clears the new image flag. If bonded 
    *   devices are used, then the bonded data must be cleared.
    *
    * Parameters:
    *   None
    *
    * Return:
    *   None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_AfterAppImageUpdate(void){
        /* See if the image was updated */
        if( `$INSTANCE_NAME`_GET_FLAG_UPDATE_APP == `$INSTANCE_NAME`_FLAG_SET){
            `$INSTANCE_NAME`_DBG_PRINT("> *** App Image was updated ***\r\n");
            //TODO: deal with bonded devices
            /* Clear the flag */
            `$BOOTLOADABLE_NAME`_SetFlashByte(`$INSTANCE_NAME`_FLAG_UPDATE_APP, `$INSTANCE_NAME`_FLAG_CLEAR);
        }
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_EnterBootloadMode()
    ********************************************************************************
    *
    * Summary:
    *   Sets the active application to the stack bootloader, and then resets
    *   the device. The active application is written in the Flash metadata section.
    *   This function will not return. 
    *
    *   NOTE The active application number is not set directly, but the boolean 
    *   mark instead means that the application is active or not for the relative 
    *   metadata. Both metadata sections are updated. For example, if the second 
    *   application is to be set active, then in the metadata section for the first 
    *   application there will be a "0" written, which means that it is not active, and 
    *   for the second metadata section there will be a "1" written, which means that it is 
    *   active. TODO: more efficient and direct implementation that doesn't waste a Flash 
    *   Write cycle on the entire device
    *
    * Parameters:
    *   None
    *
    * Return:
    *   None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_EnterBootloadMode(void){
        `$INSTANCE_NAME`_DBG_PRINT("> Entering Bootload mode...\r\n");
        uint8 idx;
        /* Set the active application by updating the metadata section */
        for( idx = ZERO; idx < `$BOOTLOADABLE_NAME`_MAX_NUM_OF_BTLDB; idx++){
            `$INSTANCE_NAME`_writeFlashByte((uint32) `$INSTANCE_NAME`_MD_BTLDB_ACTIVE_OFFSET(idx), (uint8)(idx == `$INSTANCE_NAME`_ID_PROGRAM_STACK) );
        }
        /* Reset the device in bootload mode */
        `$BOOTLOADABLE_NAME`_Load();
}
#endif /* OTA_TYPE APP_PROJECT */

/* OTA_TYPE */
#if (`$OTA_TYPE` == `$INSTANCE_NAME`__STACK_PROJECT)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_BootUserApp()
    ********************************************************************************
    *
    * Summary:
    *   This function checks if to see if there is a valid user applciation. If
    *   there is, instruct the launcher to boot the app next time the device boots,
    *   and immediately reset the device.
    *
    * Parameters:
    *   None
    *
    * Return:
    *   None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_BootUserApp(void){
         /* Check if the application image is present, valid, and has not been run before */
        if( (CYRET_SUCCESS == `$BOOTLOADER_NAME`_ValidateBootloadable(`$INSTANCE_NAME`_ID_PROGRAM_APP)) && (`$INSTANCE_NAME`_GET_FLAG_UPDATE_APP == `$INSTANCE_NAME`_FLAG_SET) ){
            `$INSTANCE_NAME`_DBG_PRINT("\r\n> Application is ready to launch\r\n");
            `$INSTANCE_NAME`_DBG_PRINT("> Booting app...\r\n");
            /* Set the app to boot */
            `$BOOTLOADABLE_NAME`_SetActiveApplication(`$INSTANCE_NAME`_ID_PROGRAM_APP);
            /* Reset the device */
            CySoftwareReset();
        }   
    }

    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_AfterStackImageUpdate()
    ********************************************************************************
    *
    * Summary:
    *   This function checks if the Stack Self Project Image has been Updated and is running
    *   for the first time. If so, and if Bonding data is used then it verifies
    *   bonding data and erases bonding data if it is not valid. 
    *
    * Parameters:
    *   None
    *
    * Return:
    *   None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_AfterStackImageUpdate(void){
        /* Check to see if the stack project was updated */
        if( `$INSTANCE_NAME`_GET_FLAG_UPDATE_STACK == `$INSTANCE_NAME`_FLAG_SET ){
            `$INSTANCE_NAME`_DBG_PRINT("> *** Stack Project was updated ***\r\n");
            /* Delete the bonded data */
            #if `$INSTANCE_NAME`_BONDING_ENABLED
                /* Clear the bonded device list */
                // TODO: Clear_ROM_Array
            #endif /* BONDING_ENABLED */
            /* Set byte in metadata row indicating that the Stack Project was started */
            `$BOOTLOADER_NAME`_SetFlashByte(`$INSTANCE_NAME`_FLAG_UPDATE_STACK, `$INSTANCE_NAME`_FLAG_CLEAR);
        }
    }
#endif /* OTA_TYPE */

/* [] END OF FILE */
