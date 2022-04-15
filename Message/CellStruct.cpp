//
// Created by 16000 on 2022/4/10.
//

#include "CellStruct.h"

CellStruct::CellStruct(int row, int column, int num) : row(row), column(column), num(num) {}

int CellStruct::getRow() const {
    return row;
}

int CellStruct::getColumn() const {
    return column;
}

int CellStruct::getNum() const {
    return num;
}

CellStruct::CellStruct() : row(-1), column(-1), num(-1) {

}

void CellStruct::setNum(int num) {
    CellStruct::num = num;
}
