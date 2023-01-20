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
 * file with main game logic
 *
*/

#include "gameLogic.h"
#include "helper.h"

const char MOVE_UP = 'w';
const char MOVE_DOWN = 's';
const char MOVE_LEFT = 'a';
const char MOVE_RIGHT = 'd';

unsigned mergeTiles(unsigned &x, unsigned &y) {
    y += x;
    x = 0;
    return y;
}

void shiftColumn(unsigned **board, size_t dim, size_t colIdx, char cmd, unsigned &score, bool &changed) {
    if (board == nullptr || colIdx > dim || (cmd != MOVE_UP && cmd != MOVE_DOWN)) {
        return;
    }
    size_t start = cmd == MOVE_UP ? 0 : dim - 1;
    int direction = cmd == MOVE_UP ? 1 : -1;
    int emptySquares = 0;
    int lastNonZeroIdx = (int) start;

    for (size_t row = 1; row < dim; ++row) {
        size_t currIdx = start + direction * row;
        if (board[currIdx - direction][colIdx] == 0) {
            ++emptySquares;
        }
        if (board[currIdx][colIdx] == 0) {
            continue;
        }

        if (lastNonZeroIdx == -1 || board[currIdx][colIdx] != board[lastNonZeroIdx][colIdx]) {
            lastNonZeroIdx = (int) currIdx;
        } else if (board[currIdx][colIdx] == board[lastNonZeroIdx][colIdx]) {
            score += mergeTiles(board[currIdx][colIdx], board[lastNonZeroIdx][colIdx]);
            lastNonZeroIdx = -1;
            changed = true;
        }

        if (board[currIdx][colIdx] != 0 && emptySquares > 0) {
            lastNonZeroIdx = (int) currIdx - direction * emptySquares;
            swap(board[currIdx][colIdx], board[lastNonZeroIdx][colIdx]);
            --emptySquares;
            changed = true;
        }
    }
}

void shiftRow(unsigned **board, size_t dim, size_t rowIdx, char cmd, unsigned &score, bool &changed) {
    if (board == nullptr || rowIdx > dim || (cmd != MOVE_LEFT && cmd != MOVE_RIGHT)) {
        return;
    }
    size_t start = cmd == MOVE_LEFT ? 0 : dim - 1;
    int direction = cmd == MOVE_LEFT ? 1 : -1;
    int emptySquares = 0;
    int lastNonZeroIdx = (int) start;

    for (size_t col = 1; col < dim; ++col) {
        size_t currIdx = start + direction * col;
        if (board[rowIdx][currIdx - direction] == 0) {
            ++emptySquares;
        }
        if (board[rowIdx][currIdx] == 0) {
            continue;
        }

        if (lastNonZeroIdx == -1 || board[rowIdx][currIdx] != board[rowIdx][lastNonZeroIdx]) {
            lastNonZeroIdx = (int) currIdx;
        } else if (board[rowIdx][currIdx] == board[rowIdx][lastNonZeroIdx]) {
            score += mergeTiles(board[rowIdx][currIdx], board[rowIdx][lastNonZeroIdx]);
            lastNonZeroIdx = -1;
            changed = true;
        }

        if (board[rowIdx][currIdx] != 0 && emptySquares > 0) {
            lastNonZeroIdx = (int) currIdx - direction * emptySquares;
            swap(board[rowIdx][currIdx], board[rowIdx][lastNonZeroIdx]);
            --emptySquares;
            changed = true;
        }
    }
}

size_t randomIdx(size_t count) {
    return rand() % count;
}

unsigned randomTile() {
    return 2 * (1 + rand() % 2);
}

size_t coordsToIdx(size_t row, size_t col) {
    return row * 10 + col;
}

size_t *idxToCoords(size_t idx) {
    size_t *coords = new size_t[2];
    coords[1] = idx % 10;
    coords[0] = idx / 10;
    return coords;
}

unsigned *getEmptyTiles(const unsigned **board, size_t dim, size_t &count) {
    unsigned *emptyTiles = new unsigned[dim * dim];
    count = 0;
    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim; ++col) {
            if (board[row][col] == 0) {
                emptyTiles[count++] = coordsToIdx(row, col);
            }
        }
    }
    return emptyTiles;
}

bool availableMoves(const unsigned **board, size_t dim) {
    for (size_t row = 0; row < dim - 1; ++row) {
        for (size_t col = 0; col < dim - 1; ++col) {
            if (board[row][col] == board[row][col + 1]) {
                return true;
            }
            if (board[row][col] == board[row + 1][col]) {
                return true;
            }
        }
    }
    for (size_t row = 0; row < dim - 1; ++row) {
        if (board[row][dim - 1] == board[row + 1][dim - 1]) {
            return true;
        }
    }
    for (size_t col = 0; col < dim - 1; ++col) {
        if (board[dim - 1][col] == board[dim - 1][col + 1]) {
            return true;
        }
    }
    return false;
}

void addRandomTile(unsigned **board, size_t dim, bool &finished) {
    size_t emptyCount;
    unsigned *emptySquares = getEmptyTiles((const unsigned **) board, dim, emptyCount);
    size_t *coords = idxToCoords(emptySquares[randomIdx(emptyCount)]);
    board[coords[0]][coords[1]] = randomTile();
    delete[] emptySquares;
    delete[] coords;
    if (emptyCount == 1) {
        finished = !availableMoves((const unsigned **) board, dim);
    }
}

void moveBoard(unsigned **board, size_t dim, char cmd, unsigned &score, bool &finished) {
    bool changed = false;
    if (cmd == MOVE_UP || cmd == MOVE_DOWN) {
        for (size_t colIdx = 0; colIdx < dim; ++colIdx) {
            shiftColumn(board, dim, colIdx, cmd, score, changed);
        }
    } else if (cmd == MOVE_LEFT || cmd == MOVE_RIGHT) {
        for (size_t rowIdx = 0; rowIdx < dim; ++rowIdx) {
            shiftRow(board, dim, rowIdx, cmd, score, changed);
        }
    }
    if (changed) {
        addRandomTile(board, dim, finished);
    }
}