/***************************************************************************
*                                       MICA
* File: micaCommon.c
* Workspace: micaCompnents
* Project Name: libMica
* Version: v1.0
* Author: Craig Cheney
*
* Brief:
*   Generic Functions used in MICA
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2018.03.03 CC - Document created
********************************************************************************/
#include "micaCommon.h"

/*******************************************************************************
* Function Name: to_degrees()
****************************************************************************//**
*
* \brief Converts a radian argument to degrees
*
* \param radian - value to convert
*
* \return the angle in degrees
*
*
*******************************************************************************/
inline float to_degrees(float radians){
    return radians * (180.0f) / PI;
}
/*******************************************************************************
* Function Name: to_radians()
****************************************************************************//**
*
* \brief Converts a degree argument to radians
*
* \param degrees - value to convert, in degrees
*
* \return the angle in radians
*
*
*******************************************************************************/
inline float to_radians(float degrees){
    return degrees *  PI / (180.0f);
}

///*******************************************************************************
//* Function Name: Comms_validateUart()
//****************************************************************************//**
//* \brief
//*  Validate the UART communication structure provided
//*
//* \param i2c
//*  Pointer to the UART Struct
//*
//* \return
//*  An error code with the result
//*******************************************************************************/
//uint32_t Comms_validateUart(COMMS_UART_S *uart){
//  uint32_t error = COMMS_ERROR_NONE;
//  error |= (uart->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
//  error |= (uart->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
//  error |= (uart->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
//  error |= (uart->getRxBufferSize == NULL)   ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
//  error |= (uart->getTxBufferSize == NULL)   ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
//  return error;
//}
//
//
//
///*******************************************************************************
//* Function Name: Comms_validateI2C()
//****************************************************************************//**
//* \brief
//*  Validate the I2C communication structure provided
//*
//* \param i2c
//*  Pointer to the I2C Struct
//*
//* \return
//*  An error code with the result
//*******************************************************************************/
//uint32_t Comms_validateI2C(COMMS_I2C_S *i2c){
//  uint32_t error = COMMS_ERROR_NONE;
//  error |= (i2c->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
//  error |= (i2c->writeCmd == NULL)    ? COMMS_ERROR_WRITE_CMD : COMMS_ERROR_NONE;
//  error |= (i2c->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
//  error |= (i2c->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
//  error |= (i2c->readArray == NULL)   ? COMMS_ERROR_READ_ARRAY : COMMS_ERROR_NONE;
//  return error;
//}
//
///*******************************************************************************
//* Function Name: Comms_validateSpi()
//****************************************************************************//**
//* \brief
//*  Validate the UART communication structure provided
//*
//* \param i2c
//*  Pointer to the UART Struct
//*
//* \return
//*  An error code with the result
//*******************************************************************************/
//uint32_t Comms_validateSpi(COMMS_SPI_S *spi) {
//    uint32_t error = COMMS_ERROR_NONE;
//    error |= (spi->write == NULL)       ? COMMS_ERROR_WRITE : COMMS_ERROR_NONE;
//    error |= (spi->writeArray == NULL)  ? COMMS_ERROR_WRITE_ARRAY : COMMS_ERROR_NONE;
//    error |= (spi->read == NULL)        ? COMMS_ERROR_READ : COMMS_ERROR_NONE;
//    error |= (spi->getRxBufferSize == NULL)   ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
//    error |= (spi->getTxBufferSize == NULL)   ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
//    error |= (spi->clearRxBuffer == NULL) ? COMMS_ERROR_RXBUFFER : COMMS_ERROR_NONE;
//    error |= (spi->clearTxBuffer == NULL) ? COMMS_ERROR_TXBUFFER : COMMS_ERROR_NONE;
//    
//    return error;
//}


/* [] END OF FILE */
