//
// Created by 16000 on 2022/4/7.
//

#include "Cell.h"

Cell::Cell() {
    this->isDetermined = false;
    this->number = 0;
    this->possibleNumList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}

Cell::Cell(int num) {
    this->isDetermined = true;
    this->number = num;
    this->possibleNumList = {num};
}
