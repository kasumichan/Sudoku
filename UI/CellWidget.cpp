//
// Created by 16000 on 2022/4/10.
//

#include "CellWidget.h"


const QString CellWidget::unDeterminedStyle = "color:gray;font-size:24px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";
const QString CellWidget::determinedStyle = "color:blue;font-size:50px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";
const QString CellWidget::fixedStyle = "color:green;font-size:50px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";
const QString CellWidget::invalidStyle = "color:red;font-size:50px;border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);";

CellWidget::CellWidget(QWidget *parent) : QLabel(parent) {
    i = -1;
    j = -1;
    determinedNum = -1;
    isFixed = false;
    isDetermined = false;
}

void CellWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
    int clickedNum = event->x() / 27 + event->y() / 27 * 3 + 1;
//    std::cout << clickedNum << std::endl;
    if (!isDetermined && !isFixed) {
        SetDeterminedNum(clickedNum);
        emit num_clicked({i, j, clickedNum});
    } else if (!isFixed) {
        emit num_removed();
        SetUndetermined();
    }
}

bool CellWidget::IsDetermined() const {
    return isDetermined;
}

void CellWidget::SetIsDetermined(bool isDetermined) {
    CellWidget::isDetermined = isDetermined;
}

void CellWidget::mousePressEvent(QMouseEvent *event) {
    QLabel::mousePressEvent(event);

}

void CellWidget::mouseReleaseEvent(QMouseEvent *ev) {
    QLabel::mouseReleaseEvent(ev);


}

void CellWidget::SetDeterminedNum(int num) {
    determinedNum = num;
    setText(QString::fromStdString(std::to_string(num)));
    setStyleSheet(determinedStyle);
    isDetermined = !isDetermined;
}

void CellWidget::SetUndetermined() {

    setText("1 2 3 4 5 6 7 8 9");
    setStyleSheet(unDeterminedStyle);
    isDetermined = false;
}

bool CellWidget::IsFixed() const {
    return isFixed;
}

void CellWidget::SetIsFixed(bool isFixed) {
    CellWidget::isFixed = isFixed;
}

void CellWidget::SetFixedNum() {

    setText(QString::fromStdString(std::to_string(determinedNum)));
    setStyleSheet(fixedStyle);
    isFixed = true;
}

int CellWidget::getDeterminedNum() const {
    return determinedNum;
}

void CellWidget::setDeterminedNum(int determinedNum) {
    CellWidget::determinedNum = determinedNum;
}

int CellWidget::getI() const {
    return i;
}

void CellWidget::setI(int i) {
    CellWidget::i = i;
}

int CellWidget::getJ() const {
    return j;
}

void CellWidget::setJ(int j) {
    CellWidget::j = j;
}
