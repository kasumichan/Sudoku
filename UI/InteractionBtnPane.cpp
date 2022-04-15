//
// Created by 16000 on 2022/4/13.
//

#include "InteractionBtnPane.h"
#include <QDebug>

InteractionBtnPane::InteractionBtnPane(QWidget *parent) : QWidget(parent) {
    hintLabel = new QLabel("提示");
    eraseLabel = new QLabel("擦除");
    noteLabel = new QLabel("笔记");
    eraseBtn = new QPushButton();
    noteBtn = new QPushButton();
    hintBtn = new QPushButton();

    setObjectName();
    initLayout();
    addListener();
}

void InteractionBtnPane::initLayout() {
    auto *layout = new QGridLayout;
    layout->addWidget(eraseBtn, 0, 0, 1, 1);
    layout->addWidget(noteBtn, 0, 1, 1, 1);
    layout->addWidget(hintBtn, 0, 2, 1, 1);

    layout->addWidget(eraseLabel, 1, 0, 1, 1);
    layout->addWidget(noteLabel, 1, 1, 1, 1);
    layout->addWidget(hintLabel, 1, 2, 1, 1);

    InteractionBtnPane::setLayout(layout);

}


void InteractionBtnPane::addListener() {
    connect(hintBtn, &QPushButton::clicked, [&] { emit hintClicked(); });
    connect(noteBtn, &QPushButton::clicked, [&] { emit noteClicked(); });
    connect(eraseBtn, &QPushButton::clicked, [&] { emit eraseClicked(); });
}

QPushButton *InteractionBtnPane::getEraseBtn() const {
    return eraseBtn;
}

QPushButton *InteractionBtnPane::getNoteBtn() const {
    return noteBtn;
}

QPushButton *InteractionBtnPane::getHintBtn() const {
    return hintBtn;
}

void InteractionBtnPane::setObjectName() {
    hintLabel->setObjectName("tipLabel");
    eraseLabel->setObjectName("tipLabel");
    noteLabel->setObjectName("tipLabel");

    hintBtn->setObjectName("hintBtn");
    eraseBtn->setObjectName("eraseBtn");
    noteBtn->setObjectName("noteBtn");
}
