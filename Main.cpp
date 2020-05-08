#include "BoardClass.h"

using namespace std;

int main()
{
    int width, queensCount;
    cout << "Enter square board width(height):" << endl;
    cin >> width;
    cout << "Enter queens to place on board count:" << endl;
    cin >> queensCount;
    Board* board = new Board(width, queensCount);
    char** solution;
    solution = board->TrySetQueen();
    if (solution != nullptr) {
        board->DrawBoard();
    }
    else {
        cout << "Algorithm can not find any solution" << endl;
    }
    delete solution;
    system("pause");
}

