//
// Created by 16000 on 2022/4/8.
//

#include "MainWindow.h"
#include "iostream"

void MainWindow::initUI() {
    this->setWindowTitle("Sudoku");
//    this->resize(800, 600);

    menu->setTitle("File");
    menu->addAction("New Game", this, &MainWindow::on_new_game_clicked);
    menu->addAction("Puzzle", this, &MainWindow::on_puzzle_clicked);
    nextBtn->setText("Next Step");
    connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(on_next_clicked()));

    info->setText("123");
    info->setFrameShape(QFrame::Box);
    info->setFrameShadow(QFrame::Raised);

    info->setStyleSheet(
            "border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");

    menubar->addMenu(menu);



//    board->verticalHeader()->setVisible(false);

}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    menubar = new QMenuBar(this);
    menu = new QMenu();
    nextBtn = new QPushButton(this);
    board = vector<vector<QLabel *>>(9, vector<QLabel *>(9));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = new QLabel(QString::fromStdString(std::to_string(i * 10 + j)));
            board[i][j]->setAlignment(Qt::AlignCenter);
            board[i][j]->setFixedSize(80, 80);
            board[i][j]->setFrameShape(QFrame::Box);
            board[i][j]->setFrameShadow(QFrame::Raised);

            board[i][j]->setStyleSheet(
                    "border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");

        }
    }
    info = new QLabel(this);
    info->setFixedWidth(600);
    initUI();
    initLayout();

}

void MainWindow::initLayout() {
    auto *layout = new QVBoxLayout();
    layout->addWidget(menubar);

    auto *mainLayout = new QHBoxLayout();
    auto *boardLayout = new QGridLayout();

    mainLayout->addLayout(boardLayout);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            boardLayout->addWidget(board[i][j], i, j, 1, 1);
        }
    }
    mainLayout->addWidget(info);

    layout->addLayout(mainLayout);

    layout->addWidget(nextBtn);
    setLayout(layout);
}

void MainWindow::addListener() {

}

void MainWindow::on_new_game_clicked() {
    std::cout << "qwe";
}

void MainWindow::on_puzzle_clicked() {
    std::cout << "puzzle";
}

void MainWindow::on_next_clicked() {
    std::cout << "nextBtn";
}
