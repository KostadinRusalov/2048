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
 * header file for game logic
 *
*/
#include <iostream>

#ifndef INC_2048_GAMELOGIC_H
#define INC_2048_GAMELOGIC_H

void addRandomTile(unsigned **, size_t, bool &);

void moveBoard(unsigned **, size_t, char, unsigned &, bool &);

#endif
