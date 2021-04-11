/***************************************************************************//**
* \file micaConstants.h
* \version 1.1.0
*
* \brief
* Provides the constants required for libMICA
*
* \date Date Created:  2017.04.20
* \date Last Modified: 2017.08.22
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
/**
* \defgroup group_constants Constant
* \{
* Constants used across libMICA
*/

#ifndef MICA_CONSTANTS_H
#define MICA_CONSTANTS_H
    /***************************************
    * Included source files
    ***************************************/

    /***************************************
    * Macro definitions 
    ***************************************/    

    /**
    * \defgroup group_constants_digits Numeric Constants
    * \{
    * Constant numbers for readability
    */
        #define ZERO            (0u)    /**< Constant 0 */
        #define ONE             (1u)    /**< Constant 1 */
        #define TWO             (2u)    /**< Constant 2 */
        #define THREE           (3u)    /**< Constant 3 */
        #define FOUR            (4u)    /**< Constant 4 */
        #define FIVE            (5u)    /**< Constant 5 */
        #define SIX             (6u)    /**< Constant 6 */
        #define SEVEN           (7u)    /**< Constant 7 */
        #define EIGHT           (8u)    /**< Constant 8 */
        #define NINE            (9u)    /**< Constant 9 */
        #define NULL_OCTET      (0u)    /**< Null Octet */
    /* \} group_constants_digits*/

    /**
    * \defgroup group_constants_bits Bit Constants
    * \{
    * Constants for manipulating bit values
    */
        #define BITS_SINGLE_BIT         (0x01u)             /**< Single bit mask */
        #define BITS_ONE_NIBBLE         (4u)                /**< Number of bits in a nibble */
        #define BITS_ONE_BYTE           (8u)                /**< Number of bits in one byte */
        #define BITS_TWO_BYTES          (16u)               /**< Number of bits in two bytes */
        #define BITS_THREE_BYTES        (24u)               /**< Number of bits in three bytes */
        #define SHIFT_BYTE_HALF         (BITS_ONE_NIBBLE)   /**< Half Byte Shift*/
        #define SHIFT_BYTE_ONE          (BITS_ONE_BYTE)     /**< One Byte Shift*/
        #define SHIFT_BYTE_TWO          (BITS_TWO_BYTES)    /**< Two Byte Shift*/
        #define SHIFT_BYTE_THREE        (BITS_THREE_BYTES)  /**< Three Byte Shift*/
        #define MASK_HIGH_NIBBLE        (0xF0u)             /**< High nibble mask*/
        #define MASK_LOW_NIBBLE         (0x0Fu)             /**< Low nibble mask*/
        #define MASK_BYTE               (0xFFu)             /**< One byte mask*/
        #define MASK_12_BIT             (0x0FFFu)           /**< One and a half byte mask*/
        #define MASK_TWO_BYTE           (0xFFFFu)           /**< Two byte mask*/
        #define MASK_THREE_BYTE         (0xFFFFFFu)         /**< Three byte mask*/
        #define MASK_ODD                (BITS_SINGLE_BIT)   /**< Odd mask*/
    /* \} group_constants_bits*/

    /**
    * \defgroup group_constants_index Index Constants
    * \{
    * Indexes for arrays and such
    */
        #define MICA_USE            (1u) /**< Parameter or options is enabled and used in the application*/
        #define MICA_NO_USE         (0u) /**< Parameter or options is NEITHER enabled NOR used in the application*/
        #define INDEX_ZERO                      (ZERO)  /**< Reset and index to zero */
        #define INDEX_ZERO_CORRECT              (ONE)   /**< Correct for arrays being zero indexed*/
    
/* \} group_constants_index*/

    /**
    * \defgroup group_constants_ids Sensor Ids
    * \{
    * The ID of MICA sensors
    */
        #define MICA_ID_ACC                         (0x01u) /**< ID of the accelerometer */
        #define MICA_ID_GYR                         (0x02u) /**< ID of the Gyroscope */
        #define MICA_ID_MAG                         (0x03u) /**< ID of the Magnetometer */
        #define MICA_ID_ADC                         (0x04u) /**< ID of the Analog to Digital Converter */
        #define MICA_ID_LCELL                       (0x06u) /**< ID of the Load cell */
    /* \} group_constants_ids*/

    /**
    * \defgroup group_constants_packets Packet Constants
    * \{
    *  Constants that the define the shape the BLE MICA packets
    */
        #define MICA_PACKET_START_LEN                   (4u)    /**< Length in bytes of the MICA start packet */
        #define MICA_PACKET_START_INDEX_SENSOR_TYPE     (0u)    /**< Index of the Sensor type */
        #define MICA_PACKET_START_INDEX_CHAN_ENABLED    (1u)    /**< Index of the bit mask for enabled channels */
        #define MICA_PACKET_START_INDEX_PC_MSB          (2u)    /**< Index of the period count Most Significant Byte */
        #define MICA_PACKET_START_INDEX_PC_LSB          (3u)    /**< Index of the period count Lease Significant Byte */

    /* \} group_constants_packets*/

    /**
    * \defgroup group_constants_channel Sensor Channels
    * \{
    * Constants for the sensor channels
    */
        #define MICA_CHANNEL_INDEX_X                 (0u)    /**< index of the X Channel*/
        #define MICA_CHANNEL_INDEX_Y                 (1u)    /**< Index of the Y channel*/
        #define MICA_CHANNEL_INDEX_Z                 (2u)    /**< Index of the Z channel*/
        #define MICA_CHANNEL_INDEX_NUM_CHAN          (0u)    /**< Index of the number of channels that data was collected from*/      
        #define MICA_CHANNEL_INDEX_DATA              (1u)    /**< Index of the start of data when reported by a sensor */
        #define MICA_CHANNEL_MASK_X                  (1u << MICA_CHANNEL_INDEX_X) /**< Mask of the X channel*/
        #define MICA_CHANNEL_MASK_Y                  (1u << MICA_CHANNEL_INDEX_Y) /**< Mask of the Y channel*/
        #define MICA_CHANNEL_MASK_Z                  (1u << MICA_CHANNEL_INDEX_Z) /**< Mask of the Z channel*/
    /* \} group_constants_channel*/

    /** 
    * \defgroup group_ble_macros_actuation Actuation     
    * \{    
    * This needs to be reconciled with micaBle.h definitions
    */
        #define MICA_ACT_CMD_MOTORS             (1u) /**< Command for talking to the motors */
        #define MICA_ACT_CMD_MOTORS_INDEX_CTRL  (0u) /**< Index of the control register in the motor command */
        #define MICA_ACT_CMD_MOTORS_INDEX_PWM_R (1u) /**< Index of the Right PWM compare val in the motor command */
        #define MICA_ACT_CMD_MOTORS_INDEX_PWM_L (2u) /**< Index of the Left PWM compare val in the motor command */
        
    /* \} group_ble_macros_actuation */
        
    /** 
    * \defgroup group_ble_macros_sensing Sensing     
    * \{    
    * Constants for interacting with the sensing module
    */
        #define MICA_SENSE_BYTES_PER_PARAM      (2u) /**< Number of bytes contained in a dynamic param for a sensor (address & value) */
        #define MICA_SENSE_CMD_START            (1u) /**< Start command for a given sensor(s) */
        #define MICA_SENSE_CMD_STOP             (0u) /**< Stop command for a given sensor(s) */
    /* \} group_ble_macros_sensing */

    /** 
    * \defgroup group_ble_macros_timing Timing     
    * \{    
    * Constants for BLE to Timing
    */
        #define MICA_TIMING_PC_TO_USEC          (10u) /**< Number of microseconds per period count (100 kHz) */
        #define SHIFT_FLAG_ROLLUNDER            (3u)    /**< Position for the packet rollunder flag */
        #define SHIFT_SEC_ELAP                  (4u)    /**< Position of the packet elapsed flag*/        
        #define MASK_FLAG_ROLLUNDER             (0x08u) /**< Mask for the packet rollunder flag */
        #define MASK_SEC_ELAP                   (0x07u) /**< Mask for the Seconds elapsed flag */

        #define BYTES_PER_CHANNEL               (2u)   /**< Number of bytes for each channel */
        #define TIME_HEADER_LEN                 (3u)   /**< Number of bytes in the time data header */
        #define NO_OFFSET                       (0u)   /**< Do not include an offset when send data via the BLE */
        // #define THREE_AXIS_DATA_LEN              (0x04u)/**< Mask for the Seconds elapsed flag */
    /* \} group_ble_macros_timing */
    
#endif /* MICA_CONSTANTS_H */
/* \} group_constants*/

/* [] END OF FILE */
