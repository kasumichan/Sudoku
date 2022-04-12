//
// Created by 16000 on 2022/4/7.
//

#ifndef SUDOKU_BOARDDATA_H
#define SUDOKU_BOARDDATA_H

#include "CellData.h"
#include "../Message/Message.h"
#include <set>
#include <sstream>
#include <iostream>
using std::set;
using std::cin;
using std::cout;
using std::endl;
using std::stringstream;

class BoardData {
private:

    int totDecided;

    vector<vector<CellData>> board = vector<vector<CellData>>(9, vector<CellData>(9));

    void updatePsbNumList();

    static int bk2r(int b, int k);

    static int bk2c(int b, int k);

    static int rc2b(int r, int c);

    static int rc2k(int r, int c);


public:
    explicit BoardData(const vector<CellStruct> &decidedNumList);


    vector<int> findFullHouse();

    vector<int> findHiddenSingle();

    vector<int> findNakedSingle();

    Message findSingles();

    Message findIntersections();

    Message findXWing();

    Message run();

    bool idk();

    bool isValid();

    vector<vector<CellData>> &getBoard();

    void print();



};


#endif //SUDOKU_BOARDDATA_H
