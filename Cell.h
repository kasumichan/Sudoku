//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_CELL_H
#define SUDOKU_CELL_H

#include <vector>
#include <algorithm>

using std::vector;


class Cell {
private:
    bool isSet;
    int id_x;
    int id_y;
    int id_block;
    int id_block_loc;
public:
    void setIsDetermined(bool isDetermined);

    void setNum(int num);

    void setPossibleNumList(const vector<int> &possibleNumList);

private:
    bool isDetermined;
    int num;
    vector<int> possibleNumList;

public:
    Cell();

    void Set(int id_x, int id_y, int id_block, int id_block_loc, bool isDetermined, int number = 0);

    bool IsSet() const;

    bool IsDetermined() const;

    void ExcludeNum(int num);

public:
    int getIdX() const;

    int getIdY() const;

    int getIdBlock() const;

    int getIdBlockLoc() const;

    const vector<int> &getPossibleNumList() const;

    int getNum() const;


};


#endif //SUDOKU_CELL_H
