/***************************************************************************
*                                 MICA  © 2019
*
* File: PSoC_i2c.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
* 
*
* Brief:
*   Wrapper class that provides a generic I2C interface for Psoc,
*   using the Wire library.
*
* 2019.10.08  - Document Created
********************************************************************************/
#include "PSoC_i2c.h"
#include "project.h"
#include "I2C_I2C.h"

/*******************************************************************************
* Function Name: i2cPsoc_start()
****************************************************************************//**
* \brief
*  Wire to generic I2C Start Wrapper
*  Starts the I2C bus
*
* \param i2c
*   Pointer to the generic COMMS_I2C_S to register the functions.
*
* \return
* An error code with the result of the start procedure 
*******************************************************************************/
uint32_t i2cPsoc_start(COMMS_I2C_S *i2c){
  /* Register the Psoc commands with the COMMS struct */
  i2c->write = i2cPsoc_write;
  i2c->writeCmd = i2cPsoc_writeCmd;
  i2c->writeArray = i2cPsoc_writeArray;
  i2c->read = i2cPsoc_read;
  i2c->readArray = i2cPsoc_readArray2;
  /* Start the bus */
  I2C_Start();
  return COMMS_ERROR_NONE;
}


/*******************************************************************************
* Function Name:  i2cPsoc_Write()
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
*   COMMS_ERROR_NONE                 | On successful operation
*   Error from I2C Component, I2C
*
*******************************************************************************/
uint32_t i2cPsoc_write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val) {
    /* Start, Slave Address & Write bit */
    uint32_t result = I2C_I2CMasterSendStart(deviceAddr, I2C_I2C_WRITE_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE );
    if (result != COMMS_ERROR_NONE) { return result;}
    /* SUB Address */
    result = I2C_I2CMasterWriteByte(regAddr, I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* DATA */
    result = I2C_I2CMasterWriteByte(val, I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* STOP Bit */
    I2C_I2CMasterSendStop(I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* Indicate successs */
    return COMMS_ERROR_NONE;
}



/*******************************************************************************
* Function Name:  i2cPsoc_WriteCmd()
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
*   COMMS_ERROR_NONE                 | On successful operation
*   Error from I2C Component, I2C
*
*******************************************************************************/
uint32_t i2cPsoc_writeCmd(uint8_t deviceAddr, uint8_t cmd){
    /* Start, Slave Address & Write bit */
    uint32_t result = I2C_I2CMasterSendStart(deviceAddr, I2C_I2C_WRITE_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE );
    if (result != COMMS_ERROR_NONE) { return result;}
    /* Command */
    result = I2C_I2CMasterWriteByte(cmd, I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* STOP Bit */
    I2C_I2CMasterSendStop(I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* Indicate successs */
    return COMMS_ERROR_NONE;
    
}


/*******************************************************************************
* Function Name:  i2cPsoc_WriteArray()
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
*   COMMS_ERROR_NONE                 | On successful operation
*   Error from I2C Component, I2C
*
*******************************************************************************/
uint32_t i2cPsoc_writeArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len) {
    /* Start, Slave Address & Write bit */
    uint32_t result = I2C_I2CMasterSendStart(deviceAddr, I2C_I2C_WRITE_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE );
    if (result != COMMS_ERROR_NONE) { return result;}
    /* SUB Address */
    result = I2C_I2CMasterWriteByte(regAddr, I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* DATA */
    uint16_t i;
    for(i = ZERO; i < len; i++) {
        result = I2C_I2CMasterWriteByte(array[i], I2C_PSOC_TIMEOUT_WRITE);
        if (result != COMMS_ERROR_NONE) { return result;}
    }
    /* STOP Bit */
    I2C_I2CMasterSendStop(I2C_PSOC_TIMEOUT_WRITE);
    if (result != COMMS_ERROR_NONE) { return result;}
    /* Indicate successs */
    return COMMS_ERROR_NONE;
}



/*******************************************************************************
* Function Name:  i2cPsoc_Read()
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
*   COMMS_ERROR_NONE                           | On successful operation
*   Error from I2C Component
*
*******************************************************************************/
uint32_t i2cPsoc_read(uint8_t deviceAddr, uint8_t regAddr, uint8_t * readVal) {
    /* Start, Slave Address & Write bit */
    uint32_t opResult = I2C_I2CMasterSendStart(deviceAddr, I2C_I2C_WRITE_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* SUB Address */
    opResult = I2C_I2CMasterWriteByte(regAddr, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Restart, Slave address & read bit */
    opResult = I2C_I2CMasterSendRestart(deviceAddr, I2C_I2C_READ_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* Place to return data */
    uint8_t rdByte;
    /* Read the data */
    opResult = I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA, &rdByte, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Place the opResult into the pointer */
    *readVal = (uint8_t) rdByte;
    
    /* Send the stop bit */
    opResult = I2C_I2CMasterSendStop(I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    
    /* Indicate successs */
    return COMMS_ERROR_NONE;
    
/* Put the error code in readVal & return failed */
displayError:
    /* Place hardware specific value into the readVal */
    *readVal = opResult;
    /* return write failed */
    return COMMS_ERROR_READ;
}


uint32_t i2cPsoc_readArray2(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len){
    /* Start, Slave Address & Write bit */
    uint32_t opResult = I2C_I2CMasterSendStart(deviceAddr, I2C_I2C_WRITE_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* SUB Address */
    opResult = I2C_I2CMasterWriteByte(regAddr, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Restart, Slave address & read bit */
//    opResult = I2C_I2CMasterSendRestart(deviceAddr, I2C_I2C_READ_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE);
//    /* Return error and error code if operation failed */
//    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* Place to return data */
    opResult = I2C_I2CMasterReadBuf(deviceAddr, resultArray, len, I2C_I2C_MODE_REPEAT_START  );
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) {
        goto displayError; 
    } else {
        /* Wait for transfer to complete */
        while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)){}
        
//        if( I2C_I2CMasterGetReadBufSize() != 2) {
//            goto displayError;
//        }
    }
    
//    uint8_t rdByte;
//    uint16_t i;
//    for(i=ZERO; i<len; i++){
//        /* Read the data */
//        opResult = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA, &rdByte, I2C_PSOC_TIMEOUT_WRITE);
//        /* Return error and error code if operation failed */
//        if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
//        /* Place the opResult into the pointer */
//        resultArray[i] = rdByte;
//    }
    
//    /* Send the stop bit */
//    opResult = I2C_I2CMasterSendStop(I2C_PSOC_TIMEOUT_WRITE);
//    /* Return error and error code if operation failed */
//    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    
    /* Indicate successs */
    return COMMS_ERROR_NONE;
    
/* Put the error code in readVal & return failed */
displayError:
    /* Place hardware specific value into the readVal */
    resultArray[ZERO] = opResult;
    /* return write failed */
    return COMMS_ERROR_READ;
}


/*******************************************************************************
* Function Name:  i2cPsoc_ReadArray()
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
*   COMMS_ERROR_NONE                           | On successful operation
*   Error from I2C Component
*
*******************************************************************************/
uint32_t i2cPsoc_readArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len){
    /* Start, Slave Address & Write bit */
    uint32_t opResult = I2C_I2CMasterSendStart(deviceAddr, I2C_I2C_WRITE_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* SUB Address */
    opResult = I2C_I2CMasterWriteByte(regAddr, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    /* Restart, Slave address & read bit */
    opResult = I2C_I2CMasterSendRestart(deviceAddr, I2C_I2C_READ_XFER_MODE, I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    /* Place to return data */
    uint8_t rdByte;
    uint16_t i;
    for(i=ZERO; i<len; i++){
        /* Read the data */
        opResult = I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA, &rdByte, I2C_PSOC_TIMEOUT_WRITE);
        /* Return error and error code if operation failed */
        if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
        /* Place the opResult into the pointer */
        resultArray[i] = rdByte;
    }
    
    /* Send the stop bit */
    opResult = I2C_I2CMasterSendStop(I2C_PSOC_TIMEOUT_WRITE);
    /* Return error and error code if operation failed */
    if (opResult != I2C_I2C_MSTR_NO_ERROR ) { goto displayError; } 
    
    
    /* Indicate successs */
    return COMMS_ERROR_NONE;
    
/* Put the error code in readVal & return failed */
displayError:
    /* Place hardware specific value into the readVal */
    resultArray[ZERO] = opResult;
    /* return write failed */
    return COMMS_ERROR_READ;
}

/* [] END OF FILE */
