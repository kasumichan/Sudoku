//
// Created by 16000 on 2022/4/13.
//

#ifndef SUDOKU_FILLINBTNPANE_H
#define SUDOKU_FILLINBTNPANE_H

#include <QWidget>
#include <QPushButton>
#include <vector>
#include <QHBoxLayout>
#include <QFile>

using std::vector;

class FillInBtnPane : public QWidget {
Q_OBJECT
private:
    vector<QPushButton *> btn;

private:
    void initLayout();

    void setObjectName();

public:
    explicit FillInBtnPane(QWidget *parent = nullptr);

signals:
    void sendNum(int num);
};


#endif //SUDOKU_FILLINBTNPANE_H
