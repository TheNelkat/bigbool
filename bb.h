#ifndef BB_H
#define BB_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_PARTS 20

#define ERR_OK 0
#define BAD_STR 1
#define MEM_NOT_ALLOC 2
#define BAD_SHIFT 3
#define EMPTY_VECTOR 4

typedef struct BigBool
{
    uint8_t parts[MAX_PARTS];
    int last_bit;
    int last_byte;
} vector;

// vector* bb_z(vector* bb)

//  Function:
//  Fill the whole vector with zeros
vector* bb_z(vector* bb);


// vector* BB_from_str(char* str, int len);
// Function:
// Convert the string with '1' and '0' to the vector
vector* BB_from_str(char* str, int len);



// char* bb_to_str(vector* bb)
// Function:
// Convert vector into string
char* bb_to_str(vector* bb);



// vector* left_shift(vector* bb_old, int size_of_shift)

// Function:
// Shift the vector to the left
vector* left_shift(vector* bb_old, int size_of_shift);


// vector* right_shift(vector* bb_old, int size_of_shift)

// Function:
// Shift the vector to the left
vector* right_shift(vector* bb_old, int size_of_shift);


// vector* cycle_right(vector* bb, int size_of_shift)

// Function:
// Does cycling shift to the right
vector* cycle_right(vector* bb, int size_of_shift);


// vector* cycle_left(vector* bb, int size_of_shift)

// Function:
// Does cycling shift to the left
vector* cycle_left(vector* bb, int size_of_shift);


// vector* bb_and(vector* bb1, vector* bb2)

// Function:
// Makes a bitwise AND
vector* bb_and(vector* bb1, vector* bb2);


// vector* bb_or(vector* bb1, vector* bb2)

// Function:
// Makes a bitwise OR
vector* bb_or(vector* bb1, vector* bb2);


// vector* bb_xor(vector* bb1, vector* bb2)

// Function:
// Makes a bitwise XOR
vector* bb_xor(vector* bb1, vector* bb2);


// vector* bb_not(vector* bb)

// Function:
// Makes a bitwise NOT
vector* bb_not(vector* bb);



#endif