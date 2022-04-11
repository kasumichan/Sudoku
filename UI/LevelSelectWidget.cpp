//
// Created by 16000 on 2022/4/11.
//

#include "LevelSelectWidget.h"

#include <utility>
#include<iostream>

using namespace std;

LevelSelectWidget::LevelSelectWidget(string degree, QWidget *parent) :
        QWidget(parent), page(0), level(0), btnRow(4), btnCol(5) {
    LevelSelectWidget::degree = std::move(degree);
    for (int i = 0; i < 20; ++i) {
        levelBtn.push_back(new InfoBtn(QString::fromStdString(std::to_string(i + 1))));
    }
    lastBtn = new QPushButton("上一页");
    nextBtn = new QPushButton("下一页");
    okBtn = new InfoBtn("确定", "简单");
    initLayout();
    addListener();
}

void LevelSelectWidget::initLayout() {
    LevelSelectWidget::setWindowTitle(QString::fromStdString(degree));
    auto *layout = new QGridLayout;
    for (int i = 0; i < btnRow; ++i) {
        for (int j = 0; j < btnCol; ++j) {
            layout->addWidget(levelBtn[i * btnCol + j], i, j, 1, 1);
        }
    }
    layout->addWidget(lastBtn, 4, 0, 1, 2);
    layout->addWidget(nextBtn, 4, 3, 1, 2);
    layout->addWidget(okBtn, 5, 0, 1, 5);

    LevelSelectWidget::setLayout(layout);
}

void LevelSelectWidget::nextClicked() {
    if (page < 4) {
        ++page;
        for (int i = 0; i < btnRow * btnCol; ++i) {
            levelBtn[i]->setText(QString::fromStdString(std::to_string(page * btnRow * btnCol + i + 1)));
        }
    }
}

void LevelSelectWidget::lastClicked() {
    if (page > 0) {
        --page;
        for (int i = 0; i < btnRow * btnCol; ++i) {
            levelBtn[i]->setText(QString::fromStdString(std::to_string(page * btnRow * btnCol + i + 1)));
        }
    }
}


void LevelSelectWidget::levelBtnClicked(int i) {
    level = levelBtn[i]->getLevel();
    okBtn->setLevel(level);
}

void LevelSelectWidget::addListener() {
    for (int i = 0; i < btnRow * btnCol; ++i) {
        connect(levelBtn[i], SIGNAL(sendLevel(int)), this, SLOT(levelBtnClicked(int)));
    }
    connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(nextClicked()));
    connect(lastBtn, SIGNAL(clicked(bool)), this, SLOT(lastClicked()));
}

InfoBtn *LevelSelectWidget::getOkBtn() const {
    return okBtn;
}

void LevelSelectWidget::reset(string degree) {
    LevelSelectWidget::degree = degree;
    LevelSelectWidget::setWindowTitle(QString::fromStdString(degree));
    okBtn->setDegree(degree);
    LevelSelectWidget::page = 0;
    LevelSelectWidget::level = 0;
}
