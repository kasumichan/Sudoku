//
// Created by 16000 on 2022/4/7.
//

#include "Board.h"

Board::Board() {

    auto it = board.begin();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            block[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] = (*(it + i)).begin() + j;
            row[i][j] = (*(it + i)).begin() + j;
            column[i][j] = (*(it + j)).begin() + i;
        }
    }


//    block[0] = {(*(it + 0)).begin() + 0,
//                (*(it + 0)).begin() + 1,
//                (*(it + 0)).begin() + 2,
//                (*(it + 1)).begin() + 0,
//                (*(it + 1)).begin() + 1,
//                (*(it + 1)).begin() + 2,
//                (*(it + 2)).begin() + 0,
//                (*(it + 2)).begin() + 1,
//                (*(it + 2)).begin() + 2};
//
//    block[1] = {(*(it + 0)).begin() + 3,
//                (*(it + 0)).begin() + 4,
//                (*(it + 0)).begin() + 5,
//                (*(it + 1)).begin() + 3,
//                (*(it + 1)).begin() + 4,
//                (*(it + 1)).begin() + 5,
//                (*(it + 2)).begin() + 3,
//                (*(it + 2)).begin() + 4,
//                (*(it + 2)).begin() + 5};
//
//    block[2] = {(*(it + 0)).begin() + 6,
//                (*(it + 0)).begin() + 7,
//                (*(it + 0)).begin() + 8,
//                (*(it + 1)).begin() + 6,
//                (*(it + 1)).begin() + 7,
//                (*(it + 1)).begin() + 8,
//                (*(it + 2)).begin() + 6,
//                (*(it + 2)).begin() + 7,
//                (*(it + 2)).begin() + 8};
//
//    block[3] = {(*(it + 3)).begin() + 0,
//                (*(it + 3)).begin() + 1,
//                (*(it + 3)).begin() + 2,
//                (*(it + 4)).begin() + 0,
//                (*(it + 4)).begin() + 1,
//                (*(it + 4)).begin() + 2,
//                (*(it + 5)).begin() + 0,
//                (*(it + 5)).begin() + 1,
//                (*(it + 5)).begin() + 2};
//
//    block[4] = {(*(it + 3)).begin() + 3,
//                (*(it + 3)).begin() + 4,
//                (*(it + 3)).begin() + 5,
//                (*(it + 4)).begin() + 3,
//                (*(it + 4)).begin() + 4,
//                (*(it + 4)).begin() + 5,
//                (*(it + 5)).begin() + 3,
//                (*(it + 5)).begin() + 4,
//                (*(it + 5)).begin() + 5};
//
//    block[5] = {(*(it + 3)).begin() + 6,
//                (*(it + 3)).begin() + 7,
//                (*(it + 3)).begin() + 8,
//                (*(it + 4)).begin() + 6,
//                (*(it + 4)).begin() + 7,
//                (*(it + 4)).begin() + 8,
//                (*(it + 5)).begin() + 6,
//                (*(it + 5)).begin() + 7,
//                (*(it + 5)).begin() + 8};
//
//    block[6] = {(*(it + 6)).begin() + 0,
//                (*(it + 6)).begin() + 1,
//                (*(it + 6)).begin() + 2,
//                (*(it + 7)).begin() + 0,
//                (*(it + 7)).begin() + 1,
//                (*(it + 7)).begin() + 2,
//                (*(it + 8)).begin() + 0,
//                (*(it + 8)).begin() + 1,
//                (*(it + 8)).begin() + 2};
//
//    block[7] = {(*(it + 6)).begin() + 3,
//                (*(it + 6)).begin() + 4,
//                (*(it + 6)).begin() + 5,
//                (*(it + 7)).begin() + 3,
//                (*(it + 7)).begin() + 4,
//                (*(it + 7)).begin() + 5,
//                (*(it + 8)).begin() + 3,
//                (*(it + 8)).begin() + 4,
//                (*(it + 8)).begin() + 5};
//
//    block[8] = {(*(it + 6)).begin() + 6,
//                (*(it + 6)).begin() + 7,
//                (*(it + 6)).begin() + 8,
//                (*(it + 7)).begin() + 6,
//                (*(it + 7)).begin() + 7,
//                (*(it + 7)).begin() + 8,
//                (*(it + 8)).begin() + 6,
//                (*(it + 8)).begin() + 7,
//                (*(it + 8)).begin() + 8};



}
