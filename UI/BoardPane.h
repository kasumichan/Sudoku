//
// Created by 16000 on 2022/4/8.
//

#ifndef SUDOKU_BOARDPANE_H
#define SUDOKU_BOARDPANE_H

#include <QGridLayout>
#include "../Controller/CellWidget.h"

class BoardPane : public QWidget {
Q_OBJECT
private:
    vector<vector<CellWidget *>> board;

public:
    explicit BoardPane(QWidget *parent = nullptr);

    void initLayout();

    void reset();

    const vector<vector<CellWidget *>> &getBoard() const;

protected:
    void paintEvent(QPaintEvent *event) override;
};


#endif //SUDOKU_BOARDPANE_H
