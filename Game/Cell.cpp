//
// Created by 16000 on 2022/4/7.
//

#include "Cell.h"


Cell::Cell() : row(-1), col(-1), num(-1), blkId(-1), blkLoc(-1), decided(false) {
}

void Cell::set(int row, int col, int blkId, int blkLoc, bool decided, int num) {
    this->row = row;
    this->col = col;
    this->blkId = blkId;
    this->blkLoc = blkLoc;
    this->decided = decided;
    if (this->decided) {
        this->num = num;
        this->psbNumList = {num};
    } else {
        this->psbNumList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    }
}


bool Cell::isDecided() const {
    return decided;
}

int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return col;
}

int Cell::getBlkId() const {
    return blkId;
}

int Cell::getBlkLoc() const {
    return blkLoc;
}

void Cell::rmvNum(int num) {
    psbNumList.erase(std::remove(psbNumList.begin(), psbNumList.end(), num), psbNumList.end());
}

int Cell::getNum() const {
    return num;
}

const vector<int> &Cell::getPsbNumList() const {
    return psbNumList;
}

void Cell::setDecided(bool decided) {
    Cell::decided = decided;
}

void Cell::setNum(int num) {
    Cell::num = num;
}

void Cell::setPsbList(const vector<int> &psbNumList) {
    Cell::psbNumList = psbNumList;
}
