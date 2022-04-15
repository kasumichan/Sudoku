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
    bool noteMod;
    int selectedRow;
    int selectedCol;

private:

public:
    explicit BoardPane(QWidget *parent = nullptr);

    void initLayout();

    void reset();

    const vector<vector<CellWidget *>> &getBoard() const;

    void setPeriStyle(int row, int col);

    void setUnselectedStatus();

    void setSameNumStyle(int row, int col);

public slots:

    void receivePos(int row, int col);

    void receiveNum(int num);

    void receiveErase();

    void receiveNoteMod();

signals:

    void sendData(CellStruct data);

    void sendErase(CellStruct data);


};


#endif //SUDOKU_BOARDPANE_H
