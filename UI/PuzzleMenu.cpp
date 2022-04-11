//
// Created by 16000 on 2022/4/11.
//

#include "PuzzleMenu.h"

PuzzleMenu::PuzzleMenu(QWidget *parent) : QMenu(parent) {

    this->setTitle("谜题");
    this->addAction("简单", this, &PuzzleMenu::easyPuzzle);
    this->addAction("中等", this, &PuzzleMenu::mediumPuzzle);
    this->addAction("困难", this, &PuzzleMenu::hardPuzzle);
    this->addAction("极困难", this, &PuzzleMenu::veryHardPuzzle);
    levelSelectWidget = new LevelSelectWidget("简单");
    connect(levelSelectWidget->getOkBtn(), SIGNAL(sendCellData(vector<CellData>)), this,
            SLOT(receiveCellData(vector<CellData>)));
}

void PuzzleMenu::easyPuzzle() {
    levelSelectWidget->reset("简单");
    levelSelectWidget->show();
}

void PuzzleMenu::mediumPuzzle() {
    levelSelectWidget->reset("中等");
    levelSelectWidget->show();
}

void PuzzleMenu::hardPuzzle() {
    levelSelectWidget->reset("困难");
    levelSelectWidget->show();

}

void PuzzleMenu::veryHardPuzzle() {
    levelSelectWidget->reset("极困难");
    levelSelectWidget->show();

}

void PuzzleMenu::receiveCellData(vector<CellData> data) {
    levelSelectWidget->close();
    emit sendPuzzleData(std::move(data));
}
