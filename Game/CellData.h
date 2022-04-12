//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_CELLDATA_H
#define SUDOKU_CELLDATA_H

#include <vector>
#include <algorithm>

using std::vector;


class CellData {
private:
    int row;
    int col;
    int blkId;
    int blkLoc;
    bool decided;
    int num;
    vector<int> psbNumList;

public:
    CellData();

public:
    void set(int row, int col, int blkId, int blkLoc, bool decided, int num = 0);

    bool isDecided() const;

    void rmvNum(int num);

    int getRow() const;

    int getCol() const;

    int getBlkId() const;

    int getBlkLoc() const;

    const vector<int> &getPsbNumList() const;

    int getNum() const;

    void setDecided(bool decided);

    void setNum(int num);

    void setPsbList(const vector<int> &psbNumList);

    bool contain(int num);


};


#endif //SUDOKU_CELLDATA_H
