//
// Created by 16000 on 2022/4/8.
//

#include "BoardPane.h"
#include <QPainter>

BoardPane::BoardPane(QWidget *parent) : QWidget(parent) {
    board = vector<vector<CellWidget *>>(9, vector<CellWidget *>(9));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = new CellWidget(i, j);
        }
    }

    BoardPane::initLayout();

}

void BoardPane::initLayout() {
    setFixedSize(750,750);
    vector<vector<QGridLayout *>> layoutVec(3, vector<QGridLayout *>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            layoutVec[i][j] = new QGridLayout;
            layoutVec[i][j]->setSpacing(0);
            for (int m = 0; m < 3; ++m) {
                for (int n = 0; n < 3; ++n) {
                    layoutVec[i][j]->addWidget(board[i * 3 + m][j * 3 + n], m, n, 1, 1);
                }
            }
        }
    }

    auto *layout = new QGridLayout;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            layout->addLayout(layoutVec[i][j], i, j, 1, 1);

        }
    }
    layout->setSpacing(10);
    QPalette pal(this->palette());

    //设置背景黑色
    pal.setColor(QPalette::Background, Qt::black);
    BoardPane::setAutoFillBackground(true);
    BoardPane::setPalette(pal);
    BoardPane::setLayout(layout);

}

const vector<vector<CellWidget *>> &BoardPane::getBoard() const {
    return board;
}

void BoardPane::reset() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j]->reset();
        }
    }
}

void BoardPane::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::black,4));
////    painter.
//    painter.drawLine(20, this->width()/3, 740, this->width()/3);
}
