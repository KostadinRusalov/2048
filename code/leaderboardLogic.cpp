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
 * file for reading and writing leaderboard files
 *
*/
#include <iostream>
#include <fstream>
#include "leaderboardLogic.h"
#include "helper.h"

const size_t MAX_FILENAME_LEN = 34;
const char DELIMITER = ' ';

const char DIRECTORY[] = "../leaderboards/leaderboard";
const char TXT_EXTENSION[] = ".txt";

char *getFilename(size_t dim) {
    if (!isValid(dim)) {
        return nullptr;
    }
    char *filename = new char[MAX_FILENAME_LEN]{};
    concat(filename, DIRECTORY);
    if (dim == DIM_UPPER_BOUND) {
        char strDim[] = "10";
        concat(filename, strDim);
        concat(filename, TXT_EXTENSION);
    } else {
        char strDim[2];
        strDim[0] = toChar(dim);
        strDim[1] = '\0';
        concat(filename, strDim);
        concat(filename, TXT_EXTENSION);

    }
    return filename;
}

void getNicknamesScores(size_t dim, char **nicknames, unsigned *scores, size_t &count) {
    if (!isValid(dim)) {
        return;
    }
    char *filename = getFilename(dim);
    std::ifstream leaderboardFile(filename);

    if (!leaderboardFile.is_open()) {
        delete[] filename;
        return;
    }
    count = 0;
    while (!leaderboardFile.eof()) {
        leaderboardFile >> nicknames[count] >> scores[count];
        ++count;
    }
    // when the file is empty count is still 1
    if (nicknames[0][0] == '\0') {
        count = 0;
    }

    leaderboardFile.close();
    delete[] filename;
}

void addNicknameScore(char *nickname, unsigned score, char **nicknames, unsigned *scores, size_t &count) {
    if (count == 0) {
        nicknames[count] = nickname;
        scores[count] = score;
        ++count;
        return;
    }

    if (count == MAX_NICKNAMES_SCORES_COUNT && score <= scores[count - 1]) {
        return;
    }

    if (count == MAX_NICKNAMES_SCORES_COUNT) {
        nicknames[count - 1] = nickname;
        scores[count - 1] = score;
    } else {
        nicknames[count] = nickname;
        scores[count] = score;
        ++count;
    }

    int idx = (int) count - 1;
    while (idx > 0 && scores[idx] > scores[idx - 1]) {
        swap(scores[idx], scores[idx - 1]);
        swap(nicknames[idx], nicknames[idx - 1]);
        --idx;
    }
}

void appendLeaderboard(size_t dim, char *nickname, unsigned score) {
    if (!isValid(dim)) {
        return;
    }

    size_t count = 0;
    char **nicknames = allocateMatrix(MAX_NICKNAMES_SCORES_COUNT, MAX_NICKNAME_LENGTH);
    unsigned *scores = new unsigned[MAX_NICKNAMES_SCORES_COUNT];

    getNicknamesScores(dim, nicknames, scores, count);

    addNicknameScore(nickname, score, nicknames, scores, count);

    char *filename = getFilename(dim);
    std::ofstream leaderboardFile(filename);

    if (!leaderboardFile.is_open()) {
        delete[] filename;
        delete[] scores;
        deallocateMatrix(nicknames, MAX_NICKNAMES_SCORES_COUNT);
        return;
    }

    for (size_t idx = 0; idx < count - 1; ++idx) {
        leaderboardFile << nicknames[idx] << DELIMITER << scores[idx] << DELIMITER;
    }
    leaderboardFile << nicknames[count - 1] << DELIMITER << scores[count - 1];
    leaderboardFile.close();

    delete[] filename;
//    delete[] scores;
//    deallocateMatrix(nicknames, MAX_NICKNAMES_SCORES_COUNT);
}