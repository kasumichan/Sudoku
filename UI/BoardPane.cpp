//
// Created by 16000 on 2022/4/8.
//

#include "BoardPane.h"
#include <QPainter>
#include <QDebug>

BoardPane::BoardPane(QWidget *parent) : QWidget(parent), noteMod(false) {
    board = vector<vector<CellWidget *>>(9, vector<CellWidget *>(9));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = new CellWidget(i, j);
            connect(board[i][j], &CellWidget::sendPosition, this, &BoardPane::receivePos);
        }
    }
    selectedRow = 0;
    selectedCol = 0;
    BoardPane::initLayout();
    reset();

}

void BoardPane::initLayout() {
    setFixedSize(750, 750);
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
//    layout->setSpacing(10);
//    QPalette pal(this->palette());
//    //设置背景黑色
//    pal.setColor(QPalette::Background, Qt::green);
//    BoardPane::setAutoFillBackground(true);
//    BoardPane::setPalette(pal);
    BoardPane::setLayout(layout);

}

const vector<vector<CellWidget *>> &BoardPane::getBoard() const {
    return board;
}

void BoardPane::reset() {
    BoardPane::setUnselectedStatus();
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j]->reset();
        }
    }
    board[0][0]->setStyleSheet(CellWidget::selectedStyle);
    setPeriStyle(0, 0);
}

void BoardPane::receivePos(int row, int col) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j]->isValid()) {
                return;
            }
        }
    }
    BoardPane::selectedRow = row;
    BoardPane::selectedCol = col;
    setUnselectedStatus();
    if (board[row][col]->isValid() && !board[row][col]->isNoteMod()) {
        board[row][col]->setStyleSheet(CellWidget::selectedStyle);
    }
    setPeriStyle(row, col);
    setSameNumStyle(row, col);

}

void BoardPane::receiveNum(int num) {

    if (!board[selectedRow][selectedCol]->isFixed()) {
        if (noteMod && !board[selectedRow][selectedCol]->isDecided()) {
            board[selectedRow][selectedCol]->setNoteMod(true);
            board[selectedRow][selectedCol]->setStyleSheet(CellWidget::noteStyle);

            if (std::find(board[selectedRow][selectedCol]->getNoteList().begin(),
                          board[selectedRow][selectedCol]->getNoteList().end(), num) !=
                board[selectedRow][selectedCol]->getNoteList().end()) {
                board[selectedRow][selectedCol]->getNoteList().erase(
                        std::remove(board[selectedRow][selectedCol]->getNoteList().begin(),
                                    board[selectedRow][selectedCol]->getNoteList().end(), num),
                        board[selectedRow][selectedCol]->getNoteList().end());
            } else {
                board[selectedRow][selectedCol]->getNoteList().push_back(num);
            }
            board[selectedRow][selectedCol]->setNote();

        } else {
            board[selectedRow][selectedCol]->setNoteMod(false);
            board[selectedRow][selectedCol]->setDecidedNum(num);
            board[selectedRow][selectedCol]->setDecided(true);
            setUnselectedStatus();
            bool flag = true;
            int b = selectedRow / 3 * 3 + selectedCol / 3;
            int k = selectedRow % 3 * 3 + selectedCol % 3;
            for (int i = 0; i < 9; ++i) {
                if (i != selectedRow) {
                    if (board[i][selectedCol]->getDecidedNum() == board[selectedRow][selectedCol]->getDecidedNum()) {
                        flag = false;
                        break;
                    }
                }
                if (i != selectedCol) {
                    if (board[selectedRow][i]->getDecidedNum() == board[selectedRow][selectedCol]->getDecidedNum()) {
                        flag = false;
                        break;
                    }
                }
                if (i != k) {
                    if (board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->getDecidedNum() ==
                        board[selectedRow][selectedCol]->getDecidedNum()) {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) {
                emit sendData({selectedRow, selectedCol, num});
                board[selectedRow][selectedCol]->setValid(true);
                board[selectedRow][selectedCol]->setStyleSheet(CellWidget::selectedStyle);
            } else {
                board[selectedRow][selectedCol]->setValid(false);
                board[selectedRow][selectedCol]->setStyleSheet(CellWidget::invalidStyle);
            }
            setPeriStyle(selectedRow, selectedCol);
            setSameNumStyle(selectedRow, selectedCol);
        }
    }

}

void BoardPane::setUnselectedStatus() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j]->isValid())continue;
            if (board[i][j]->isFixed()) {
                board[i][j]->setStyleSheet(CellWidget::fixedStyle);
            } else if (board[i][j]->isNoteMod()) {
                board[i][j]->setStyleSheet(CellWidget::noteStyle);
            } else {
                board[i][j]->setStyleSheet(CellWidget::unselectedStyle);
            }
        }
    }
}

void BoardPane::setSameNumStyle(int row, int col) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!board[i][j]->isValid())continue;
            if (board[i][j]->getDecidedNum() == board[row][col]->getDecidedNum() &&
                0 < board[i][j]->getDecidedNum() && board[i][j]->getDecidedNum() <= 9) {
                board[i][j]->setStyleSheet(CellWidget::sameStyle);
            }
        }
    }

}

void BoardPane::setPeriStyle(int row, int col) {
    int b = row / 3 * 3 + col / 3;
    int k = row % 3 * 3 + col % 3;
    for (int i = 0; i < 9; ++i) {
//        if (!board[i][col]->isValid() || !board[row][i]->isValid() ||
//            !board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->isValid())
//            continue;
        if (i != row) {
            if (board[i][col]->isFixed()) {
                board[i][col]->setStyleSheet(CellWidget::fixedPeriStyle);
            } else if (board[i][col]->isNoteMod()) {
                board[i][col]->setStyleSheet(CellWidget::notePeriStyle);
            } else {
                board[i][col]->setStyleSheet(CellWidget::unfixedPeriStyle);
            }
        }
        if (i != col) {
            if (board[row][i]->isFixed()) {
                board[row][i]->setStyleSheet(CellWidget::fixedPeriStyle);
            } else if (board[row][i]->isNoteMod()) {
                board[row][i]->setStyleSheet(CellWidget::notePeriStyle);
            } else {
                board[row][i]->setStyleSheet(CellWidget::unfixedPeriStyle);
            }
        }
        if (i != k) {
            if (board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->isFixed()) {
                board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->setStyleSheet(CellWidget::fixedPeriStyle);
            } else if (board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->isNoteMod()) {
                board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->setStyleSheet(CellWidget::notePeriStyle);
            } else {
                board[b / 3 * 3 + i / 3][b % 3 * 3 + i % 3]->setStyleSheet(CellWidget::unfixedPeriStyle);
            }
        }
    }
}

void BoardPane::receiveNoteMod() {
    BoardPane::noteMod = !BoardPane::noteMod;
}

void BoardPane::receiveErase() {
    if (!board[selectedRow][selectedCol]->isFixed()) {
        if (board[selectedRow][selectedCol]->getDecidedNum() > 0 &&
            board[selectedRow][selectedCol]->getDecidedNum() <= 9) {
            emit sendErase({selectedRow, selectedCol, board[selectedRow][selectedCol]->getDecidedNum()});
        }
        board[selectedRow][selectedCol]->setUndecidedStatus();
        board[selectedRow][selectedCol]->setValid(true);
        setUnselectedStatus();
        board[selectedRow][selectedCol]->setStyleSheet(CellWidget::selectedStyle);
        setPeriStyle(selectedRow, selectedCol);
        setSameNumStyle(selectedRow, selectedCol);
    }
}
