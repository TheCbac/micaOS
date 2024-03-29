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
uint32_t i2cPsoc_start(COMMS_I2C_S *const i2c){
  /* Register the Psoc commands with the COMMS struct */
  i2c->write = i2cPsoc_write;
  i2c->writeCmd = i2cPsoc_writeCmd;
  i2c->writeArray = i2cPsoc_writeArray;
  i2c->read = i2cPsoc_read;
  i2c->readArray = i2cPsoc_readArray;
  i2c->readCmd = i2cPsoc_readCmd;
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
*******************************************************************************/
uint32_t i2cPsoc_write(uint8_t deviceAddr, uint8_t regAddr, uint8_t val) {
    /* Send the Register address */
    uint32_t error = COMMS_ERROR_NONE;
    uint8_t packet[2] = {regAddr, val};
    uint32_t opError = I2C_I2CMasterWriteBuf(deviceAddr, packet, 2, I2C_I2C_MODE_COMPLETE_XFER );
    /* Ensure Write was successful */
    if(!opError) {
        /* Wait for the transfer to complete */
        while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){} 
    } else {
        /* Report Write error */
        error = COMMS_ERROR_WRITE;
    }
    return error;
}

/*******************************************************************************
* Function Name:  i2cPsoc_writeCmd()
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
*******************************************************************************/
uint32_t i2cPsoc_writeCmd(uint8_t deviceAddr, uint8_t cmd){
    /* Send the Register address */
    uint32_t error = COMMS_ERROR_NONE;
    uint32_t opError = I2C_I2CMasterWriteBuf(deviceAddr, &cmd, 1, I2C_I2C_MODE_COMPLETE_XFER );
    /* Ensure Write was successful */
    if(!opError) {
        /* Wait for the transfer to complete */
        while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){} 
    } else {
        /* Report Write error */
        error = COMMS_ERROR_WRITE;
    }
    return error;
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
*******************************************************************************/
uint32_t i2cPsoc_writeArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len) {
    /* Send the Register address */
    uint32_t error = COMMS_ERROR_NONE;
    uint8_t data[128];
    data[0] = regAddr;
    memcpy(&data[1], array, len);
    uint32_t opError = I2C_I2CMasterWriteBuf(deviceAddr, data, len+1, I2C_I2C_MODE_COMPLETE_XFER );
    /* Ensure Write was successful */
    if(!opError) {
        /* Wait for the transfer to complete */
        while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){} 
    } else {
        /* Report Write error */
        error = COMMS_ERROR_WRITE;
        array[0] = opError; 
    }
    return error;
}

/*******************************************************************************
* Function Name:  i2cPsoc_read()
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
*******************************************************************************/
uint32_t i2cPsoc_read(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result) {
    /* Send the Register address */
    uint32_t error = COMMS_ERROR_NONE;
    uint32_t opError = I2C_I2CMasterWriteBuf(deviceAddr, &regAddr, 1,I2C_I2C_MODE_COMPLETE_XFER );
    /* Ensure Write was successful */
    if(!opError) {
        /* Wait for the transfer to complete */
        while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){} 
    
        /* Initiate the read */
        opError = I2C_I2CMasterReadBuf(deviceAddr, result, 1, I2C_I2C_MODE_COMPLETE_XFER );
        /* Ensure write was successful */
        if(!opError) {
            /* Wait for transfer to be complete */
            while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)){}
        } else {
            /* Report errors */
            error = COMMS_ERROR_READ_ARRAY;
            *result = opError; 
        }
    } else {
        /* Report Write error */
        error = COMMS_ERROR_WRITE;
        *result = opError; 
    }
    
    return error;
}

/*******************************************************************************
* Function Name:  i2cPsoc_readCmd()
****************************************************************************//**
* \brief 
*   Read multiple bytes of data from a slave, without commanding/writing first
*
* \param deviceAddr [in]
*   Address of the slave device
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
*******************************************************************************/
 uint32_t i2cPsoc_readCmd(uint8_t deviceAddr, uint8_t *result, uint16_t len){
     /* Send the Register address */
     uint32_t error = COMMS_ERROR_NONE;
     /* Initiate the read */
     uint32_t opError = I2C_I2CMasterReadBuf(deviceAddr, result, len, I2C_I2C_MODE_COMPLETE_XFER );
     /* Ensure write was successful */
     if(!opError) {
         /* Wait for transfer to be complete */
         while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)){}
     } else {
         /* Report errors */
         error = COMMS_ERROR_READ_ARRAY;
         result[0] = opError; 
     }    
     return error;
 }


/*******************************************************************************
* Function Name:  i2cPsoc_readArray()
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
*******************************************************************************/
uint32_t i2cPsoc_readArray(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len){
    /* Send the Register address */
    uint32_t error = COMMS_ERROR_NONE;
    uint32_t opError = I2C_I2CMasterWriteBuf(deviceAddr, &regAddr, 1,I2C_I2C_MODE_COMPLETE_XFER );
    /* Ensure Write was successful */
    if(!opError) {
        /* Wait for the transfer to complete */
        while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)){} 
    
        /* Initiate the read */
        opError = I2C_I2CMasterReadBuf(deviceAddr, resultArray, len, I2C_I2C_MODE_COMPLETE_XFER );
        /* Ensure write was successful */
        if(!opError) {
            /* Wait for transfer to be complete */
            while(0u == (I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)){}
        } else {
            /* Report errors */
            error = COMMS_ERROR_READ_ARRAY;
            resultArray[0] = opError; 
        }
    } else {
        /* Report Write error */
        error = COMMS_ERROR_WRITE;
        resultArray[0] = opError; 
    }
    
    return error;
}

/* [] END OF FILE */
