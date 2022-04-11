//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_MYMENUBAR_H
#define SUDOKU_MYMENUBAR_H

#include <QMenuBar>
#include "LevelSelectWidget.h"
#include "../Puzzle/Puzzle.h"
#include "../CellData.h"
#include "PuzzleMenu.h"


class MyMenuBar : public QMenuBar {
Q_OBJECT
private:
    QMenu *file;
    PuzzleMenu *puzzle;

public:
    PuzzleMenu *getPuzzle() const;

public:
    explicit MyMenuBar(QWidget *parent = nullptr);


private slots:

    void newGame();

    void intro();



};


#endif //SUDOKU_MYMENUBAR_H
