#pragma once
#include <iostream>

using namespace std;

class Board {
private:
    int width, queensNeeded;
    char** cells;
    int queensCount;
public:
    Board(int width, int queensNeeded) : width(width), queensNeeded(queensNeeded) {
        InitCells();
    }
    ~Board() {
        for (int i = 0; i < width; i++) {
            delete[] cells[i];
        }
        delete[] cells;
    }

    void InitCells() {
        queensCount = 0;
        cells = new char* [width];
        for (int i = 0; i < width; i++) {
            cells[i] = new char[width];
            for (int j = 0; j < width; j++) {
                cells[i][j] = 0;
            }
        }
    }
    char** TrySetQueen();
    void PlaceQueen(int, int);
    void RemoveQueen(const int, const int);
    void DrawBoard();
};


char** Board::TrySetQueen() {
    if (queensNeeded > width) {
        return nullptr;
    }
    if (queensCount >= queensNeeded) {
        return cells;
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            if (!cells[i][j]) {
                PlaceQueen(i, j);
                if (TrySetQueen() == nullptr) {
                    RemoveQueen(i, j);
                }
                else {
                    return cells;
                }
            }
        }
    }
    return nullptr;
}

void Board::PlaceQueen(const int row, const int col) {
    int foo;
    for (int i = 0; i < width; i++) {
        ++cells[row][i];
        ++cells[i][col];
        foo = col - row + i;
        if (foo >= 0 && foo < width) {
            ++cells[i][foo];
        }
        foo = col + row - i;
        if (foo >= 0 && foo < width) {
            ++cells[i][foo];
        }
    }
    cells[row][col] = -1;
    ++queensCount;
}


void Board::RemoveQueen(const int row, const int col) {
    int foo;
    for (int i = 0; i < width; i++) {
        --cells[row][i];
        --cells[i][col];
        foo = col - row + i;
        if (foo >= 0 && foo < width) {
            --cells[i][foo];
        }
        foo = col + row - i;
        if (foo >= 0 && foo < width) {
            --cells[i][foo];
        }
    }
    cells[row][col] = 0;
    --queensCount;
}

void Board::DrawBoard() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            if (cells[i][j] == 0) {
                cout << ". ";
            }
            else if (cells[i][j] > 0) {
                cout << "x ";
            }
            else if (cells[i][j] == -1) {
                cout << "O ";
            }
        }
        cout << endl;
    }
}
