//
// Created by 16000 on 2022/4/7.
//

#include "CellData.h"


CellData::CellData() : row(-1), col(-1), num(-1), blkId(-1), blkLoc(-1), decided(false) {
}

void CellData::set(int row, int col, int blkId, int blkLoc, bool decided, int num) {
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


bool CellData::isDecided() const {
    return decided;
}

int CellData::getRow() const {
    return row;
}

int CellData::getCol() const {
    return col;
}

int CellData::getBlkId() const {
    return blkId;
}

int CellData::getBlkLoc() const {
    return blkLoc;
}

void CellData::rmvNum(int num) {
    psbNumList.erase(std::remove(psbNumList.begin(), psbNumList.end(), num), psbNumList.end());
}

int CellData::getNum() const {
    return num;
}

const vector<int> &CellData::getPsbNumList() const {
    return psbNumList;
}

void CellData::setDecided(bool decided) {
    CellData::decided = decided;
}

void CellData::setNum(int num) {
    CellData::num = num;
}

void CellData::setPsbList(const vector<int> &psbNumList) {
    CellData::psbNumList = psbNumList;
}
