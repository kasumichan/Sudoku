//
// Created by 16000 on 2022/4/11.
//

#include "PuzzleMenu.h"

PuzzleMenu::PuzzleMenu(QWidget *parent) : QMenu(parent) {

    this->setTitle("谜题");
    this->addAction("简单", this, &PuzzleMenu::easyPuzzle);
    this->addAction("中等", this, &PuzzleMenu::mediumPuzzle);
    this->addAction("困难", this, &PuzzleMenu::hardPuzzle);
    this->addAction("专家", this, &PuzzleMenu::veryHardPuzzle);
    levelSelectWidget = new LevelSelectPane(PuzzleDegree::EASY);
    connect(levelSelectWidget->getOkBtn(), SIGNAL(sendCellData(vector<CellStruct>)), this,
            SLOT(receiveCellData(vector<CellStruct>)));
}

void PuzzleMenu::easyPuzzle() {
    levelSelectWidget->setWindowIcon(QIcon("Resources/icon/junior.png"));
    levelSelectWidget->reset(PuzzleDegree::EASY);
    levelSelectWidget->setWindowModality(Qt::ApplicationModal);
    levelSelectWidget->show();
}

void PuzzleMenu::mediumPuzzle() {
    levelSelectWidget->setWindowIcon(QIcon("Resources/icon/middle.png"));
    levelSelectWidget->reset(PuzzleDegree::MEDIUM);
    levelSelectWidget->setWindowModality(Qt::ApplicationModal);
    levelSelectWidget->show();

}

void PuzzleMenu::hardPuzzle() {
    levelSelectWidget->setWindowIcon(QIcon("Resources/icon/senior.png"));
    levelSelectWidget->reset(PuzzleDegree::HARD);
    levelSelectWidget->setWindowModality(Qt::ApplicationModal);
    levelSelectWidget->show();

}

void PuzzleMenu::veryHardPuzzle() {

    levelSelectWidget->setWindowIcon(QIcon("Resources/icon/expert.png"));
    levelSelectWidget->reset(PuzzleDegree::VERY_HARD);
    levelSelectWidget->setWindowModality(Qt::ApplicationModal);
    levelSelectWidget->show();

}

void PuzzleMenu::receiveCellData(vector<CellStruct> data) {
    levelSelectWidget->close();
    emit sendPuzzleData(std::move(data));
}
