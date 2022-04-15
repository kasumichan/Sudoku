//
// Created by 16000 on 2022/4/13.
//

#include "FillInBtnPane.h"
#include <QDebug>

FillInBtnPane::FillInBtnPane(QWidget *parent) : QWidget(parent) {
    btn = vector<QPushButton *>(9);
    for (int i = 0; i < 9; ++i) {
        btn[i] = new QPushButton();
        connect(btn[i], &QPushButton::clicked, [=] { emit sendNum(i+1); });
    }
    initLayout();
    setObjectName();

}

void FillInBtnPane::initLayout() {
    auto *layout = new QHBoxLayout;
    for (int i = 0; i < 9; ++i) {
        layout->addWidget(btn[i]);
    }
    setLayout(layout);
}

void FillInBtnPane::setObjectName() {
    for (int i = 0; i < 9; ++i) {
        btn[i]->setObjectName("b" + QString::number(i + 1));
    }

}
