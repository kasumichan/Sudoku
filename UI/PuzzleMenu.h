//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_PUZZLEMENU_H
#define SUDOKU_PUZZLEMENU_H

#include <QMenu>
#include "../CellData.h"
#include "LevelSelectWidget.h"
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class PuzzleMenu : public QMenu {
Q_OBJECT
private:

    LevelSelectWidget *levelSelectWidget;

public:
    explicit PuzzleMenu(QWidget *parent = nullptr);

private slots:


    void easyPuzzle();

    void mediumPuzzle();

    void hardPuzzle();

    void veryHardPuzzle();

    void receiveCellData(vector<CellData> data);

signals:

    void sendPuzzleData(vector<CellData> data);
};


#endif //SUDOKU_PUZZLEMENU_H
