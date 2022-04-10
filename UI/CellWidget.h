//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_CELLWIDGET_H
#define SUDOKU_CELLWIDGET_H

#include <QLabel>
#include <iostream>
#include <QMouseEvent>
#include <vector>
using std::vector;


class CellWidget : public QLabel {
Q_OBJECT

public:
    const static QString unDeterminedStyle;
    const static QString determinedStyle;
    const static QString fixedStyle;
    const static QString invalidStyle;

private:
    int i;
    int j;
public:
    int getI() const;

    void setI(int i);

    int getJ() const;

    void setJ(int j);

private:
    int determinedNum;
    bool isDetermined;
public:
    int getDeterminedNum() const;

    void setDeterminedNum(int determinedNum);

private:
    bool isFixed;
public:
    bool IsFixed() const;

    void SetIsFixed(bool isFixed);

public:
    bool IsDetermined() const;

    void SetIsDetermined(bool isDetermined);

    void SetDeterminedNum(int num);

    void SetUndetermined();

    void SetFixedNum();

public:

    explicit CellWidget(QWidget *parent = nullptr);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:

    void num_clicked(vector<int> num);

    void num_removed();

};


#endif //SUDOKU_CELLWIDGET_H
