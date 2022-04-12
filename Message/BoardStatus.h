//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_BOARDSTATUS_H
#define SUDOKU_BOARDSTATUS_H


enum class BoardStatus {
    VALID,
    INVALID,
    VAGUE,
    INTERSECTION_FOUND,
    XWING_ROW_FOUND,
    XWING_COL_FOUND
};


#endif //SUDOKU_BOARDSTATUS_H
