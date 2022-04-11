//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include "Cell.h"
#include "../Message/Message.h"
#include <set>

class Board {
private:

    int totDecided;

    vector<vector<Cell>> board = vector<vector<Cell>>(9, vector<Cell>(9));

    void updatePsbNumList();


public:
    explicit Board(const vector<CellData> &decidedNumList);


    vector<int> findFullHouse();

    vector<int> findHiddenSingle();

    vector<int> findNakedSingle();

    Message run();

    bool idk();

    bool isValid();

    void print();



};


#endif //SUDOKU_BOARD_H
