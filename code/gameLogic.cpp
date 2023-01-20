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

void shiftColumn(unsigned **board, size_t dim, size_t colIdx, char command, unsigned &score, bool &changed) {
    if (board == nullptr || colIdx >= dim || (command != MOVE_UP && command != MOVE_DOWN)) {
        return;
    }
    size_t start = command == MOVE_UP ? 0 : dim - 1;
    int direction = command == MOVE_UP ? 1 : -1;
    int emptyTiles = 0;
    int lastUnmergedIdx = (int) start;

    for (size_t row = 1; row < dim; ++row) {
        size_t currIdx = start + direction * row;

        if (board[currIdx - direction][colIdx] == 0) {
            ++emptyTiles;
        }
        unsigned &current = board[currIdx][colIdx];
        if (current == 0) {
            continue;
        }

        if (lastUnmergedIdx == -1 || current != board[lastUnmergedIdx][colIdx]) {
            lastUnmergedIdx = (int) currIdx;
        } else if (current == board[lastUnmergedIdx][colIdx]) {
            score += mergeTiles(current, board[lastUnmergedIdx][colIdx]);
            lastUnmergedIdx = -1;
            changed = true;
        }

        if (board[currIdx][colIdx] != 0 && emptyTiles > 0) {
            lastUnmergedIdx = (int) currIdx - direction * emptyTiles;
            swap(current, board[lastUnmergedIdx][colIdx]);
            --emptyTiles;
            changed = true;
        }
    }
}

void shiftRow(unsigned **board, size_t dim, size_t rowIdx, char command, unsigned &score, bool &changed) {
    if (board == nullptr || rowIdx >= dim || (command != MOVE_LEFT && command != MOVE_RIGHT)) {
        return;
    }
    size_t start = command == MOVE_LEFT ? 0 : dim - 1;
    int direction = command == MOVE_LEFT ? 1 : -1;
    int emptyTiles = 0;
    int lastUnmergedIdx = (int) start;

    for (size_t col = 1; col < dim; ++col) {
        size_t currIdx = start + direction * col;
        if (board[rowIdx][currIdx - direction] == 0) {
            ++emptyTiles;
        }
        unsigned &current = board[rowIdx][currIdx];
        if (current == 0) {
            continue;
        }

        if (lastUnmergedIdx == -1 || current != board[rowIdx][lastUnmergedIdx]) {
            lastUnmergedIdx = (int) currIdx;
        } else if (current == board[rowIdx][lastUnmergedIdx]) {
            score += mergeTiles(current, board[rowIdx][lastUnmergedIdx]);
            lastUnmergedIdx = -1;
            changed = true;
        }

        if (current != 0 && emptyTiles > 0) {
            lastUnmergedIdx = (int) currIdx - direction * emptyTiles;
            swap(current, board[rowIdx][lastUnmergedIdx]);
            --emptyTiles;
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
    unsigned *emptyTiles = getEmptyTiles((const unsigned **) board, dim, emptyCount);
    size_t *coords = idxToCoords(emptyTiles[randomIdx(emptyCount)]);
    board[coords[0]][coords[1]] = randomTile();
    delete[] emptyTiles;
    delete[] coords;
    if (emptyCount == 1) {
        finished = !availableMoves((const unsigned **) board, dim);
    }
}

void moveBoard(unsigned **board, size_t dim, char command, unsigned &score, bool &finished) {
    bool changed = false;
    if (command == MOVE_UP || command == MOVE_DOWN) {
        for (size_t colIdx = 0; colIdx < dim; ++colIdx) {
            shiftColumn(board, dim, colIdx, command, score, changed);
        }
    } else if (command == MOVE_LEFT || command == MOVE_RIGHT) {
        for (size_t rowIdx = 0; rowIdx < dim; ++rowIdx) {
            shiftRow(board, dim, rowIdx, command, score, changed);
        }
    }
    if (changed) {
        addRandomTile(board, dim, finished);
    }
}