//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_PUZZLEMENU_H
#define SUDOKU_PUZZLEMENU_H

#include <QMenu>
#include "../Message/CellStruct.h"
#include "../UI/LevelSelectPane.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class PuzzleMenu : public QMenu {
Q_OBJECT
private:

    LevelSelectPane *levelSelectWidget;

public:
    explicit PuzzleMenu(QWidget *parent = nullptr);

private slots:


    void easyPuzzle();

    void mediumPuzzle();

    void hardPuzzle();

    void veryHardPuzzle();

    void receiveCellData(vector<CellStruct> data);

signals:

    void sendPuzzleData(vector<CellStruct> data);
};


#endif //SUDOKU_PUZZLEMENU_H
