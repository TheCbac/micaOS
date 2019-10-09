/***************************************************************************
*                              MICA  © 2019
*                               
*
* File: spi_psoc.h
* Workspace: cloudChamber_v5.1
* Project: Thermocouple_v5.1
* Version: 1.0.0
* Authors: C. Cheney
* 
* PCB: mcuPSoC4 5.2.1
* PSoC: 
*
* Brief:
*   Header for spi_psoc.c
*
* 2019.06.20  - Document Created
********************************************************************************/

/* Header Guard */
#ifndef spi_psoc_H
    #define spi_psoc_H
    /***************************************
    * Included files
    ***************************************/
    #include <stdint.h>
    #include "micaCommon.h"
    #include "micaComms.h"
    /***************************************
    * Macro Definitions
    ***************************************/
    #define SPI_PSOC_ERROR_NONE         (0) /**< No error occurred (or no error detection present) */
    
    #define SPI_PSOC_FLAG_NO_DATA       (0) /**< No Data was received */
    #define SPI_PSOC_FLAG_PENDING_RX    (1) /**< Data was already in the queue */
    
    #define SPI_PSOC_ERROR_NO_DATA      (1u << SPI_PSOC_FLAG_NO_DATA) /**< No Data was received */
    #define SPI_PSOC_ERROR_PENDING_RX   (1u << SPI_PSOC_FLAG_PENDING_RX) /**< Data was already in the queue */
    
    

    
    /***************************************
    * Enumerated Types
    ***************************************/

    
    /***************************************
    * Structures
    ***************************************/

    /***************************************
    * Function declarations 
    ***************************************/ 
    uint32_t spiPsoc_start(COMMS_SPI_S *spi);
    uint32_t spiPsoc_write(uint8_t addr, uint8_t val);
    uint32_t spiPsoc_read(uint8_t addr, uint8_t *ret);
    uint32_t spiPsoc_writeArray(uint8_t addr, uint8_t* array, uint16_t len);
    uint32_t spiPsoc_readArray(uint8_t addr, uint8_t* array, uint16_t len);
    uint32_t spiPsoc_getRxBufferSize(uint8_t *result);
    uint32_t spiPsoc_getTxBufferSize(uint8_t *result);
    uint32_t spiPsoc_clearRxBuffer(void);
    uint32_t spiPsoc_clearTxBuffer(void);

#endif /* spi_psoc_H */
/* [] END OF FILE */
