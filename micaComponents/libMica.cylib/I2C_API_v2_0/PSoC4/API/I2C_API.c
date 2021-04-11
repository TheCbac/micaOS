/***************************************************************************
*                                       MICA
* File: I2C_API.c
* Workspace: micaComponents
* Project Name: libMica
* Version: v2.0
* Author: Craig Cheney
*
* Brief:
*   Extension for the MICA I2C API
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.05.03 CC - Transitioned to I2C component v4 (timeout)
*   2018.03.14 CC - Document created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"

/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_Write()
****************************************************************************//**
* \brief
*  Writes a byte to data to a given register of the target I2C slave 
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param regAddr
*  Address of register to write to for the slave device  
*       
* \param val
*  Byte of data to be written the slave's register
*
* \return
* An error code with the result of the Write procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   Error from I2C Component, `$i2cInstanceName`
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_Write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val) {
    /* Start, Slave Address & Write bit */
    uint32_t result = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE );
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* SUB Address */
    result = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* DATA */
    result = `$i2cInstanceName`_I2CMasterWriteByte(val, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* STOP Bit */
    `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
}

/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_WriteCmd()
****************************************************************************//**
* \brief
*  Sends a command to the target device, with no corresponding data
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param cmd
*  Command to write
*       
* \return
* An error code with the result of the Write procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   Error from I2C Component, `$i2cInstanceName`
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_WriteCmd(uint8_t deviceAddr, uint8_t cmd){
    /* Start, Slave Address & Write bit */
    uint32_t result = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE );
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Command */
    result = `$i2cInstanceName`_I2CMasterWriteByte(cmd, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* STOP Bit */
    `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
    
}


/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_WriteArray()
****************************************************************************//**
* \brief
*  Writes multiple bytes of data out the a specified device
*
* \param deviceAddr
*  Address of the I2C slave device
*
* \param regAddr
*  The starting address of the registers to write to
*
* \param array
*   Pointer to the array that contains the data to write
*
* \param len
*   The length of data to write out
*       
* \return
* An error code with the result of the Write procedure. 
* The possible error codes are:
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   `$INSTANCE_NAME`_ERR_OK                 | On successful operation
*   Error from I2C Component, `$i2cInstanceName`
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_WriteArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len) {
    /* Start, Slave Address & Write bit */
    uint32_t result = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE );
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* SUB Address */
    result = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* DATA */
    uint16_t i;
    for(i = ZERO; i < len; i++) {
        result = `$i2cInstanceName`_I2CMasterWriteByte(array[i], `$i2cInstanceName`_TIMEOUT_WRITE);
        if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    }
    /* STOP Bit */
    `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    if (result != `$INSTANCE_NAME`_ERR_OK) { return result;}
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
}



/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_Read()
****************************************************************************//**
* \brief 
* Read a byte of data from a slave
*
* \param deviceAddr [in]
*   Address of the slave device
*
* \param regAddr [in]
*   Memory address of the register to be read
*
* \param readVal [out]
*   Pointer to varable to place result into. If the command fails this will be 
*   the I2C opcode associated with the error.
*
* \Return
*   Error associated with the read value
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   i2cApi_ERR_OK                           | On successful operation
*   Error from I2C Component
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_Read(uint8_t deviceAddr, uint8_t regAddr, uint8_t * readVal) {
    /* Start, Slave Address & Write bit */
    uint32_t opResult = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* SUB Address */
    opResult = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Restart, Slave address & read bit */
    opResult = `$i2cInstanceName`_I2CMasterSendRestart(deviceAddr, `$i2cInstanceName`_I2C_READ_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* Place to return data */
    uint8_t rdByte;
    /* Read the data */
    opResult = `$i2cInstanceName`_I2CMasterReadByte(`$i2cInstanceName`_I2C_NAK_DATA, &rdByte, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Place the opResult into the pointer */
    *readVal = (uint8_t) rdByte;
    
    /* Send the stop bit */
    opResult = `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
    
/* Put the error code in readVal & return failed */
displayError:
    /* Place hardware specific value into the readVal */
    *readVal = opResult;
    /* return write failed */
    return `$INSTANCE_NAME`_ERR_READ;
}

/*******************************************************************************
* Function Name:  `$INSTANCE_NAME`_ReadArray()
****************************************************************************//**
* \brief 
*   Read multiple bytes of data from a slave
*
* \param deviceAddr [in]
*   Address of the slave device
*
* \param regAddr [in]
*   Memory address of the register to be read
*
* \param resultArray [out]
*   Pointer to array to place result into. If the command fails this will be 
*   the I2C opcode associated with the error.
*
* \param len [in]
*   Number of byte to read
*
* \Return
*   Error associated with the read value
*
*  Errors codes                             | Description
*   ------------                            | -----------
*   i2cApi_ERR_OK                           | On successful operation
*   Error from I2C Component
*
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_ReadArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len){
    /* Start, Slave Address & Write bit */
    uint32_t opResult = `$i2cInstanceName`_I2CMasterSendStart(deviceAddr, `$i2cInstanceName`_I2C_WRITE_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* SUB Address */
    opResult = `$i2cInstanceName`_I2CMasterWriteByte(regAddr, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Restart, Slave address & read bit */
    opResult = `$i2cInstanceName`_I2CMasterSendRestart(deviceAddr, `$i2cInstanceName`_I2C_READ_XFER_MODE, `$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* Place to return data */
    uint8_t rdByte;
    uint16_t i;
    for(i=ZERO; i<len; i++){
        /* Read the data */
        opResult = `$i2cInstanceName`_I2CMasterReadByte(`$i2cInstanceName`_I2C_ACK_DATA, &rdByte, `$i2cInstanceName`_TIMEOUT_WRITE);
        /* Return error and error code if operation failed */
        if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
        /* Place the opResult into the pointer */
        resultArray[i] = (uint8_t) rdByte;
    }
    
    /* Send the stop bit */
    opResult = `$i2cInstanceName`_I2CMasterSendStop(`$i2cInstanceName`_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != `$i2cInstanceName`_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    
    /* Indicate successs */
    return `$INSTANCE_NAME`_ERR_OK;
    
/* Put the error code in readVal & return failed */
displayError:
    /* Place hardware specific value into the readVal */
    resultArray[ZERO] = opResult;
    /* return write failed */
    return `$INSTANCE_NAME`_ERR_READ;
}
/* [] END OF FILE */
