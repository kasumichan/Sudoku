//
// Created by 16000 on 2022/4/8.
//

#ifndef SUDOKU_BOARDWIDGET_H
#define SUDOKU_BOARDWIDGET_H

#include <QGridLayout>
#include "CellWidget.h"

class BoardWidget : public QWidget {
Q_OBJECT
private:
    vector<vector<CellWidget *>> board;

public:
    explicit BoardWidget(QWidget *parent = nullptr);

    void initLayout();

    void reset();

    const vector<vector<CellWidget *>> &getBoard() const;

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //SUDOKU_BOARDWIDGET_H
