//
// Created by 16000 on 2022/4/10.
//

#include "CellData.h"

CellData::CellData(int row, int column, int num) : row(row), column(column), num(num) {}

int CellData::getRow() const {
    return row;
}

int CellData::getColumn() const {
    return column;
}

int CellData::getNum() const {
    return num;
}

CellData::CellData() : row(-1), column(-1), num(-1) {

}
