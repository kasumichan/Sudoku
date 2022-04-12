//
// Created by 16000 on 2022/4/11.
//

#include "InfoBtn.h"

#include <utility>
#include <iostream>

void InfoBtn::mouseReleaseEvent(QMouseEvent *e) {
    QAbstractButton::mousePressEvent(e);
    if (text() == "确定") {
        emit sendCellData(readData());
    } else {
        setCheckable(true);
        setChecked(true);
        emit sendLevel(level);
    }
}

InfoBtn::InfoBtn(PuzzleDegree degree, QWidget *parent)
        : QPushButton(parent), degree(degree), level(0) {
}

int InfoBtn::getLevel() const {
    return level;
}

void InfoBtn::setLevel(int level) {
    InfoBtn::level = level;
}

vector<CellData> InfoBtn::readData() {
    string levelStr;

    switch (degree) {
        case PuzzleDegree::EASY:
            levelStr = easy[level];
            break;
        case PuzzleDegree::MEDIUM:
            levelStr = medium[level];
            break;
        case PuzzleDegree::HARD:
            levelStr = hard[level];
            break;
        case PuzzleDegree::VERY_HARD:
            levelStr = very_hard[level];
            break;
        default:
            break;
    }
    vector<int> levelVec;
    levelVec.reserve(81);
    for (int i = 0; i < 81; ++i) {
        levelVec.push_back(levelStr[i] - '0');
    }
    vector<CellData> cd;
    for (int i = 0; i < 81; ++i) {
        if (levelVec[i] != 0) {
            cd.emplace_back(i / 9, i % 9, levelVec[i]);
        }
    }
    return cd;

}

PuzzleDegree InfoBtn::getDegree() const {
    return degree;
}

void InfoBtn::setDegree(PuzzleDegree degree) {
    InfoBtn::degree = degree;
}


