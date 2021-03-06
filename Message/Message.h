//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_MESSAGE_H
#define SUDOKU_MESSAGE_H

#include <vector>
#include <string>
#include "CellStruct.h"
#include "BoardStatus.h"

using std::vector;
using std::string;

class Message {
public:
    CellStruct cellData;
    BoardStatus boardStatus;
    string solution;
    vector<CellStruct> excludeData;

    Message(const CellStruct &cellData, BoardStatus boardStatus, string solution, const vector<CellStruct>& excludeData ={});

};


#endif //SUDOKU_MESSAGE_H
