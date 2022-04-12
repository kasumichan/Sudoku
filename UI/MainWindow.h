//
// Created by 16000 on 2022/4/8.
//

#ifndef SUDOKU_MAINWINDOW_H
#define SUDOKU_MAINWINDOW_H


#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QScrollArea>
#include <QFrame>
#include <vector>
#include <string>
#include <QPainter>

#include "../Message/Message.h"
#include "BoardPane.h"
#include "../Game/BoardData.h"
#include "MenuBarPane.h"
#include "InfoPane.h"

using std::vector;

class MainWindow : public QWidget {
Q_OBJECT
private:
    BoardPane *boardWidget;
    InfoPane *infoWidget;
    BoardData boardData;
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:

    QPushButton *nextBtn;
    QPushButton *beginBtn;

    MenuBarPane *menubar;

    vector<CellStruct> determinedList;

public:

    explicit MainWindow(QWidget *parent = nullptr);

    void initUI();

    void initLayout();

    void addListener();

    void reset();

    void setFixed();

private slots:

    void newGameStarted();

    void on_next_clicked();

    void on_begin_clicked();

    void receivePuzzleData(vector<CellStruct>);

    void add_num(vector<int> numVec);

    void remove_num();

};


#endif //SUDOKU_MAINWINDOW_H
