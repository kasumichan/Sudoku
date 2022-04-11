//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_MESSAGE_H
#define SUDOKU_MESSAGE_H

#include <vector>
#include <string>
#include "CellData.h"
#include "BoardStatus.h"

using std::vector;
using std::string;

class Message {
public:
    CellData cellData;
    BoardStatus boardStatus;
    string solution;

    Message(const CellData &cellData, BoardStatus boardStatus, string solution);

};


#endif //SUDOKU_MESSAGE_H
