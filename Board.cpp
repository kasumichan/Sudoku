//
// Created by 16000 on 2022/4/7.
//

#include "Board.h"
#include <iostream>


Board::Board(const vector<vector<int>> &determinedNumList) {
    for (const auto &determinedNum: determinedNumList) {
        int x = determinedNum[0];
        int y = determinedNum[1];
        int num = determinedNum[2];
        board[x][y].Set(x, y, x / 3 * 3 + y / 3, x % 3 * 3 + y % 3, true, num);
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j].IsSet()) {
                board[i][j].Set(i, j, i / 3 * 3 + j / 3, i % 3 * 3 + j % 3, false);
            }
        }
    }

}

void Board::Init() {

    auto it = board.begin();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            block[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3] = (*(it + i)).begin() + j;
            row[i][j] = (*(it + i)).begin() + j;
            column[i][j] = (*(it + j)).begin() + i;
        }
    }
}

void Board::Exclude() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j].IsDetermined()) {
                int x = board[i][j].getIdX();
                int y = board[i][j].getIdY();
                int block_id = board[i][j].getIdBlock();
                int block_loc = board[i][j].getIdBlockLoc();
                for (int k = 0; k < 9; ++k) {
                    if (board[k][y].IsDetermined()) {
                        board[i][j].ExcludeNum(board[k][y].getNum());
                    }
                }
                for (int k = 0; k < 9; ++k) {
                    if (board[x][k].IsDetermined()) {
                        board[i][j].ExcludeNum(board[x][k].getNum());
                    }
                }
                for (int k = 0; k < 9; ++k) {
                    if (board[block_id / 3 * 3 + k % 3][block_id % 3 * 3 + k / 3].IsDetermined()) {
                        board[i][j].ExcludeNum(board[block_id / 3 * 3 + k % 3][block_id % 3 * 3 + k / 3].getNum());
                    }
                }
            }
        }
    }
}

void Board::Print() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].IsDetermined()) {
                std::cout << i << "\t" << j << "\t" << board[i][j].getNum();
            } else {
                std::cout << i << "\t" << j;
                std::cout << "\t" << "Possible: ";
                for (int num: board[i][j].getPossibleNumList()) {
                    std::cout << "\t" << num;
                }
            }
            std::cout << std::endl;
        }
    }
}
