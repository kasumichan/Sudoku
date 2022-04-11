//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_CELLWIDGET_H
#define SUDOKU_CELLWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>
#include <vector>

using std::vector;


class CellWidget : public QLabel {
Q_OBJECT

public:
    const static QString undecidedStyle;
    const static QString decidedStyle;
    const static QString fixedStyle;
    const static QString invalidStyle;

private:
    int row;
    int col;

    int num;
    bool decided;
    bool fixed;

    int width;
    int height;

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


protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

signals:

    void numClicked(vector<int> num);

    void numRemoved();

};


#endif //SUDOKU_CELLWIDGET_H
