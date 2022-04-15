//
// Created by 16000 on 2022/4/10.
//

#include "CellWidget.h"
#include <QDebug>


const QString CellWidget::unselectedStyle = "color:#00CED1;background-color:#FFFEE2;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::fixedStyle = "color:#FF4500;background-color:#FFFEE2;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::fixedPeriStyle = "color:#FF4500;background-color:#FDEECF;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::unfixedPeriStyle = "color:#00CED1;background-color:#FDEECF;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::selectedStyle = "color:#ffffff;background-color:#8B4513;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::sameStyle = "color:#ffffff;background-color:#74B116;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::invalidStyle = "color:#ffffff;background-color:#ff0000;font-size:50px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::noteStyle = "color:#00CED1;background-color:#FFFEE2;font-size:24px;border-width:3px;border-style: solid;border-color: #F0E68C;";
const QString CellWidget::notePeriStyle = "color:#00CED1;background-color:#FDEECF;font-size:24px;border-width:3px;border-style: solid;border-color: #F0E68C;";


CellWidget::CellWidget(int row, int col, QWidget *parent, int width, int height) :
        QLabel(parent), width(width), height(height), row(row), col(col), decided(false), fixed(false), num(-1),
        valid(true), noteList({}), noteMod(false) {
    CellWidget::setFixedSize(width, height);
    CellWidget::setWordWrap(true);
    CellWidget::setAlignment(Qt::AlignCenter);
    CellWidget::setFrameShape(QFrame::Box);
    CellWidget::setFrameShadow(QFrame::Raised);
    CellWidget::setUndecidedStatus();
}

//void CellWidget::mouseDoubleClickEvent(QMouseEvent *event) {
//    QWidget::mouseDoubleClickEvent(event);
//    if (!CellWidget::isFixed()) {
//        if (CellWidget::isDecided()) {
//            CellWidget::setDecided(false);
//            CellWidget::setUndecidedStatus();
//            emit numRemoved();
//        } else {
//            int clickedNum = event->x() / (width / 3) + event->y() / (height / 3) * 3 + 1;
//            CellWidget::setDecided(true);
//            CellWidget::setDecidedNum(clickedNum);
//            emit numClicked({row, col, clickedNum});
//        }
//    }
//}

bool CellWidget::isDecided() const {
    return decided;
}

void CellWidget::setDecided(bool decided) {
    CellWidget::decided = decided;
}

void CellWidget::mousePressEvent(QMouseEvent *event) {
    QLabel::mousePressEvent(event);
    emit sendPosition(row, col);

}

void CellWidget::mouseReleaseEvent(QMouseEvent *event) {
    QLabel::mouseReleaseEvent(event);
}

void CellWidget::setDecidedNum(int num) {
    CellWidget::num = num;
    setText(QString::fromStdString(std::to_string(num)));
}

void CellWidget::setUndecidedStatus() {
    CellWidget::num = -1;
    CellWidget::setText("");
    CellWidget::noteList = {};
    setStyleSheet(CellWidget::unselectedStyle);
}

bool CellWidget::isFixed() const {
    return fixed;
}

void CellWidget::setFixed(bool fixed) {
    CellWidget::fixed = fixed;
    if (isFixed()) {
        CellWidget::setText(QString::fromStdString(std::to_string(num)));
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

bool CellWidget::isValid() const {
    return valid;
}

void CellWidget::setValid(bool valid) {
    CellWidget::valid = valid;
}

vector<int> &CellWidget::getNoteList() {
    return noteList;
}

void CellWidget::setNote() {
    QString note = "";
    std::sort(noteList.begin(), noteList.end());
    for (int i = 0; i < noteList.size(); ++i) {
        note += QString::number(noteList[i]);
        if (i != noteList.size() - 1) {
            note += " ";
        }
    }
    setText(note);
}

bool CellWidget::isNoteMod() const {
    return noteMod;
}

void CellWidget::setNoteMod(bool noteMod) {
    CellWidget::noteMod = noteMod;
}

