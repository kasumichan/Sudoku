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
    int row;
    int col;
    int blkId;
    int blkLoc;
    bool decided;
    int num;
    vector<int> psbNumList;

public:
    Cell();

public:

    void set(int row, int col, int blkId, int blkLoc, bool decided, int num = 0);

    bool isDecided() const;

    void rmvNum(int num);

public:
    int getRow() const;

    int getCol() const;

    int getBlkId() const;

    int getBlkLoc() const;

    const vector<int> &getPsbNumList() const;

    int getNum() const;

    void setDecided(bool decided);

    void setNum(int num);

    void setPsbList(const vector<int> &psbNumList);


};


#endif //SUDOKU_CELL_H
