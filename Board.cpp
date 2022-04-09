//
// Created by 16000 on 2022/4/7.
//

#include "Board.h"
#include <iostream>


Board::Board(const vector<vector<int>> &determinedNumList) {
    totalDetermined = determinedNumList.size();
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

void Board::UpdatePossibleNumList() {
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
                    if (board[block_id / 3 * 3 + k / 3][block_id % 3 * 3 + k % 3].IsDetermined()) {
                        board[i][j].ExcludeNum(board[block_id / 3 * 3 + k / 3][block_id % 3 * 3 + k % 3].getNum());
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

vector<int> Board::FindFullHouse() {
    // by row
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        int index = -1;
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].IsDetermined()) {
                all.erase(std::remove(all.begin(), all.end(), board[i][j].getNum()), all.end());
            } else {
                count++;
                index = j;
            }
            if (count == 2) {
                break;
            }
        }
        if (count == 1 && index != -1) {
            std::cout << "There is only " << all[0] << " left in this row\t";
//            std::cout << "Full House Found" << "\t" << "r" << i + 1 << "c" << index + 1 << ": " << all[0] << std::endl;
            return {i, index, all[0]};
        }
    }

    // by column
    for (int j = 0; j < 9; ++j) {
        int count = 0;
        int index = -1;
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 9; ++i) {
            if (board[i][j].IsDetermined()) {
                all.erase(std::remove(all.begin(), all.end(), board[i][j].getNum()), all.end());
            } else {
                count++;
                index = i;
            }
            if (count == 2) {
                break;
            }
        }
        if (count == 1 && index != -1) {
            std::cout << "There is only " << all[0] << " left in this column\t";
//            std::cout << "Full House Found" << "\t" << "r" << index + 1 << "c" << j + 1 << ": " << all[0] << std::endl;
            return {index, j, all[0]};
        }
    }

    //by block
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        int index = -1;
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; ++j) {
            if (board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].IsDetermined()) {
                all.erase(std::remove(all.begin(), all.end(), board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].getNum()),
                          all.end());
            } else {
                count++;
                index = j;
            }
            if (count == 2) {
                break;
            }
        }
        if (count == 1 && index != -1) {
            std::cout << "There is only " << all[0] << " left in this block\t";
//            std::cout << "Full House Found" << "\t" << "r" << i / 3 * 3 + index / 3 + 1 << "c"
//                      << i % 3 * 3 + index % 3 + 1 << ": " << all[0] << std::endl;
            return {i / 3 * 3 + index / 3, i % 3 * 3 + index % 3, all[0]};
        }
    }

    return {};
}

vector<int> Board::FindHiddenSingle() {
    // by row
    for (int i = 0; i < 9; ++i) {
        for (int num = 0; num < 9; ++num) {
            int count = 0;
            int index = -1;
            for (int j = 0; j != 9; ++j) {
                if (board[i][j].IsDetermined() && board[i][j].getNum() == num) {
                    break;
                }
                if (!board[i][j].IsDetermined() &&
                    std::find(board[i][j].getPossibleNumList().begin(), board[i][j].getPossibleNumList().end(), num) !=
                    board[i][j].getPossibleNumList().end()) {
                    count++;
                    index = j;
                }
            }
            if (count == 1) {
                std::cout << "In this row, " << num << " can only be placed here\t";
//                std::cout << "Hidden Single Found" << "\t" << "r" << i + 1 << "c" << index + 1 << ": " << num
//                          << std::endl;
                return {i, index, num};
            }

        }
    }


    // by column
    for (int j = 0; j < 9; ++j) {
        for (int num = 0; num < 9; ++num) {
            int count = 0;
            int index = -1;
            for (int i = 0; i != 9; ++i) {
                if (board[i][j].IsDetermined() && board[i][j].getNum() == num) {
                    break;
                }
                if (!board[i][j].IsDetermined() &&
                    std::find(board[i][j].getPossibleNumList().begin(), board[i][j].getPossibleNumList().end(), num) !=
                    board[i][j].getPossibleNumList().end()) {
                    count++;
                    index = i;
                }
            }
            if (count == 1) {
                std::cout << "In this column, " << num << " can only be placed here\t";
//                std::cout << "Hidden Single Found" << "\t" << "r" << index + 1 << "c" << j + 1 << ": " << num
//                          << std::endl;
                return {index, j, num};
            }

        }
    }


    // by block
    for (int i = 0; i < 9; ++i) {
        for (int num = 0; num < 9; ++num) {
            int count = 0;
            int index = -1;
            for (int j = 0; j != 9; ++j) {
                if (board[i][j].IsDetermined() && board[i][j].getNum() == num) {
                    break;
                }
                if (!board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].IsDetermined() &&
                    std::find(board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].getPossibleNumList().begin(),
                              board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].getPossibleNumList().end(), num) !=
                    board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].getPossibleNumList().end()) {
                    count++;
                    index = j;
                }
            }
            if (count == 1) {
                std::cout << "In this block, " << num << " can only be placed here\t";
//                std::cout << "Hidden Single Found" << "\t" << "r" << i / 3 * 3 + index / 3 + 1 << "c"
//                          << i % 3 * 3 + index % 3 + 1 << ": " << num << std::endl;
                return {i / 3 * 3 + index / 3, i % 3 * 3 + index % 3, num};
            }
        }
    }
    return {};
}

vector<int> Board::FindNakedSingle() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j].IsDetermined() && board[i][j].getPossibleNumList().size() == 1) {
                std::cout << "In this cell, nothing but " << board[i][j].getPossibleNumList()[0] << " can be placed here\t";
//                std::cout << "Naked Single Found" << "\t" << "r" << i + 1 << "c" << j + 1 << ": "
//                          << board[i][j].getPossibleNumList()[0] << std::endl;
                return {i, j, board[i][j].getPossibleNumList()[0]};
            }
        }
    }
    return {};
}

void Board::run() {
    while (totalDetermined != 81) {
        auto res = FindFullHouse();
        if (!res.empty()) {
            board[res[0]][res[1]].setNum(res[2]);
            board[res[0]][res[1]].setIsDetermined(true);
            UpdatePossibleNumList();
            ++totalDetermined;
            std::cout << "Full House Found" << "\t" << "r" << res[0] + 1 << "c" << res[1] + 1 << ":\t" << res[2]
                      << std::endl;
            continue;
        }

        res = FindHiddenSingle();
        if (!res.empty()) {
            board[res[0]][res[1]].setNum(res[2]);
            board[res[0]][res[1]].setIsDetermined(true);
            UpdatePossibleNumList();
            ++totalDetermined;
            std::cout << "Hidden House Found" << "\t" << "r" << res[0] + 1 << "c" << res[1] + 1 << ":\t" << res[2]
                      << std::endl;
            continue;
        }

        res = FindNakedSingle();
        if (!res.empty()) {
            board[res[0]][res[1]].setNum(res[2]);
            board[res[0]][res[1]].setIsDetermined(true);
            ++totalDetermined;
            UpdatePossibleNumList();
            std::cout << "Naked House Found" << "\t" << "r" << res[0] + 1 << "c" << res[1] + 1 << ":\t" << res[2]
                      << std::endl;
            continue;
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << board[i][j].getNum() << "  ";
        }
        std::cout << std::endl;
    }

}

bool Board::IsValid() {
    // by row
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        std::set<int> totalNum = {};
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].IsDetermined()) {
                totalNum.insert(board[i][j].getNum());
                ++count;
            }
        }
        if (count != totalNum.size()) {
            return false;
        }
    }

    // by column
    for (int j = 0; j < 9; ++j) {
        int count = 0;
        std::set<int> totalNum = {};
        for (int i = 0; i < 9; ++i) {
            if (board[i][j].IsDetermined()) {
                totalNum.insert(board[i][j].getNum());
                ++count;
            }
        }
        if (count != totalNum.size()) {
            return false;
        }
    }

    // by block
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        std::set<int> totalNum;
        for (int j = 0; j < 9; ++j) {
            if (board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].IsDetermined()) {
                totalNum.insert(board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].getNum());
                ++count;
            }
        }
        if (count != totalNum.size()) {
            return false;
        }
    }
    return true;
}
