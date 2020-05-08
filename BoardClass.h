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
        //make all cells zeros;
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
    //if it is impossible to place Queens on table 
    if (queensNeeded > width) {
        // - end before the mess starts;
        return nullptr;
    }
    //if last needed funtion call called recursion once more. 
    //("if" statement with ID = LastCall. You'll understand later)
    if (queensCount >= queensNeeded) {
        // -soltution found
        return cells;
    }
    //the mess starts
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            //if current cell is free (0 == false)
            if (!cells[i][j]) {
                //place Queen and mark cells which are no more safe to stay on
                PlaceQueen(i, j);
                //Trying to place another Queen. ("if" with ID = QueenRemoverIf)
                if (TrySetQueen() == nullptr) {
                    //if free position not found - remove placed earlier Queen
                    RemoveQueen(i, j);
                }
                //if program execution reached this place, it means that "if" with ID = LastCall returned not nullptr
                else {
                    //returning cells array. 
                    //From this place from stack finally shrinks.
                    return cells;
                }
            }
        }
    }
    //if tried all possible cells and not found a free one, return nullptr.
    //"if" with ID = QueenRemoverIf will accept this result and remove Queen which caused this situation.
    return nullptr;
}

void Board::PlaceQueen(const int row, const int col) {
    //nothing special.
    int foo;
    for (int i = 0; i < width; i++) {
        ++cells[row][i];
        ++cells[i][col];
        //you do not need to understand thus
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
    //nothing special.
    int foo;
    for (int i = 0; i < width; i++) {
        --cells[row][i];
        --cells[i][col];
        //you do not need to understand this
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
    //simple std::cout
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            if (cells[i][j] == 0) {
                cout<< ". ";
            }
            else if (cells[i][j] > 0) {
                cout<< "x ";
            }
            else if (cells[i][j] == -1) {
                cout<< "O ";
            }
        }
        cout<< endl;
    }
}
