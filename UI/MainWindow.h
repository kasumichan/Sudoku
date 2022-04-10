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

#include "../Message.h"
#include "CellWidget.h"
#include "../Board.h"

using std::vector;

class MainWindow : public QWidget {
Q_OBJECT
private:
    vector<string> easy = {"0 1 5\n",
                           "0 2 2\n",
                           "0 5 6\n",
                           "1 0 1\n",
                           "1 1 6\n",
                           "1 3 9\n",
                           "1 8 4\n",
                           "2 1 4\n",
                           "2 2 9\n",
                           "2 3 8\n",
                           "2 5 3\n",
                           "2 6 6\n",
                           "2 7 2\n",
                           "3 0 4\n",
                           "3 6 8\n",
                           "4 1 8\n",
                           "4 2 3\n",
                           "4 3 2\n",
                           "4 5 1\n",
                           "4 6 5\n",
                           "4 7 9\n",
                           "5 2 1\n",
                           "5 8 2\n",
                           "6 1 9\n",
                           "6 2 7\n",
                           "6 3 3\n",
                           "6 5 5\n",
                           "6 6 2\n",
                           "6 7 4\n",
                           "7 0 2\n",
                           "7 5 9\n",
                           "7 7 5\n",
                           "7 8 6\n",
                           "8 3 1\n",
                           "8 6 9\n",
                           "8 7 7"};

    vector<string> hard = {"0 0 6\n",
                           "0 3 3\n",
                           "0 6 1\n",
                           "1 1 7\n",
                           "1 2 1\n",
                           "1 3 6\n",
                           "1 4 2\n",
                           "2 0 8\n",
                           "2 2 5\n",
                           "2 5 1\n",
                           "3 0 5\n",
                           "3 3 8\n",
                           "3 4 7\n",
                           "3 6 9\n",
                           "3 8 1\n",
                           "4 2 9\n",
                           "4 6 6\n",
                           "5 0 4\n",
                           "5 2 7\n",
                           "5 4 6\n",
                           "5 5 9\n",
                           "5 8 8\n",
                           "6 3 2\n",
                           "6 6 8\n",
                           "6 8 7\n",
                           "7 4 8\n",
                           "7 5 6\n",
                           "7 6 4\n",
                           "7 7 1\n",
                           "8 2 8\n",
                           "8 5 3\n",
                           "8 8 2"};
    vector<vector<CellWidget *>> board;
    Board board1;
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QLabel *info;
    QLabel *tip;

    QPushButton *nextBtn;
    QPushButton *beginBtn;
    QMenu *menu;
    QMenuBar *menubar;

    vector<vector<int>> determinedList;
    string path;

public:

    explicit MainWindow(QWidget *parent = nullptr);

    void initUI();

    void initLayout();

    void addListener();

private slots:

    void on_new_game_clicked();

    void on_easy_puzzle_clicked();

    void on_setting_clicked();

    void on_next_clicked();

    void on_begin_clicked();

    void on_hard_puzzle_clicked();

    void add_num(vector<int> numVec);

    void remove_num();
};


#endif //SUDOKU_MAINWINDOW_H
