//
// Created by 16000 on 2022/4/11.
//

#include "InfoBtn.h"

#include <utility>
#include <iostream>

void InfoBtn::mousePressEvent(QMouseEvent *e) {
    QAbstractButton::mousePressEvent(e);
    if (text() == "确定") {
        emit sendCellData(readData());
    } else {
        level = std::stoi(InfoBtn::text().toStdString()) - 1;
        emit sendLevel(level);
    }
}

InfoBtn::InfoBtn(const QString &text, string degree, QWidget *parent)
        : QPushButton(parent), degree(std::move(degree)), level(0) {
    InfoBtn::setText(text);
}

int InfoBtn::getLevel() const {
    return level;
}

void InfoBtn::setLevel(int level) {
    InfoBtn::level = level;
}

vector<CellData> InfoBtn::readData() {
    string levelStr;
    if (degree == "简单") {
        levelStr = easy[level];
    } else if (degree == "中等") {
        levelStr = medium[level];
    } else if (degree == "困难") {
        levelStr = hard[level];
    } else {
        levelStr = very_hard[level];
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

const string &InfoBtn::getDegree() const {
    return degree;
}

void InfoBtn::setDegree(const string &degree) {
    InfoBtn::degree = degree;
}
