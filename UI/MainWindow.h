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
#include <QFrame>
#include <vector>
#include <string>
using std::vector;

class MainWindow : public QWidget {
Q_OBJECT
private:
    vector<vector<QLabel*>> board;
    QLabel *info;
    QPushButton *nextBtn;
    QMenu *menu;
    QMenuBar *menubar;

public:

    explicit MainWindow(QWidget *parent = nullptr);

    void initUI();

    void initLayout();

    void addListener();

private slots:
    static void on_new_game_clicked();
    static void on_puzzle_clicked();
    static void on_next_clicked();
};




#endif //SUDOKU_MAINWINDOW_H
