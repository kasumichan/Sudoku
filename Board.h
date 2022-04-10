//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include "Cell.h"
#include "Message.h"
#include <set>

class Board {
private:

    int totalDetermined;
    vector<vector<Cell>> board = vector<vector<Cell>>(9, vector<Cell>(9));



public:
    explicit Board(const vector<vector<int>> &determinedNumList);

    void UpdatePossibleNumList();

    vector<int> FindFullHouse();

    vector<int> FindHiddenSingle();

    vector<int> FindNakedSingle();

    Message run();

    bool idk();

    bool IsValid();

    void Print();



};


#endif //SUDOKU_BOARD_H
