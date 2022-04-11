//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_LEVELSELECTPANE_H
#define SUDOKU_LEVELSELECTPANE_H

#include <QGridLayout>
#include <QPushButton>
#include <vector>
#include <string>
#include "../Controller/InfoBtn.h"
#include "../Message/PuzzleDegree.h"

using std::string;
using std::vector;

class LevelSelectPane : public QWidget {
Q_OBJECT
private:
    int page;
    int level;
    PuzzleDegree degree;
    int rowCnt;
    int colCnt;
public:
    InfoBtn *getOkBtn() const;

private:
    vector<InfoBtn *> levelBtn;
    QPushButton *nextBtn;
    QPushButton *lastBtn;
    InfoBtn *okBtn;

public:
    explicit LevelSelectPane(PuzzleDegree degree, QWidget *parent = nullptr);

    void initLayout();

    void addListener();

    void reset(PuzzleDegree degree);

    void setTitle();

private slots:

    void levelBtnClicked(int i);

    void nextClicked();

    void lastClicked();


signals:


};


#endif //SUDOKU_LEVELSELECTPANE_H
