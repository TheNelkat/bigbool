#ifndef BIGBOOL_H
#define BIGBOOL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_PARTS 20

#define ERR_OK 0
#define BAD_STR 1
#define BAD_SHIFT 2
#define EMPTY_VECTOR 3

/**
 *  VECTOR'S STRUCTURE
 *  
 *  uint8_t stores the number of vector
 *  last_bit == vector len 8
 *  last_byte == vector len /8
 *
 */
 
typedef struct BigBool
{
    uint8_t parts[MAX_PARTS];
    int last_bit;
    int last_byte;
} vector;


/**
 * 
 * ADDITIONAL FUNCTIONS
 * 
 */ 

    

/* int bb_random(vector* bb);

    Function: 
    Creates a random vector with random leght(no more than 20 bytes) and filled with random numbers.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb == NULL. */

int bb_random(vector* bb);

/* int bb_zero(vector* bb);

    Function:
    Fills a vector with zeros, change the legth of the vector(last_byte=0,last_bit=1).

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb == NULL. */

int bb_zero(vector* bb);

/* int copy(vector* org, vector* cop);

    Function:
    Copies a vector org to a vector cop.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if org == NULL or cop == NULL. */

int copy(vector* org, vector* cop);



/**
 * 
 *  CONVERSSION
 * 
 */


/* int bb_from_str(vector* bb, char* str);

    Function:
    Converts the string with '1' and '0' to the vector.

    Return value:
    ERR_OK on success;
    BAD_STR if str == NULL or contains characters other than '0' and '1' or str is too long;
    EMPTY_VECTOR if bb == NULL. */

int bb_from_str(vector* bb, char* str);

/* char* bb_to_str(vector* bb);

    Function:
    Converts a vector into a string.

    Return value:
    char* str on success;
    empty str if str == NULL;
    empty str if bb == NULL. */

char* bb_to_str(vector* bb);


/* int bb_from_uint64(vector* bb, uint64_t num);

    Function:
    Converts a uint64 number to a vector.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb == NULL;
    bb_zero(bb) if num == 0. */

int bb_from_uint64(vector* bb, uint64_t num);




/**
 * 
 * LOGICAL OPERATIONS
 * 
 */

    
/* int bb_not(vector* bb)

    Function:
    Makes a bitwise NOT.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb == NULL. */

int bb_not(vector* bb);

/* int bb_and(vector* bb1, vector* bb2)

    Function:
    Makes a bitwise AND.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb1 == NULL or bb2 == NULL. */

int bb_and(vector* bb1, vector* bb2);

/* int bb_or(vector* bb1, vector* bb2)

    Function:
    Makes a bitwise OR.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb1 == NULL or bb2 == NULL. */

int bb_or(vector* bb1, vector* bb2);

/* int bb_xor(vector* bb1, vector* bb2)

    Function:
    Makes a bitwise XOR.

    Return value:
    ERR_OK on success;
    EMPTY_VECTOR if bb1 == NULL or bb2 == NULL. */

int bb_xor(vector* bb1, vector* bb2);



/**
 * 
 * SHIFTS
 * 
 */


/* int right_shift_same(vector* bb, int shift);

    Function:
    Shift the vector to the right(makes the vector smaller), does not change the legth.

    Return value:
    ERR_OK on success;
    BAD_SHIFT if shift<1;
    EMPTY_VECTOR if bb1 == NULL. */

int right_shift_same(vector* bb, int shift);

/* int right_shift_dif(vector* bb, int shift);

    Function:
    Shift the vector to the right(makes the vector smaller), changes the legth.

    Return value:
    ERR_OK on success;
    BAD_SHIFT if shift<1;
    EMPTY_VECTOR if bb1 == NULL. */

int right_shift_dif(vector* bb, int shift);

/* int left_shift_same(vector* bb, int shift);

    Function:
    Shift the vector to the left(makes the vector bigger), does not change the legth.

    Return value:
    ERR_OK on success;
    BAD_SHIFT if shift<1;
    EMPTY_VECTOR if bb1 == NULL.  */

int left_shift_same(vector* bb, int shift);

/* int left_shift_dif(vector* bb, int shift);

    Function:
    Shift the vector to the left(makes the vector bigger), changes the legth.

    Return value:
    ERR_OK on success;
    BAD_SHIFT if shift<1 or legth of the vector with a shift > MAX_PARTS*8;
    EMPTY_VECTOR if bb1 == NULL.   */   

int left_shift_dif(vector* bb, int shift);

/* int cycle_right(vector* bb1, vector* bb2, int shift);

    Function:
    Does cycling shift to the rigth.

    Return value:
    ERR_OK on success;
    BAD_SHIFT if shift<1;
    EMPTY_VECTOR if bb1 == NULL or bb2 == NULL. */

int cycle_right(vector* bb1, vector* bb2, int shift);

/* int cycle_left(vector* bb1, vector* bb2, int shift);

    Function:
    Does cycling shift to the left.

    Return value:
    ERR_OK on success;
    BAD_SHIFT if shift<1;
    EMPTY_VECTOR if bb1 == NULL or bb2 == NULL. */

int cycle_left(vector* bb1, vector* bb2, int shift);


#endif