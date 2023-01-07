#include <iostream>

const char MOVE_UP = 'w';
const char MOVE_DOWN = 's';
const char MOVE_LEFT = 'a';
const char MOVE_RIGHT = 'd';

size_t merge(unsigned &x, unsigned &y) {
    y += x;
    x = 0;
    return y;
}

void swap(unsigned &x, unsigned &y) {
    unsigned temp = x;
    x = y;
    y = temp;
}

void shiftColumn(unsigned **&board, size_t dim, size_t colIdx, char cmd, unsigned &score) {
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
            score += merge(board[currIdx][colIdx], board[lastNonZeroIdx][colIdx]);
            lastNonZeroIdx = -1;
        }

        if (board[currIdx][colIdx] != 0 && emptySquares > 0) {
            swap(board[currIdx][colIdx], board[currIdx - direction * emptySquares][colIdx]);
            --emptySquares;
        }
    }
}

void shiftRow(unsigned **&board, size_t dim, size_t rowIdx, char cmd, unsigned &score) {
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
            score += merge(board[rowIdx][currIdx], board[rowIdx][lastNonZeroIdx]);
            lastNonZeroIdx = -1;
        }

        if (board[rowIdx][currIdx] != 0 && emptySquares > 0) {
            swap(board[rowIdx][currIdx], board[rowIdx][currIdx - direction * emptySquares]);
            --emptySquares;
        }
    }
}

size_t randomIdx(size_t count) {
    return rand() % count;
}

unsigned randomValue() {
    return 2 * (1 + rand() % 2);
}

size_t coordsToIdx(size_t row, size_t col) {
    return row * 10 + col;
}

size_t *idxToCoords(size_t idx) {
    auto *coords = new size_t[2];
    coords[1] = idx % 10;
    coords[0] = (idx / 10);
    return coords;
}

unsigned *getEmptySquares(unsigned **board, size_t dim, size_t &count) {
    auto *emptySquares = new unsigned[dim * dim];
    count = 0;
    for (size_t row = 0; row < dim; ++row) {
        for (size_t col = 0; col < dim; ++col) {
            if (board[row][col] == 0) {
                emptySquares[count++] = coordsToIdx(row, col);
            }
        }
    }
    return emptySquares;
}

void addRandomValue(unsigned **&board, size_t dim) {
    size_t emptyCount;
    unsigned *emptySquares = getEmptySquares(board, dim, emptyCount);
    size_t *coords = idxToCoords(emptySquares[randomIdx(emptyCount)]);
    board[coords[0]][coords[1]] = randomValue();
    delete[] emptySquares;
    delete[] coords;
}

void moveBoard(unsigned **&board, size_t dim, char cmd, unsigned &score) {
    if (cmd == MOVE_UP || cmd == MOVE_DOWN) {
        for (size_t colIdx = 0; colIdx < dim; ++colIdx) {
            shiftColumn(board, dim, colIdx, cmd, score);
        }
    } else if (cmd == MOVE_LEFT || cmd == MOVE_RIGHT) {
        for (size_t rowIdx = 0; rowIdx < dim; ++rowIdx) {
            shiftRow(board, dim, rowIdx, cmd, score);
        }
    }
    addRandomValue(board, dim);
}

unsigned **createBoard(size_t dim) {
    auto **board = new unsigned *[dim];
    for (size_t row = 0; row < dim; ++row) {
        board[row] = new unsigned[dim];
    }
    addRandomValue(board, dim);
    addRandomValue(board, dim);
    return board;
}

void deleteBoard(unsigned **board, size_t dim) {
    for (size_t row = 0; row < dim; ++row) {
        delete[] board[row];
    }
    delete[] board;
}

int main() {
    return 0;
}