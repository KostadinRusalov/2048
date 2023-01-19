#include <iostream>

#ifndef INC_2048_LEADERBOARDLOGIC_H
#define INC_2048_LEADERBOARDLOGIC_H
const size_t MAX_NICKNAMES_SCORES_COUNT = 5;

void appendLeaderboard(size_t, char *, unsigned);

void getNicknamesScores(size_t, char **, unsigned *, size_t &);

#endif
