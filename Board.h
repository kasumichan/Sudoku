//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include "Cell.h"

class Board {
private:
    vector<vector<Cell>> board = vector<vector<Cell>>(9, vector<Cell>(9));

    vector<vector<vector<Cell>::iterator>> block = vector<vector<vector<Cell>::iterator>>
            (9, vector<vector<Cell>::iterator>(9));

    vector<vector<vector<Cell>::iterator>> column = vector<vector<vector<Cell>::iterator>>
            (9, vector<vector<Cell>::iterator>(9));

    vector<vector<vector<Cell>::iterator>> row = vector<vector<vector<Cell>::iterator>>
            (9, vector<vector<Cell>::iterator>(9));


    void Init();
public:
    explicit Board(const vector<vector<int>> &determinedNumList);

    void Exclude();

    void Print();

};


#endif //SUDOKU_BOARD_H
