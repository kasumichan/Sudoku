//
// Created by 16000 on 2022/4/11.
//

#include "LevelSelectPane.h"

#include <utility>
#include<iostream>

using namespace std;

LevelSelectPane::LevelSelectPane(PuzzleDegree degree, QWidget *parent) :
        QWidget(parent), page(0), level(0), rowCnt(4), colCnt(5), degree(degree) {
    levelBtn = vector<InfoBtn *>(rowCnt * colCnt);
    for (int i = 0; i < 20; ++i) {
        levelBtn[i] = new InfoBtn();
        levelBtn[i]->setText(QString::number(i + 1));
    }
    lastBtn = new QPushButton("上一页");
    nextBtn = new QPushButton("下一页");
    okBtn = new InfoBtn(PuzzleDegree::EASY);
    okBtn->setText("确定");
    initLayout();
    addListener();
}

void LevelSelectPane::initLayout() {
    setTitle();
    auto *layout = new QGridLayout;
    for (int i = 0; i < rowCnt; ++i) {
        for (int j = 0; j < colCnt; ++j) {
            layout->addWidget(levelBtn[i * colCnt + j], i, j, 1, 1);
        }
    }
    layout->addWidget(lastBtn, 4, 0, 1, 2);
    layout->addWidget(nextBtn, 4, 3, 1, 2);
    layout->addWidget(okBtn, 5, 0, 1, 5);

    LevelSelectPane::setLayout(layout);
}

void LevelSelectPane::nextClicked() {
    if (page < 4) {
        ++page;
        for (int i = 0; i < rowCnt * colCnt; ++i) {
            levelBtn[i]->setLevel(page * rowCnt * colCnt + i);
            levelBtn[i]->setText(QString::number(levelBtn[i]->getLevel() + 1));
        }
    }
}

void LevelSelectPane::lastClicked() {
    if (page > 0) {
        --page;
        for (int i = 0; i < rowCnt * colCnt; ++i) {
            levelBtn[i]->setLevel(page * rowCnt * colCnt + i);
            levelBtn[i]->setText(QString::number(levelBtn[i]->getLevel() + 1));
        }
    }
}


void LevelSelectPane::levelBtnClicked(int i) {
    okBtn->setLevel(i);
}

void LevelSelectPane::addListener() {
    for (int i = 0; i < rowCnt * colCnt; ++i) {
        connect(levelBtn[i], SIGNAL(sendLevel(int)), this, SLOT(levelBtnClicked(int)));
    }
    connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(nextClicked()));
    connect(lastBtn, SIGNAL(clicked(bool)), this, SLOT(lastClicked()));
}

InfoBtn *LevelSelectPane::getOkBtn() const {
    return okBtn;
}

void LevelSelectPane::reset(PuzzleDegree degree) {
    LevelSelectPane::degree = degree;
    LevelSelectPane::setTitle();
    okBtn->setDegree(degree);
    for (int i = 0; i < rowCnt * colCnt; ++i) {
        levelBtn[i]->setLevel(i);
        levelBtn[i]->setText(QString::number(i + 1));
    }
    LevelSelectPane::page = 0;
    LevelSelectPane::level = 0;
}

void LevelSelectPane::setTitle() {
    switch (degree) {
        case PuzzleDegree::EASY:
            LevelSelectPane::setWindowTitle("简单");
            break;
        case PuzzleDegree::MEDIUM:
            LevelSelectPane::setWindowTitle("中等");
            break;
        case PuzzleDegree::HARD:
            LevelSelectPane::setWindowTitle("困难");
            break;
        case PuzzleDegree::VERY_HARD:
            LevelSelectPane::setWindowTitle("极困难");
            break;
        default:
            break;
    }
}
