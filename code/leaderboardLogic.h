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
 * header file for leaderboard logic
 *
*/
#include <iostream>

#ifndef INC_2048_LEADERBOARDLOGIC_H
#define INC_2048_LEADERBOARDLOGIC_H
const size_t MAX_NICKNAMES_SCORES_COUNT = 5;

void appendLeaderboard(size_t, char *, unsigned);

void getNicknamesScores(size_t, char **, unsigned *, size_t &);

#endif
