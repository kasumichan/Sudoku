//
// Created by 16000 on 2022/4/7.
//

#include "Cell.h"


Cell::Cell() {
    this->isSet = false;
}

void Cell::Set(int id_x, int id_y, int id_block, int id_block_loc, bool isDetermined, int number) {
    this->isSet = true;
    this->id_x = id_x;
    this->id_y = id_y;
    this->id_block = id_block;
    this->id_block_loc = id_block_loc;
    this->isDetermined = isDetermined;
    if (this->isDetermined) {
        this->num = number;
        this->possibleNumList = {number};
    } else {
        this->possibleNumList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    }
}

bool Cell::IsSet() const {
    return isSet;
}

bool Cell::IsDetermined() const {
    return isDetermined;
}

int Cell::getIdX() const {
    return id_x;
}

int Cell::getIdY() const {
    return id_y;
}

int Cell::getIdBlock() const {
    return id_block;
}

int Cell::getIdBlockLoc() const {
    return id_block_loc;
}

void Cell::ExcludeNum(int num) {
    possibleNumList.erase(std::remove(possibleNumList.begin(), possibleNumList.end(), num), possibleNumList.end());
}

int Cell::getNum() const {
    return num;
}

const vector<int> &Cell::getPossibleNumList() const {
    return possibleNumList;
}
