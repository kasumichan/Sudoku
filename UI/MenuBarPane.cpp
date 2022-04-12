//
// Created by 16000 on 2022/4/11.
//

#include "MenuBarPane.h"
#include <QMessageBox>
#include "iostream"

MenuBarPane::MenuBarPane(QWidget *parent) : QMenuBar(parent) {
    file = new QMenu(this);
    file->setTitle("开始");
    file->addAction("自定义游戏", this, &MenuBarPane::newGame);
    file->addAction("说明", this, &MenuBarPane::intro);


    puzzle = new PuzzleMenu(this);
    addMenu(file);
    addMenu(puzzle);

}

void MenuBarPane::newGame() {
    emit startNewGame();
}

void MenuBarPane::intro() {
    QMessageBox::information(this, "说明", "该软件可以按步骤给出数独求解方案。\n\n"
                                         "点击自定义游戏可以自己创建数独，双击小数字来选择对应数字，再次双击可取消。"
                                         "点击开始游戏即可开始，点击下一步即可给出一步的提示。\n\n"
                                         "点击谜题，软件自带了不同难度的数独。\n\n"
                                         "一些功能尚在学习中，因此可能无法求解一些较难的数独。");
}

PuzzleMenu *MenuBarPane::getPuzzle() const {
    return puzzle;
}


