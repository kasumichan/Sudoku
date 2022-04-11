//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_CELLDATA_H
#define SUDOKU_CELLDATA_H


class CellData {
private:
    int row;
    int column;
    int num;
public:
    int getRow() const;

    CellData();

    int getColumn() const;

    int getNum() const;

    CellData(int row, int column, int num);
};


#endif //SUDOKU_CELLDATA_H
