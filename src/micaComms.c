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
#include "micaCommon.h"


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
uint32_t Comms_validateUart(COMMS_UART_S *uart){
  uint32_t error = COMMS_ERROR_NONE;
  error |= (uart == NULL)               ? COMMS_ERROR_START : COMMS_ERROR_NONE;
  error |= (uart->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
  error |= (uart->print == NULL) ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
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
  error |= (i2c == NULL)              ? COMMS_ERROR_I2C : COMMS_ERROR_NONE; 
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
    error |= (spi == NULL)              ? COMMS_ERROR_SPI : COMMS_ERROR_NONE;
    error |= (spi->setActive == NULL)   ? COMMS_ERROR_SPI : COMMS_ERROR_NONE;
    error |= (spi->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
    error |= (spi->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
    error |= (spi->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
    error |= (spi->getRxBufferSize == NULL)   ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
    error |= (spi->getTxBufferSize == NULL)   ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
    error |= (spi->clearRxBuffer == NULL) ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
    error |= (spi->clearTxBuffer == NULL) ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
    
    return error;
}

/*******************************************************************************
* Function Name: float2Byte()
****************************************************************************//**
* \brief
*  Converts a float to a byte array
*
* \param fIn [In]
*  Input float
*
* \param array [out]
* Output array. Must be at lease 4 bytes long
*
* \return
*  none
*******************************************************************************/
void float2Byte(float fIn, uint8_t* array) {
  floatByte_U data;
  data.num = fIn;
  uint8_t i;
  for(i=0; i<BYTES_PER_FLOAT; i++) {
    array[i] = data.bytes[i];
  }
}

/*******************************************************************************
* Function Name: byte2Float()
****************************************************************************//**
* \brief
*  Converts a byte array to a float 
*
* \param array [in]
* Input array. Must be at lease 4 bytes long
*
* \param fOut [out]
*  Resulting float
*
* \return
*  none
*******************************************************************************/
void byte2Float(uint8_t* array, float* fOut) {
  floatByte_U data;
  uint8_t i;
  for(i=0; i<BYTES_PER_FLOAT; i++){
    data.bytes[i] = array[i];
  }
  *fOut = data.num;
}

/*******************************************************************************
* Function Name: uint32ToByte()
****************************************************************************//**
* \brief
*  Converts a uin32_t to an array
*
* \param in [in]
*  Uint32 input
*
* \param array [out]
*  Output array. Must be at lease 4 bytes long
*
* \return
*  none
*******************************************************************************/
void uint32ToByte(uint32_t in, uint8_t* array) {
  uint32Byte_U data;
  data.num = in;
  uint8_t i;
  for(i=0; i<BYTES_PER_UINT32; i++) {
    array[i] = data.bytes[i];
  }
}


/*******************************************************************************
* Function Name: byte2Float()
****************************************************************************//**
* \brief
*  Converts a byte array to a float 
*
* \param array [in]
* Input array. Must be at least 4 bytes long
*
* \param out [out]
*  Resulting uin3t2_t
*
* \return
*  none
*******************************************************************************/
void ByteToUint32(uint8_t* array, uint32_t* out){  
  uint32Byte_U data;
  uint8_t i;
  for(i=0; i<BYTES_PER_UINT32; i++){
    data.bytes[i] = array[i];
  }
  *out = data.num;
}



/* [] END OF FILE */
