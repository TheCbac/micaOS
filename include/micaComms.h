/***************************************************************************
*                                       MICA
* File: micaComms.h
* Workspace: micaOS
* Version: v2.0.0
* Author: Craig Cheney
*
* Brief:
*   Defitions for use with Communication
* 
* Authors:
*   Craig Cheney
*
* Change Log:
*   2019.10.01 CC - Document created
********************************************************************************/
/* Header Guard */
#ifndef MICA_COMMS_H
  #define MICA_COMMS_H
  /***************************************
  * Included Files
  ***************************************/  
  #include <stdint.h>
  /***************************************
  * Macros
  ***************************************/  
  #define COMMS_ERROR_SHIFT_WRITE             (0) /**< Shift of a null write function */
  #define COMMS_ERROR_SHIFT_WRITE_CMD         (1) /**< Shift of a null write command function */
  #define COMMS_ERROR_SHIFT_WRITE_ARRAY       (2) /**< Shift of a null write array function */
  #define COMMS_ERROR_SHIFT_READ              (3) /**< Shift of a null read function */
  #define COMMS_ERROR_SHIFT_READ_ARRAY        (4) /**< Shift of a null read array function */
  #define COMMS_ERROR_SHIFT_RXBUFFER          (5) /**< Shift of a null getRxBuffer function */
  #define COMMS_ERROR_SHIFT_TXBUFFER          (6) /**< Shift of a null getTxBuffer function */


  #define COMMS_ERROR_NONE                    (0) /**< No error occurred */
  #define COMMS_ERROR_WRITE                   (1u << COMMS_ERROR_SHIFT_WRITE)       /**< Flag of a null write function */
  #define COMMS_ERROR_WRITE_CMD               (1u << COMMS_ERROR_SHIFT_WRITE_CMD)   /**< Flag of a null write command function */
  #define COMMS_ERROR_WRITE_ARRAY             (1u << COMMS_ERROR_SHIFT_WRITE_ARRAY) /**< Flag of a null write array function */
  #define COMMS_ERROR_READ                    (1u << COMMS_ERROR_SHIFT_READ)        /**< Flag of a null read function */
  #define COMMS_ERROR_READ_ARRAY              (1u << COMMS_ERROR_SHIFT_READ_ARRAY)  /**< Flag of a null read array function */
  #define COMMS_ERROR_RXBUFFER                (1u << COMMS_ERROR_SHIFT_RXBUFFER)  /**< Flag of a null getRxBuffer function  */
  #define COMMS_ERROR_TXBUFFER                (1u << COMMS_ERROR_SHIFT_TXBUFFER)  /**< Flag of a null getTxBuffer function */


  /***************************************
  * Structs
  ***************************************/ 

  /* Serial  */
  typedef struct {
    uint32_t (*write)(uint8_t val);                         /**< Write out a byte of data via UART */
    uint32_t (*writeArray)(uint8_t *array, uint16_t len);  /**< Write multiple registers */
    uint32_t (*read)(uint8_t *result);                      /**< Read data from RX buffer */
    uint32_t (*readArray)(uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */
    uint32_t (*getRxBufferSize)(uint8_t *result);           /**< Retrieve number of bytes pending in RX buffer*/
    uint32_t (*getTxBufferSize)(uint8_t *result);           /**< Retrieve number of bytes pending in TX buffer*/
  } COMMS_SERIAL_S;
    
  /* I2C */
  typedef struct {
    uint32_t (*write)(uint8_t deviceAddr, uint8_t regAddr, uint8_t val);                        /**< Write to an I2C register */
    uint32_t (*writeCmd)(uint8_t deviceAddr, uint8_t cmd);                                      /**< Send a command via I2C */
    uint32_t (*writeArray)(uint8_t deviceAddr, uint8_t regAddr, uint8_t *array, uint16_t len);  /**< Write multiple registers */
    uint32_t (*read)(uint8_t deviceAddr, uint8_t regAddr, uint8_t *result);  
    uint32_t (*readArray)(uint8_t deviceAddr, uint8_t regAddr, uint8_t *resultArray, uint16_t len);   /**< Read multiple values from a device */
  } COMMS_I2C_S;

  /* SPI */
  typedef struct {
    uint32_t (*write) (uint8_t addr, uint8_t val);
    uint32_t (*read) (uint8_t addr, uint8_t *ret);
    uint32_t (*writeArray)(uint8_t addr, uint8_t* array, uint16_t len);
    uint32_t (*readArray) (uint8_t addr, uint8_t* array, uint16_t len);
    uint32_t (*getRxBufferSize)(uint8_t *result);           /**< Retrieve number of bytes pending in RX buffer*/
    uint32_t (*getTxBufferSize)(uint8_t *result);           /**< Retrieve number of bytes pending in TX buffer*/
    uint32_t (*clearRxBuffer)(void);
    uint32_t (*clearTxBuffer)(void);
  } COMMS_SPI_S;

  /***************************************
  * Function Prototypes
  ***************************************/ 
  uint32_t Comms_validateUart(COMMS_SERIAL_S *uart);
  uint32_t Comms_validateI2C(COMMS_I2C_S *i2c);
  uint32_t Comms_validateSpi(COMMS_SPI_S *spi);

#endif /* MICA_COMMS_H */

/* [] END OF FILE */

