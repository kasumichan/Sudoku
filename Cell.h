//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H
#include <vector>
using std::vector;


class Cell {
private:
    bool isDetermined;
    int number;
    vector<int> possibleNumList;
public:
    Cell();
    explicit Cell(int num);
    void ExcludeNum(int num);
};


#endif //SUDOKU_CELL_H
