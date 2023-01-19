/**
 *
 * Solution to course project # 4
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2022/2023
 *
 * @author Kostadin Rusalov
 * @idnumber 2MI0600244
 * @compiler GCC
 *
 * header file for helper functions
 *
*/
#include <iostream>

#ifndef INC_2048_HELPER_H
#define INC_2048_HELPER_H

const size_t MAX_NICKNAME_LENGTH = 12;
const size_t DIM_LOWER_BOUND = 4;
const size_t DIM_UPPER_BOUND = 10;

void clearConsole();

void copy(const char *, char *);

void swap(unsigned &, unsigned &);

void swap(char *, char *);

unsigned **createBoard(size_t);

bool isValid(size_t);

void deleteBoard(unsigned **, size_t);

int digitCount(unsigned);

void printSpaces(int);

int compare(const char *, const char *);

char **allocateMatrix(size_t , size_t );

void deallocateMatrix(char **, size_t );

char toChar(size_t );

size_t strlen(const char *);

void concat(char *str1, const char *);

#endif