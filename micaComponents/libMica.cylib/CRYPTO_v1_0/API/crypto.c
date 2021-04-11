/***************************************************************************
*                                 MICA  © 2019
*                           MIT BioInstrumentation Lab
*
* File: `$INSTANCE_NAME`.c
* Workspace: micaComponents
* Project: libMica
* Version: 1.0.0
* Authors: Craig Cheney
* 
* PCB:  
* PSoC: 
*
* Brief:
*   Provides crypotological hashing functions.
*
* 2019.03.01  - Document Created
********************************************************************************/
#include "`$INSTANCE_NAME`.h"
#include "micaCommon.h"
#include <stdlib.h>

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_fisherYates()
****************************************************************************//**
* \brief
*  Implements the Fisher-Yates shuffle for creating a permutation 
*
*   https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#The_modern_algorithm
*   https://stackoverflow.com/questions/42321370/fisher-yates-shuffling-algorithm-in-c
*   
* \param array [in/out]
*   Array to shuffle params
*
* \param len [in]
*   Number of parameters to manipulate
*
* \param seed [in]
*   Seed value in creating a random number
*
* \return
*  none
*******************************************************************************/
void  `$INSTANCE_NAME`_fisherYates(uint8_t *array, uint16_t len, uint32_t seed ){
    uint8_t tmp;
    uint16_t i, j;
    /* Seed the random number generator */
    srand(seed);
    /* Shuffle the array */
    for(i = len - INDEX_ZERO_CORRECT; i > ZERO; i--){
        j = rand() % (i + ONE);
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_xorshift32()
****************************************************************************//**
* \brief
*  Generate a psuedorandom number from a seed. See https://en.wikipedia.org/wiki/Xorshift
*
* \param seed
*  Seed value input
*
* \return
*  Random number generator
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_rand_xorshift32(uint32_t seed){
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	uint32_t x = seed;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return x;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_hash_djb2()
****************************************************************************//**
* \brief
*  Hashing function for strings. See http://www.cse.yorku.ca/~oz/hash.html
*
* \param str
*  Pointer to null terminated string. 
*
* \return
*  Hash of the string
*******************************************************************************/
uint32_t `$INSTANCE_NAME`_hash_djb2(char *str) {
    uint32_t hash = 5381;
    int c;
    /* Iterate until null char */
    while( (c = *str++) ) {
        /* hash * 33 + c */ 
        hash = ((hash << 5) + c);
    }
    
    return hash;
}

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_printHash()
****************************************************************************//**
* \brief
*  Prints a hash
*
* \param hashString [in]
*  Packet to string that was hashed
*
* \param hashVaule [in]
* Value that was hashed 
* 
* \param fn [in]
*   Print function to use to display results
* 
* \return
*  None
*******************************************************************************/
  void `$INSTANCE_NAME`_printHash(char* hashString, uint32_t hashValue, void (*printFn)(char *pszFmt, ...)){
    printFn("\r\n");
    printFn(hashString);
    printFn(" hashed to %d", hashValue);
}


/* [] END OF FILE */
