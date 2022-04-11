//
// Created by 16000 on 2022/4/10.
//

#include "CellWidget.h"


const QString CellWidget::undecidedStyle = "color:gray;font-size:24px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";
const QString CellWidget::decidedStyle = "color:blue;font-size:50px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";
const QString CellWidget::fixedStyle = "color:green;font-size:50px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";
const QString CellWidget::invalidStyle = "color:red;font-size:50px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";

CellWidget::CellWidget(int row, int col, QWidget *parent, int width, int height) :
        QLabel(parent), width(width), height(height), row(row), col(col), decided(false), fixed(false), num(-1) {
    CellWidget::setFixedSize(width, height);
    CellWidget::setWordWrap(true);
    CellWidget::setAlignment(Qt::AlignCenter);
    CellWidget::setFrameShape(QFrame::Box);
    CellWidget::setFrameShadow(QFrame::Raised);
    CellWidget::setUndecidedStatus();
}

void CellWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
    if (!CellWidget::isFixed()) {
        if (CellWidget::isDecided()) {
            CellWidget::setDecided(false);
            CellWidget::setUndecidedStatus();
            emit numRemoved();
        } else {
            int clickedNum = event->x() / (width / 3) + event->y() / (height / 3) * 3 + 1;
            CellWidget::setDecided(true);
            CellWidget::setDecidedNum(clickedNum);
            emit numClicked({row, col, clickedNum});
        }
    }
}

bool CellWidget::isDecided() const {
    return decided;
}

void CellWidget::setDecided(bool decided) {
    CellWidget::decided = decided;
}

void CellWidget::mousePressEvent(QMouseEvent *event) {
    QLabel::mousePressEvent(event);

}

void CellWidget::mouseReleaseEvent(QMouseEvent *event) {
    QLabel::mouseReleaseEvent(event);
}

void CellWidget::setDecidedNum(int num) {
    CellWidget::num = num;
    setText(QString::fromStdString(std::to_string(num)));
    setStyleSheet(decidedStyle);
}

void CellWidget::setUndecidedStatus() {
    CellWidget::num = -1;
    setText("1 2 3 4 5 6 7 8 9");
    setStyleSheet(undecidedStyle);
}

bool CellWidget::isFixed() const {
    return fixed;
}

void CellWidget::setFixed(bool fixed) {
    CellWidget::fixed = fixed;
    if (isFixed()) {
        CellWidget::setText(QString::fromStdString(std::to_string(num)));
        CellWidget::setStyleSheet(fixedStyle);
    } else {
        CellWidget::setUndecidedStatus();
    }

}

int CellWidget::getDecidedNum() const {
    return num;
}

int CellWidget::getRow() const {
    return row;
}

void CellWidget::setRow(int row) {
    CellWidget::row = row;
}

int CellWidget::getCol() const {
    return col;
}

void CellWidget::setCol(int col) {
    CellWidget::col = col;
}

void CellWidget::reset() {
    CellWidget::setDecided(false);
    CellWidget::setFixed(false);
    CellWidget::setUndecidedStatus();
}
