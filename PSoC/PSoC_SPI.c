/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: PSoC_SPI.c
* Workspace: cloudChamber_v5.1
* Project: Thermocouple_v5.1
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: mcuPSoC4 5.2.1
* mcuType: PSoC
* partNumber:CY8C4245LQI-483
*
* Brief:
*   SPI for PSoC
*
* 2019.06.20  - Document Created
********************************************************************************/
#include "PSoC_SPI.h"
#include "project.h"



/*******************************************************************************
* Function Name: spiPsoc_start()
****************************************************************************//**
* \brief
*  PSoC to generic SPI Start wrapper
*   Starts the SPI bus
*
* \param spi
*   Pointer to the generic COMS_SPI_S to regster the functions
*  
*
* \return
*  An error code with the result of the start feature 
*******************************************************************************/
uint32_t spiPsoc_start(COMMS_SPI_S *spi){
    spi->write = spiPsoc_write;
    spi->read = spiPsoc_read;   
    spi->writeArray = spiPsoc_writeArray;   
    spi->readArray = spiPsoc_readArray;
    spi->getRxBufferSize = spiPsoc_getRxBufferSize;
    spi->getTxBufferSize = spiPsoc_getTxBufferSize;
    spi->clearRxBuffer = spiPsoc_clearRxBuffer;
    spi->clearTxBuffer = spiPsoc_clearTxBuffer;
    /* Start the component */
    SPIM_Start();
    spiPsoc_clearRxBuffer();
    spiPsoc_clearTxBuffer();
    
    return SPI_PSOC_ERROR_NONE;
}

/*******************************************************************************
* Function Name: spiPsoc_write()
****************************************************************************//**
* \brief
*  PSoC to generic SPI write reg wrapper
*   Writes a value to a specific register. This is currently a blocking function
*
* \param addr [in]
*   Register Address
*
* \param val [in]
*   Value to write to the register
*  
*
* \return
*  An error code with the result of the write feature 
*******************************************************************************/
uint32_t spiPsoc_write(uint8_t addr, uint8_t val){
    uint32_t error = SPI_PSOC_ERROR_NONE;
    /* Ensure RX queue is empty */
    if( SPIM_GetRxBufferSize() == ZERO) {
        SPIM_WriteTxData(addr);
        SPIM_WriteTxData(val);
        /* Wait until the data has been sent */
        while(SPIM_GetTxBufferSize()){}
        /* Wait for the data to be received */
        while(SPIM_GetRxBufferSize() != TWO) {}
        /* Throw away dummy bytes */
        SPIM_ClearRxBuffer();
    } else {
        error = SPI_PSOC_ERROR_PENDING_RX;
    }
    /* Return Error  */
    return error;
}

/*******************************************************************************
* Function Name: spiPsoc_read()
****************************************************************************//**
* \brief
*  PSoC to generic SPI read reg wrapper
*   Reads a value to a specific register - Assumes a software Buffer
*   Currently this a blocking function. 
*
* \param addr [in]
*   Register Address
*
* \param ret [out]
*   Pointer to return value 
*  
*
* \return
*  An error code with the result of the read feature 
*******************************************************************************/
uint32_t spiPsoc_read(uint8_t addr, uint8_t *ret){
    uint32_t error = SPI_PSOC_ERROR_NONE;
    /* Ensure RX queue is empty */
    if( SPIM_GetRxBufferSize() == ZERO) {
        /* Need to pulse the clock with empty byte */
        uint8_t array[TWO] = {addr, ZERO};
        SPIM_PutArray(array, TWO);
        /* Wait until the data has been sent */
        while(SPIM_GetTxBufferSize()){}
        /* Wait for the data to be received */
        while(SPIM_GetRxBufferSize() != TWO) {}
        /* Throw away dummy byte */
        SPIM_ReadRxData();
        *ret = SPIM_ReadRxData();  
    } else {
        error = SPI_PSOC_ERROR_PENDING_RX;
    }
    /* Return the error code */
    return error;
}

/*******************************************************************************
* Function Name: spiPsoc_writeArray()
****************************************************************************//**
* \brief
*  PSoC to generic SPI Write Aray
*   Writes an array of data out of the SPI port
*
* \param addr [in]
*   Register Address
*
* \param array [in]
*   Pointer array containing data elements
*
* \param len [in]
    Length of the data to transmit (excluding addr byte)
*
* \return
*  An error code with the result of the command
*******************************************************************************/
uint32_t spiPsoc_writeArray(uint8_t addr, uint8_t* array, uint16_t len){
    uint32_t error = SPI_PSOC_ERROR_NONE;
    /* Ensure RX queue is empty */
    if( SPIM_GetRxBufferSize() == ZERO) {
        SPIM_WriteTxData(addr);
        SPIM_PutArray(array, len);
        /* Wait until the data has been sent */
        while(SPIM_GetTxBufferSize()){}
        /* Wait for the dummy data to be received */
        while(SPIM_GetRxBufferSize() != (len + ONE)) {}
        /* Throw away dummy bytes */
        SPIM_ClearRxBuffer();
    } else {
        error = SPI_PSOC_ERROR_PENDING_RX;
    }
    return error;
}

/*******************************************************************************
* Function Name: spiPsoc_readArray()
****************************************************************************//**
* \brief
*  PSoC to generic SPI Read Aray
*   Writes an array of data out of the SPI port
*
* \param addr [in]
*   Register Address
*
* \param array [out]
*   Pointer array to return data elements. Must be >= len in size
*
* \param len [in]
    Number of bytes to read (excluding addr byte)
*
* \return
*  An error code with the result of the command
*******************************************************************************/
uint32_t spiPsoc_readArray(uint8_t addr, uint8_t* array, uint16_t len){
    uint32_t error = SPI_PSOC_ERROR_NONE;
    /* Ensure RX queue is empty */
    if( SPIM_GetRxBufferSize() == ZERO) {
        /* Write out the address byte */
        SPIM_WriteTxData(addr);
        uint16_t i;
        /* Read in the data */
        for(i=ZERO; i < len; i++){
            SPIM_WriteTxData(ZERO);   
        }
        /* Wait until the data has been sent */
        while(SPIM_GetTxBufferSize()){}
        /* Wait for the dummy data to be received */
        while(SPIM_GetRxBufferSize() != (len + ONE)) {}
        /* Throw away dummy byte (Addr) */
        SPIM_ReadRxData();
        /* Transmit out data */
        for(i=ZERO; i < len; i++){
            array[i] = SPIM_ReadRxData(); 
        }
    } else {
        error = SPI_PSOC_ERROR_PENDING_RX;
    }
    return error;
}
    
/*******************************************************************************
* Function Name: spiPsoc_getRxBufferSize()
****************************************************************************//**
* \brief
*  PSoC to generic SPI
*   Returns the size of the RX buffer
*
* \param result [out]
*   Result of the operation
*
* \return
*  Size of the RX buffer
*******************************************************************************/
uint32_t spiPsoc_getRxBufferSize(uint8_t *result){
    *result = SPIM_GetRxBufferSize();
    return SPI_PSOC_ERROR_NONE;  
}

/*******************************************************************************
* Function Name: spiPsoc_getTxBufferSize()
****************************************************************************//**
* \brief
*  PSoC to generic SPI
*   Returns the size of the TX buffer
*
* \param result [out]
*   Result of the operation
*
* \return
*  Size of the TX buffer
*******************************************************************************/
uint32_t spiPsoc_getTxBufferSize(uint8_t *result){
    *result = SPIM_GetTxBufferSize();   
    return SPI_PSOC_ERROR_NONE;  
}

/*******************************************************************************
* Function Name: spiPsoc_clearRxBuffer()
****************************************************************************//**
* \brief
*  PSoC to generic SPI
*   Clears the RX buffer
*
* \return
*  None
*******************************************************************************/
uint32_t spiPsoc_clearRxBuffer(void){
    SPIM_ClearRxBuffer();   
    return SPI_PSOC_ERROR_NONE;  
}

/*******************************************************************************
* Function Name: spiPsoc_clearTxBuffer()
****************************************************************************//**
* \brief
*  PSoC to generic SPI
*   Clears the TX buffer
*
* \return
*  None
*******************************************************************************/
uint32_t spiPsoc_clearTxBuffer(void){
    SPIM_ClearTxBuffer();   
    return SPI_PSOC_ERROR_NONE;  
}


/* [] END OF FILE */
