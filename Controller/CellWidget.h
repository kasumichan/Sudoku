//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_CELLWIDGET_H
#define SUDOKU_CELLWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include <vector>
#include "../Message/CellStruct.h"

using std::vector;


class CellWidget : public QLabel {
Q_OBJECT

public:
    const static QString unselectedStyle;
    const static QString selectedStyle;
    const static QString fixedPeriStyle;
    const static QString unfixedPeriStyle;
    const static QString sameStyle;
    const static QString invalidStyle;
    const static QString fixedStyle;
    const static QString noteStyle;
    const static QString notePeriStyle;

private:
    int row;
    int col;

    int num;
    bool decided;
    bool fixed;

    int width;
    int height;

    bool valid;

    vector<int> noteList;

    bool noteMod;
public:
    bool isNoteMod() const;

    void setNoteMod(bool noteMod);

public:
    bool isValid() const;

    void setValid(bool valid);

public:

    CellWidget(int row, int col, QWidget *parent = nullptr, int width = 80, int height = 80);

    int getRow() const;

    void setRow(int row);

    int getCol() const;

    void setCol(int col);

    bool isFixed() const;

    void setFixed(bool fixed);

    bool isDecided() const;

    void setDecided(bool decided);

    int getDecidedNum() const;

    void setDecidedNum(int num);

    void setUndecidedStatus();

    void reset();

    vector<int> &getNoteList();

    void setNote();


protected:
//    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

signals:

    void numClicked(vector<int> num);

    void numRemoved();

    void sendPosition(int row, int col);

};


#endif //SUDOKU_CELLWIDGET_H
