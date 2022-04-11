//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_LEVELSELECTWIDGET_H
#define SUDOKU_LEVELSELECTWIDGET_H

#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <string>
#include "InfoBtn.h"

using std::string;
using std::vector;

class LevelSelectWidget : public QWidget {
Q_OBJECT
private:
    int page;
    int level;
    string degree;
    int btnRow;
    int btnCol;
public:
    InfoBtn *getOkBtn() const;

private:
    vector<InfoBtn *> levelBtn;
    QPushButton *nextBtn;
    QPushButton *lastBtn;
    InfoBtn *okBtn;

public:
    explicit LevelSelectWidget(string degree, QWidget *parent = nullptr);

    void initLayout();

    void addListener();

    void reset(string degree);

private slots:

    void levelBtnClicked(int i);

    void nextClicked();

    void lastClicked();


signals:


};


#endif //SUDOKU_LEVELSELECTWIDGET_H
