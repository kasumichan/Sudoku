//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_MENUBARPANE_H
#define SUDOKU_MENUBARPANE_H

#include <QMenuBar>
#include "LevelSelectPane.h"
#include "../Puzzle/Puzzle.h"
#include "../Message/CellData.h"
#include "../Controller/PuzzleMenu.h"


class MenuBarPane : public QMenuBar {
Q_OBJECT
private:
    QMenu *file;
    PuzzleMenu *puzzle;

public:
    PuzzleMenu *getPuzzle() const;

public:
    explicit MenuBarPane(QWidget *parent = nullptr);


private slots:

    void newGame();

    void intro();



};


#endif //SUDOKU_MENUBARPANE_H
