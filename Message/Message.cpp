//
// Created by 16000 on 2022/4/10.
//

#include "Message.h"

#include <utility>


Message::Message(const CellStruct &cellData, BoardStatus boardStatus, string solution,
                 const vector<CellStruct> &excludeData) :
        cellData(cellData), boardStatus(boardStatus), solution(std::move(solution)), excludeData(excludeData) {

}
