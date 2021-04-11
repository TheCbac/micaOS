/***************************************************************************
*                                       MICA
* File: Sflash.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   API for interacting with the Supervisory flash
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.03 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"



/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadRow()
****************************************************************************//**
*
* \brief Places the SFlash data of the specified row into the array passed in. 
    Array must be of length `$INSTANCE_NAME`_SIZE_ROW.
*
* \param rowNum
*   The row number of the SFlash to read from 
*   
* \param dataBuffer
*   Buffer to place data into. Must be of size `$INSTANCE_NAME`_SIZE_ROW 
*
* \return
* uint32: An error code with the result of the Read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | Read was successful
*   `$INSTANCE_NAME`_ERR_INDEX_RANGE        | Invalid row number was passed in
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadRow(uint8 rowNum, uint8* dataBuffer){
    /* Ensure a valid row number */
    if(rowNum > (`$INSTANCE_NAME`_NUM_ROWS - INDEX_ZERO_CORRECT) ) {
        return `$INSTANCE_NAME`_ERR_INDEX_RANGE;
    }
    uint16 idx = ZERO;
    /* iterate through all of the row */
    for(idx = ZERO; idx < `$INSTANCE_NAME`_SIZE_ROW ; idx++){
        /* Calculate the address of the data cell */
        uint32 addr = `$INSTANCE_NAME`_BASE_ADDR + (rowNum * `$INSTANCE_NAME`_SIZE_ROW) + idx;
        /* Copy the data from SFlash into the buffer */
        dataBuffer[idx] = *(uint8 *) addr;
    }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteRow()
****************************************************************************//**
*
* \brief Copies the data in 'rowData' and writes it into the Supervisory Flash 
*   (SFlash) section of code. Wrapper of the Cypress function CySysSFlashWriteUserRow().
*
* \param rowNum
*   The row number of the SFlash to write to. 
*   
* \param rowData
*   Buffer copy data from
*
*\return 
* uint32: An error code with the result of the Write procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   ERR_NO_ERROR                            | Write was successful
*   <Cypress generated Error>                 | See CySysSFlashWriteUserRow()
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_WriteRow(uint8 rowNum, const uint8* rowData){
    /* Write the data and return the result */
    return CySysSFlashWriteUserRow(rowNum, rowData);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadLocalName()
****************************************************************************//**
*
* \brief Copies the name stored in SFLASH into the array passed in. 
*
* \param nameArray
*   Array the name will be passed into. Must be of length `$INSTANCE_NAME`_NAME_LEN
*   or longer.
*   
*
*\return 
* uint32: An error code with the result of the Read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | Read was successful
*******************************************************************************/
uint32 `$INSTANCE_NAME`_ReadLocalName(char* nameArray){
    uint8 i;
    /* Start of the name location in SFlash */
    uint32 nameBaseAddr = `$INSTANCE_NAME`_BASE_ADDR + (`$INSTANCE_NAME`_NAME_ROW * `$INSTANCE_NAME`_SIZE_ROW) + `$INSTANCE_NAME`_NAME_OFFSET;
    /* Move the longest possible name into the array */
    for(i = ZERO; i < `$INSTANCE_NAME`_NAME_LEN; i++) {
        /* Copy to the array passed in */
        uint32 addr = nameBaseAddr + i;
        /* Copy the character */
        nameArray[i] = *(char *) addr;
    }
    /* Return success */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteLocalName()
****************************************************************************//**
*
* \brief Stores the name passed in into SFLASH.
*
* \param len 
*   Length of the name. Must be less than or equal to `$INSTANCE_NAME`_NAME_LEN
*
* \param nameArray
*   Array which contains the Name - does not need to be null-terminated.
*
*\return 
* uint32: An error code with the result of the Read procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | Writing the name was successful
*   `$INSTANCE_NAME`_ERR_INDEX_RANGE        | Name was too long to write
*******************************************************************************/
uint32 `$INSTANCE_NAME`_WriteLocalName(uint8 len, char* nameArray){
    /* Ensure data is proper length */
    if(len > `$INSTANCE_NAME`_NAME_LEN) {
        return `$INSTANCE_NAME`_ERR_INDEX_RANGE;
    }
    /* Read the current row into rowData[] */
    uint8 rowData[`$INSTANCE_NAME`_SIZE_ROW];
    `$INSTANCE_NAME`_ReadRow(`$INSTANCE_NAME`_NAME_ROW, rowData);
    /* Iterate through the new array */
    uint8 i;
    for(i = ZERO; i < len; i++) {
        /* Position of data  */   
        uint8 addr = `$INSTANCE_NAME`_NAME_OFFSET + i;
        /* Copy new character */
        rowData[addr] = nameArray[i];
    }
    /* Append a null octect unless there is no space for one */
    if( len != `$INSTANCE_NAME`_NAME_LEN) {
        /* Append a null octet to end of string */
        rowData[`$INSTANCE_NAME`_NAME_OFFSET + len] = NULL_OCTET;
    }

    /* Write the new Row to SFlash */
    return `$INSTANCE_NAME`_WriteRow(`$INSTANCE_NAME`_NAME_ROW, rowData);
}
  
/* [] END OF FILE */
