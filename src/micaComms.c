/***************************************************************************
*                                       MICA
* File: micaComms.c
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   Communications functions used in micaSO 
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2019.10.01 CC - Document created
********************************************************************************/
#include "micaComms.h"



/*******************************************************************************
* Function Name: Comms_validateUart()
****************************************************************************//**
* \brief
*  Validate the UART communication structure provided
*
* \param i2c
*  Pointer to the UART Struct
*
* \return
*  An error code with the result
*******************************************************************************/
uint32_t Comms_validateUart(COMMS_SERIAL_S *uart){
  uint32_t error = COMMS_ERROR_NONE;
  error |= (uart->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
  error |= (uart->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
  error |= (uart->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
  error |= (uart->getRxBufferSize == NULL)   ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
  error |= (uart->getTxBufferSize == NULL)   ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
  return error;
}



/*******************************************************************************
* Function Name: Comms_validateI2C()
****************************************************************************//**
* \brief
*  Validate the I2C communication structure provided
*
* \param i2c
*  Pointer to the I2C Struct
*
* \return
*  An error code with the result
*******************************************************************************/
uint32_t Comms_validateI2C(COMMS_I2C_S *i2c){
  uint32_t error = COMMS_ERROR_NONE;
  error |= (i2c->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
  error |= (i2c->writeCmd == NULL)    ? COMMS_ERROR_WRITE_CMD : COMMS_ERROR_NONE;
  error |= (i2c->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
  error |= (i2c->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
  error |= (i2c->readArray == NULL)   ? COMMS_ERROR_READ_ARRAY : COMMS_ERROR_NONE;
  return error;
}

/*******************************************************************************
* Function Name: Comms_validateSpi()
****************************************************************************//**
* \brief
*  Validate the UART communication structure provided
*
* \param i2c
*  Pointer to the UART Struct
*
* \return
*  An error code with the result
*******************************************************************************/
uint32_t Comms_validateSpi(COMMS_SPI_S *spi) {
    uint32_t error = COMMS_ERROR_NONE;
    error |= (spi->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
    error |= (spi->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
    error |= (spi->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
    error |= (spi->getRxBufferSize == NULL)   ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
    error |= (spi->getTxBufferSize == NULL)   ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
    error |= (spi->clearRxBuffer == NULL) ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
    error |= (spi->clearTxBuffer == NULL) ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
    
    return error;
}


/* [] END OF FILE */
