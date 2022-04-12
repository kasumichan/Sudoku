//
// Created by 16000 on 2022/4/7.
//

#include "BoardData.h"


BoardData::BoardData(const vector<CellStruct> &decidedNumList) {
    totDecided = int(decidedNumList.size());
    for (const auto &decidedNum: decidedNumList) {
        int row = decidedNum.getRow();
        int col = decidedNum.getColumn();
        int num = decidedNum.getNum();
        board[row][col].set(row, col, rc2b(row, col), rc2k(row, col), true, num);
    }
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (!board[row][col].isDecided()) {
                board[row][col].set(row, col, rc2b(row, col), rc2k(row, col), false);
            }
        }
    }
    updatePsbNumList();
}


void BoardData::updatePsbNumList() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j].isDecided()) {
                int x = board[i][j].getRow();
                int y = board[i][j].getCol();
                int b = board[i][j].getBlkId();
                for (int k = 0; k < 9; ++k) {
                    if (board[k][y].isDecided()) {
                        board[i][j].rmvNum(board[k][y].getNum());
                    }
                }
                for (int k = 0; k < 9; ++k) {
                    if (board[x][k].isDecided()) {
                        board[i][j].rmvNum(board[x][k].getNum());
                    }
                }
                for (int k = 0; k < 9; ++k) {
                    if (board[bk2r(b, k)][bk2c(b, k)].isDecided()) {
                        board[i][j].rmvNum(board[bk2r(b, k)][bk2c(b, k)].getNum());
                    }
                }
            }
        }
    }
}

void BoardData::print() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].isDecided()) {
                std::cout << i << "\t" << j << "\t" << board[i][j].getNum();
            } else {
                std::cout << i << "\t" << j;
                std::cout << "\t" << "Possible: ";
                for (int num: board[i][j].getPsbNumList()) {
                    std::cout << "\t" << num;
                }
            }
            std::cout << std::endl;
        }
    }
}

vector<int> BoardData::findFullHouse() {
    // by row
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        int index = -1;
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].isDecided()) {
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
//            std::cout << "There is only " << all[0] << " left in this row\t";
//            std::cout << "Full House Found" << "\t" << "r" << row + 1 << "c" << index + 1 << ": " << all[0] << std::endl;
            return {i, index, all[0], 0};
        }
    }

    // by column
    for (int j = 0; j < 9; ++j) {
        int count = 0;
        int index = -1;
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 9; ++i) {
            if (board[i][j].isDecided()) {
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
//            std::cout << "There is only " << all[0] << " left in this column\t";
//            std::cout << "Full House Found" << "\t" << "r" << index + 1 << "c" << col + 1 << ": " << all[0] << std::endl;
            return {index, j, all[0], 1};
        }
    }

    //by block
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        int index = -1;
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; ++j) {
            int r = bk2r(i, j);
            int c = bk2c(i, j);
            if (board[r][c].isDecided()) {
                all.erase(std::remove(all.begin(), all.end(), board[r][c].getNum()), all.end());
            } else {
                count++;
                index = j;
            }
            if (count == 2) {
                break;
            }
        }
        if (count == 1 && index != -1) {
//            std::cout << "There is only " << all[0] << " left in this block\t";
//            std::cout << "Full House Found" << "\t" << "r" << row / 3 * 3 + index / 3 + 1 << "c"
//                      << row % 3 * 3 + index % 3 + 1 << ": " << all[0] << std::endl;
            return {bk2r(i, index), bk2c(i, index), all[0], 2};
        }
    }

    return {};
}

vector<int> BoardData::findHiddenSingle() {
    // by row
    for (int i = 0; i < 9; ++i) {
        for (int num = 1; num < 10; ++num) {
            int count = 0;
            int index = -1;
            for (int j = 0; j < 9; ++j) {
                if (board[i][j].isDecided() && board[i][j].getNum() == num) {
                    break;
                }
                if (!board[i][j].isDecided() && board[i][j].contain(num)) {
                    count++;
                    index = j;
                }
            }
            if (count == 1) {
//                std::cout << "In this row, " << num << " can only be placed here\t";
//                std::cout << "Hidden Single Found" << "\t" << "r" << row + 1 << "c" << index + 1 << ": " << num
//                          << std::endl;
                return {i, index, num, 0};
            }

        }
    }


    // by column
    for (int j = 0; j < 9; ++j) {
        for (int num = 1; num < 10; ++num) {
            int count = 0;
            int index = -1;
            for (int i = 0; i < 9; ++i) {
                if (board[i][j].isDecided() && board[i][j].getNum() == num) {
                    break;
                }
                if (!board[i][j].isDecided() && board[i][j].contain(num)) {
                    count++;
                    index = i;
                }
            }
            if (count == 1) {
//                std::cout << "In this column, " << num << " can only be placed here\t";
//                std::cout << "Hidden Single Found" << "\t" << "r" << index + 1 << "c" << col + 1 << ": " << num
//                          << std::endl;
                return {index, j, num, 1};
            }

        }
    }


    // by block
    for (int i = 0; i < 9; ++i) {
        for (int num = 1; num < 10; ++num) {
            int count = 0;
            int index = -1;
            for (int j = 0; j < 9; ++j) {
                int r = bk2r(i, j);
                int c = bk2c(i, j);
                if (board[r][c].isDecided() && board[r][c].getNum() == num) {
                    break;
                }
                if (!board[r][c].isDecided() && board[r][c].contain(num)) {
                    count++;
                    index = j;
                }
            }
            if (count == 1) {
//                std::cout << "In this block, " << num << " can only be placed here\t";
//                std::cout << "Hidden Single Found" << "\t" << "r" << row / 3 * 3 + index / 3 + 1 << "c"
//                          << row % 3 * 3 + index % 3 + 1 << ": " << num << std::endl;
                return {bk2r(i, index), bk2c(i, index), num, 2};
            }
        }
    }
    return {};
}

vector<int> BoardData::findNakedSingle() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j].isDecided() && board[i][j].getPsbNumList().size() == 1) {
//                std::cout << "In this cell, nothing but " << board[row][col].getPsbNumList()[0]
//                          << " can be placed here\t";
//                std::cout << "Naked Single Found" << "\t" << "r" << row + 1 << "c" << col + 1 << ": "
//                          << board[row][col].getPsbNumList()[0] << std::endl;
                return {i, j, board[i][j].getPsbNumList()[0]};
            }
        }
    }
    return {};
}

Message BoardData::run() {

    if (!isValid()) {
        return Message{CellStruct(), BoardStatus::INVALID, ""};
    }


    auto message = findSingles();
    if (message.boardStatus == BoardStatus::VALID) {
        return message;
    }
    if (message.boardStatus == BoardStatus::VAGUE) {
        message = findIntersections();
        if (message.boardStatus != BoardStatus::VAGUE) {
            return message;
        }
        return findXWing();
    }
    return Message{CellStruct(), BoardStatus::VAGUE, ""};
}

//void BoardData::run() {
//    while (totDecided != 81) {
//        auto res = findFullHouse();
//        if (!res.empty()) {
//            board[res[0]][res[1]].setDecidedNum(res[2]);
//            board[res[0]][res[1]].setDecided(true);
//            updatePsbNumList();
//            ++totDecided;
//            std::cout << "Full House Found" << "\t" << "r" << res[0] + 1 << "c" << res[1] + 1 << ":\t" << res[2]
//                      << std::endl;
//            continue;
//        }
//
//        res = findHiddenSingle();
//        if (!res.empty()) {
//            board[res[0]][res[1]].setDecidedNum(res[2]);
//            board[res[0]][res[1]].setDecided(true);
//            updatePsbNumList();
//            ++totDecided;
//            std::cout << "Hidden House Found" << "\t" << "r" << res[0] + 1 << "c" << res[1] + 1 << ":\t" << res[2]
//                      << std::endl;
//            continue;
//        }
//
//        res = findNakedSingle();
//        if (!res.empty()) {
//            board[res[0]][res[1]].setDecidedNum(res[2]);
//            board[res[0]][res[1]].setDecided(true);
//            ++totDecided;
//            updatePsbNumList();
//            std::cout << "Naked House Found" << "\t" << "r" << res[0] + 1 << "c" << res[1] + 1 << ":\t" << res[2]
//                      << std::endl;
//            continue;
//        }
//    }
//
//    for (int row = 0; row < 9; ++row) {
//        for (int col = 0; col < 9; ++col) {
//            std::cout << board[row][col].getNum() << "  ";
//        }
//        std::cout << std::endl;
//    }
//
//}

bool BoardData::isValid() {
    // by row
    for (int i = 0; i < 9; ++i) {
        int count = 0;
        std::set<int> totalNum = {};
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].isDecided()) {
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
            if (board[i][j].isDecided()) {
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
            if (board[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3].isDecided()) {
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

bool BoardData::idk() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j].isDecided() && board[i][j].getPsbNumList().size() == 1)
                return false;
        }
    }
    return true;
}

Message BoardData::findIntersections() {
    // Pointing
    for (int b = 0; b < 9; ++b) {
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int k = 0; k < 9; ++k) {
            int r = bk2r(b, k);
            int c = bk2c(b, k);
            if (board[r][c].isDecided()) {
                all.erase(std::remove(all.begin(), all.end(), board[r][c].getNum()), all.end());
            }
        }
        for (int num: all) {
            set<int> rowIndexSet = {};
            set<int> colIndexSet = {};
            for (int k = 0; k < 9; ++k) {
                int r = bk2r(b, k);
                int c = bk2c(b, k);
                if (!board[r][c].isDecided() && board[r][c].contain(num)) {
                    rowIndexSet.insert(r);
                    colIndexSet.insert(c);
                }
            }
            if (rowIndexSet.size() == 1) {
                int i = *rowIndexSet.begin();
                vector<CellStruct> vec = {};
                stringstream ss;
                for (int j = 0; j < 9; ++j) {
                    if (colIndexSet.find(j) != colIndexSet.end()) {
                        continue;
                    }
                    if (!board[i][j].isDecided() && board[i][j].contain(num)) {
                        vec.emplace_back(i, j, num);
                        ss << "在第" << i + 1 << "行中，数字" << num << "一定在第" << b + 1 << "宫，因此第" << i + 1 << "行第" << j + 1
                           << "列一定不能填" << num << endl;
                    }
                }
                if (!vec.empty()) {
                    return {{}, BoardStatus::INTERSECTION_FOUND, ss.str(), vec};
                }
            }
            if (colIndexSet.size() == 1) {
                int j = *colIndexSet.begin();
                vector<CellStruct> vec = {};
                stringstream ss;
                for (int i = 0; i < 9; ++i) {
                    if (rowIndexSet.find(i) != rowIndexSet.end()) {
                        continue;
                    }
                    if (!board[i][j].isDecided() && board[i][j].contain(num)) {
                        vec.emplace_back(i, j, num);
                        ss << "在第" << j + 1 << "列中，数字" << num << "一定在第" << b + 1 << "宫，因此第" << i + 1 << "行第" << j + 1
                           << "列一定不能填" << num << endl;
                        board[i][j].rmvNum(num);
                    }
                }
                if (!vec.empty()) {
                    return {{}, BoardStatus::INTERSECTION_FOUND, ss.str(), vec};
                }
            }
        }
    }

    // Claiming
    // by row
    for (int i = 0; i < 9; ++i) {
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; ++j) {
            if (board[i][j].isDecided()) {
                all.erase(std::remove(all.begin(), all.end(), board[i][j].getNum()), all.end());
            }
        }
        for (int num: all) {
            set<int> blockIndexSet = {};
            for (int j = 0; j < 9; ++j) {
                int b = rc2b(i, j);
                if (!board[i][j].isDecided() && board[i][j].contain(num)) {
                    blockIndexSet.insert(b);
                }
            }
            if (blockIndexSet.size() == 1) {
                int b = *blockIndexSet.begin();
                vector<CellStruct> vec = {};
                stringstream ss;
                for (int k = 0; k < 9; ++k) {
                    int r = bk2r(b, k);
                    int c = bk2c(b, k);
                    if (r == i) {
                        continue;
                    }
                    if (!board[r][c].isDecided() && board[r][c].contain(num)) {
                        vec.emplace_back(r, c, num);
                        ss << "在第" << b + 1 << "宫中，数字" << num << "一定在第" << i + 1 << "行，因此第" << r + 1 << "行第" << c + 1
                           << "列一定不能填" << num << endl;
                    }
                }
                if (!vec.empty()) {
                    return {{}, BoardStatus::INTERSECTION_FOUND, ss.str(), vec};
                }
            }
        }
    }

    // by col
    for (int j = 0; j < 9; ++j) {
        vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 9; ++i) {
            if (board[i][j].isDecided()) {
                all.erase(std::remove(all.begin(), all.end(), board[i][j].getNum()), all.end());
            }
        }
        for (int num: all) {
            set<int> blockIndexSet = {};
            for (int i = 0; i < 9; ++i) {
                int b = rc2b(i, j);
                if (!board[i][j].isDecided() && board[i][j].contain(num)) {
                    blockIndexSet.insert(b);
                }
            }
            if (blockIndexSet.size() == 1) {
                vector<CellStruct> vec = {};
                stringstream ss;
                int b = *blockIndexSet.begin();
                for (int k = 0; k < 9; ++k) {
                    int r = bk2r(b, k);
                    int c = bk2c(b, k);
                    if (c == j) {
                        continue;
                    }
                    if (!board[r][c].isDecided() && board[r][c].contain(num)) {
                        ss << "在第" << b + 1 << "宫中，数字" << num << "一定在第" << j + 1 << "列，因此第" << r + 1 << "行第" << c + 1
                           << "列一定不能填" << num << endl;
                        vec.emplace_back(r, c, num);
                    }
                }
                if (!vec.empty()) {
                    return {{}, BoardStatus::INTERSECTION_FOUND, ss.str(), vec};
                }
            }
        }
    }


    return {{}, BoardStatus::VAGUE, ""};
}

int BoardData::bk2r(int b, int k) {
    return b / 3 * 3 + k / 3;
}

int BoardData::bk2c(int b, int k) {
    return b % 3 * 3 + k % 3;
}

int BoardData::rc2b(int r, int c) {
    return r / 3 * 3 + c / 3;
}

int BoardData::rc2k(int r, int c) {
    return r % 3 * 3 + c % 3;
}

Message BoardData::findSingles() {

    std::stringstream ss;

    auto sol = findFullHouse();
    if (!sol.empty()) {
        board[sol[0]][sol[1]].setNum(sol[2]);
        board[sol[0]][sol[1]].setDecided(true);
        updatePsbNumList();
        ++totDecided;
        ss.str("");
        if (sol[3] == 0) {
            ss << "在该行，只有" << sol[2] << "剩下" << "\t";
        } else if (sol[3] == 1) {
            ss << "在该列，只有" << sol[2] << "剩下" << "\t";
        } else {
            ss << "在该宫，只有" << sol[2] << "剩下" << "\t";
        }
//        ss << "Full House Found" << "\t";
        ss << "r" << sol[0] + 1 << "c" << sol[1] + 1 << ":\t" << sol[2]
           << std::endl;
        return Message{{sol[0], sol[1], sol[2]}, BoardStatus::VALID, ss.str()};
    }

    sol = findHiddenSingle();
    if (!sol.empty()) {
        board[sol[0]][sol[1]].setNum(sol[2]);
        board[sol[0]][sol[1]].setDecided(true);
        updatePsbNumList();
        ++totDecided;
        ss.str("");

        if (sol[3] == 0) {
            ss << "在该行，只有该处能填" << sol[2] << "\t";
        } else if (sol[3] == 1) {
            ss << "在该列，只有该处能填" << sol[2] << "\t";
        } else {
            ss << "在该宫，只有该处能填" << sol[2] << "\t";
        }
//        ss << "Hidden House Found" << "\t";
        ss << "r" << sol[0] + 1 << "c" << sol[1] + 1 << ":\t" << sol[2]
           << std::endl;
        return Message{{sol[0], sol[1], sol[2]}, BoardStatus::VALID, ss.str()};
    }

    sol = findNakedSingle();
    if (!sol.empty()) {
        board[sol[0]][sol[1]].setNum(sol[2]);
        board[sol[0]][sol[1]].setDecided(true);
        ++totDecided;
        updatePsbNumList();
        ss.str("");
        ss << "在该单元格只能填" << sol[2] << "\t";
//        ss << "Naked House Found" << "\t";
        ss << "r" << sol[0] + 1 << "c" << sol[1] + 1 << ":\t" << sol[2] << std::endl;
        return Message{{sol[0], sol[1], sol[2]}, BoardStatus::VALID, ss.str()};
    }
    return Message{CellStruct(), BoardStatus::VAGUE, ""};
}

vector<vector<CellData>> &BoardData::getBoard() {
    return board;
}

Message BoardData::findXWing() {

    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 9; ++j) {
            for (int m = 0; m < 8; ++m) {
                for (int n = m + 1; n < 9; ++n) {
                    if (board[i][m].isDecided() || board[i][n].isDecided() || board[j][m].isDecided() ||
                        board[j][n].isDecided()) {
                        continue;
                    }
                    vector<int> commonNum = {};
                    for (int num = 0; num < 9; ++num) {
                        if (board[i][m].contain(num) && board[i][n].contain(num) && board[j][m].contain(num) &&
                            board[j][n].contain(num)) {
                            commonNum.push_back(num);
                        }
                    }
                    for (auto num: commonNum) {
                        bool rowFlag = true;
                        for (int k = 0; k < 9; ++k) {
                            if (k == m || k == n) {
                                continue;
                            }
                            if ((!board[i][k].isDecided() && board[i][k].contain(num)) ||
                                (!board[j][k].isDecided() && board[j][k].contain(num))) {
                                rowFlag = false;
                                break;
                            }
                        }
                        // 该数字在该两行只存在四个交叉点
                        if (rowFlag) {
                            // 有没有排除该两列的其他点
                            bool flag = false;
                            for (int k = 0; k < 9; ++k) {
                                if (k == i || k == j) {
                                    continue;
                                }
                                if ((!board[k][m].isDecided() && board[k][m].contain(num)) ||
                                    (!board[k][n].isDecided() && board[k][n].contain(num))) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag) {
                                stringstream ss;
                                ss << "在第" << m + 1 << "列和第" << n + 1 << "列，除了第" << i + 1 << "行和第" << j + 1
                                   << "行，其他行都不可能填" << num << endl;
                                return {{}, BoardStatus::XWING_ROW_FOUND, ss.str(),
                                        {{i, m, num}, {i, n, num}, {j, m, num}, {j, n, num}}};
                            }
                        }
                        bool colFlag = true;
                        for (int k = 0; k < 9; ++k) {
                            if (k == i || k == j) {
                                continue;
                            }
                            if ((!board[k][m].isDecided() && board[k][m].contain(num)) ||
                                (!board[k][n].isDecided() && board[k][n].contain(num))) {
                                colFlag = false;
                                break;
                            }
                        }
                        // 该数字在该两列只存在四个交叉点
                        if (colFlag) {
                            // 有没有排除该两行的其他点
                            bool flag = false;
                            for (int k = 0; k < 9; ++k) {
                                if (k == m || k == n) {
                                    continue;
                                }
                                if ((!board[i][k].isDecided() && board[i][k].contain(num)) ||
                                    (!board[j][k].isDecided() && board[j][k].contain(num))) {
                                    flag = true;
                                    break;
                                }
                            }
                            if (flag) {
                                stringstream ss;
                                ss << "在第" << i + 1 << "行和第" << j + 1 << "行，除了第" << m + 1 << "列和第" << n + 1
                                   << "列，其他列都不可能填" << num << endl;
                                return {{}, BoardStatus::XWING_COL_FOUND, ss.str(),
                                        {{i, m, num}, {i, n, num}, {j, m, num}, {j, n, num}}};
                            }
                        }
                    }
                }
            }
        }
    }
    return {{}, BoardStatus::VAGUE, ""};
}

