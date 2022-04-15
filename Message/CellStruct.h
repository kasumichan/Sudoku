
//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_CELLSTRUCT_H
#define SUDOKU_CELLSTRUCT_H


class CellStruct {
private:
    int row;
    int column;
    int num;
public:
    int getRow() const;

    CellStruct();

    int getColumn() const;

    int getNum() const;

    CellStruct(int row, int column, int num);

    void setNum(int num);
};


#endif //SUDOKU_CELLSTRUCT_H
