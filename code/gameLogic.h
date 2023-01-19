#include <iostream>

#ifndef INC_2048_GAMELOGIC_H
#define INC_2048_GAMELOGIC_H

void addRandomTile(unsigned **, size_t, bool &);

void moveBoard(unsigned **, size_t, char, unsigned &, bool &);

void printBoard(const unsigned **, size_t, const char *, unsigned);

#endif
