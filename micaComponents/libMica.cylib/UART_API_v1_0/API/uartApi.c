/***************************************************************************//**
* \file `$INSTANCE_NAME`.c
* \version 0.1.0
*
* \brief
*   Simple print functionality
*
* \date Date Created:  2017.12.19
* \date Last Modified: 2017.12.19
*
********************************************************************************
* \copyright
* Copyright 2017, MICA. All rights reserved.
*******************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "`$includeFile`.h"
#include "micaCommon.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_putString()
****************************************************************************//**
*
* \brief Prints out the string starting at address passsed until a null character
    is reached.
*
* \param Address of array, must be zero terminated
*
* \return
* None
 *******************************************************************************/
void `$INSTANCE_NAME`_putString(char * str){
    /* Iterate until a zero is hit */
    while(*str){
        `$INSTANCE_NAME`_putChar(*str);
        /* Increment index */
        str++;
    }
    
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_putArray()
****************************************************************************//**
*
* \brief Prints out the data starting at the addressed passed in, for the specified 
*   length
*
* \param Array  - Address of array with the data to print
*
* \param length - Length of data to write
*
* \return
* None
 *******************************************************************************/
void `$INSTANCE_NAME`_putArray(uint8 * array, uint16 length){
    uint8 i;
    /* Loop until length satisfacition is met*/
    for(i=ZERO; i < length; i++){
        `$INSTANCE_NAME`_putChar(*array);
        /* Increment index */
        array++;
    }
    
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_changeBase()
****************************************************************************//**
*
* \brief Changes the base to hex from decimal
*
* \param Index
*  new value
*
* \return
* None
 *******************************************************************************/
static inline uint8* `$INSTANCE_NAME`_changeBase(uint32 Index)
{
    return (uint8*)("0123456789ABCDEF"+Index);
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_print()
****************************************************************************//**
*
* \brief Prints out the string
*
* \param pszFmt
*   Pointer to string, zero formatted. String to print out, accepts %d, %s, %x, %c
*
* \return
* None
 *******************************************************************************/
void `$INSTANCE_NAME`_print(char8 *pszFmt,...){
    uint8 *pszVal;
    uint32 iVal, xVal, i = 0, buffer[12], index = 1;
    uint8 cVal;
    uint32 *pArg;
    pArg =(uint32 *)&pszFmt;

    while(*pszFmt)
    {
        if('%' != *pszFmt)
        {
            `$INSTANCE_NAME`_putChar(*pszFmt);
            pszFmt++;
            continue;
        }
        pszFmt++;

        if(*pszFmt == 's')
        {
            pszVal = (uint8*)pArg[index++];
            for(; *pszVal != '\0'; pszVal++)
                `$INSTANCE_NAME`_putChar(*pszVal);
            pszFmt++;
            continue;
        }
        if(*pszFmt == 'd')
        {
            iVal = pArg[index++];
            i = 0;
            do{
                buffer[i++] = iVal % 10;
                iVal /= 10;
            }while(iVal);
            while(i > 0)
            {
                i--;
                `$INSTANCE_NAME`_putChar(*`$INSTANCE_NAME`_changeBase(buffer[i]));
            }
            pszFmt++;
            continue;
        }
        if(*pszFmt == 'c')
        {
            cVal = (uint8)pArg[index++];
            `$INSTANCE_NAME`_putChar(cVal);
            pszFmt++;
            continue;
        }
        if(*pszFmt == 'x')
        {
            xVal = pArg[index++];
            i = 0;
            do{
                buffer[i++] = xVal % 16;
                xVal /= 16;
            }while(xVal);
            if(i%2!=0)
                buffer[i++]=0;
            if(i<2)
                buffer[i++]=0;

            while(i > 0)
            {
                i--;
                `$INSTANCE_NAME`_putChar(*`$INSTANCE_NAME`_changeBase(buffer[i]));
            }
            pszFmt++;
            continue;
        }
        if(pszFmt == '\0')
        {
            break;
        }
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_txTest()
****************************************************************************//**
*
* \brief Transmits the a string listing the compile date and time out over the UART.
*
* \param runs
*    The number of times to execute the test function. Zero indicates
*       infinite runs. 
*
* \return
* None
*******************************************************************************/
void `$INSTANCE_NAME`_txTest(uint8 runs) {
    uint8 i = ZERO;
    /* Run through a specified number of times */
    while( (i++ < runs) || runs == ZERO) {
        /* Print the date and time the program was compiled */
        `$INSTANCE_NAME`_print("Compiled: ");
        `$INSTANCE_NAME`_print(__TIME__);
        `$INSTANCE_NAME`_print(" ");
        `$INSTANCE_NAME`_print(__DATE__);
        `$INSTANCE_NAME`_print("\r\n");
        /* Delay */
        MICA_delayMs(MICA_DELAY_MS_SEC_ONE);
    }
}  

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_printHeader()
****************************************************************************//**
*
* \brief Displays the program header
*
* \param time
*    Pass in __TIME__ macro
*
* \param date
*    Pass in __DATE__ macro
*
* \param name
*    Name of the program to display 
*
* \return
* None
*******************************************************************************/
    void `$INSTANCE_NAME`_printHeader(char* time, char* date, char * name){
    `$INSTANCE_NAME`_print("**************************************\r\n* ");
    `$INSTANCE_NAME`_print(name);
    `$INSTANCE_NAME`_print("\r\n*\r\n* Compiled at: ");
    `$INSTANCE_NAME`_print(time);
    `$INSTANCE_NAME`_print(" on ");
    `$INSTANCE_NAME`_print(date);
    `$INSTANCE_NAME`_print("\r\n**************************************\r\n");
}
/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_dummyTxArray()
****************************************************************************//**
* \brief
*  Dummy tx function for supressing output. Has no effect.
*
*******************************************************************************/
void  `$INSTANCE_NAME`_dummyTxArray(uint8 * array, uint16 len){
    (void) array;
    (void) len;
}

/* [] END OF FILE */
