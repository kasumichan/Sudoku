//
// Created by 16000 on 2022/4/8.
//

#include "MainWindow.h"

#include <utility>
#include "iostream"
#include "fstream"
#include "sstream"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

void MainWindow::initUI() {
    MainWindow::setWindowTitle("数独");
//    setFixedSize(this->width(), this->height());

    nextBtn->setText("下一步");
    beginBtn->setText("开始游戏");


}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), boardData({}) {
    menubar = new MenuBarPane(this);
    infoWidget = new InfoPane(this);
    nextBtn = new QPushButton(this);
    beginBtn = new QPushButton(this);
    boardWidget = new BoardPane(this);
    initUI();
    initLayout();
    addListener();
}

void MainWindow::initLayout() {
    auto *layout = new QVBoxLayout();
    layout->addWidget(menubar);

    auto *mainLayout = new QHBoxLayout();

    mainLayout->addWidget(boardWidget);
    mainLayout->addWidget(infoWidget);

    layout->addLayout(mainLayout);

    auto *playLayout = new QHBoxLayout();
    playLayout->addWidget(beginBtn);
    playLayout->addWidget(nextBtn);
    layout->addLayout(playLayout);
    setLayout(layout);
}

void MainWindow::addListener() {
    connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(on_next_clicked()));
    connect(beginBtn, SIGNAL(clicked(bool)), this, SLOT(on_begin_clicked()));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            connect(boardWidget->getBoard()[i][j], SIGNAL(numRemoved()), this, SLOT(remove_num()));
            connect(boardWidget->getBoard()[i][j], SIGNAL(numClicked(vector<int>)), this, SLOT(add_num(vector<int>)));
        }
    }
    connect(menubar->getPuzzle(), SIGNAL(sendPuzzleData(vector<CellStruct>)), this,
            SLOT(receivePuzzleData(vector<CellStruct>)));

    connect(menubar, SIGNAL(startNewGame()), this, SLOT(newGameStarted()));
}


void MainWindow::on_next_clicked() {

    if (determinedList.size() == 81) {
        return;
    }
    Message message = boardData.run();

    switch (message.boardStatus) {
        case BoardStatus::INVALID:
            QMessageBox::information(this, "警告", "数独非法");
            break;
        case BoardStatus::VAGUE:
            QMessageBox::information(this, "说明", "数独信息不够或者我太弱了，等我变强一点。");
            break;
        case BoardStatus::HINT:
            boardData.getBoard()[message.cellData.getRow()][message.cellData.getColumn()].rmvNum(
                    message.cellData.getNum());
            infoWidget->setPath(infoWidget->getPath() + message.solution);
            break;
        case BoardStatus::VALID:
            determinedList.emplace_back(message.cellData.getRow(), message.cellData.getColumn(),
                                        message.cellData.getNum());
            boardWidget->getBoard()[message.cellData.getRow()][message.cellData.getColumn()]->setDecidedNum(
                    message.cellData.getNum());
            infoWidget->setPath(infoWidget->getPath() + message.solution);
            break;
        default:
            break;
    }


    if (determinedList.size() == 81) {
        setFixed();
        QMessageBox::information(this, "完成", "太厉害了。");
    }
}

void MainWindow::on_begin_clicked() {
    determinedList = {};
    infoWidget->setPath("");
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (boardWidget->getBoard()[i][j]->getDecidedNum() > 0) {
                determinedList.emplace_back(i, j, boardWidget->getBoard()[i][j]->getDecidedNum());
            }
        }
    }
    boardData = BoardData(determinedList);
    if (!boardData.isValid()) {
        QMessageBox::information(this, "警告", "数独非法");
        return;
    }
    setFixed();
}


void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
    boardData = BoardData(determinedList);
    if (!boardData.isValid()) {
        boardWidget->getBoard()[determinedList.back().getRow()][determinedList.back().getColumn()]->setStyleSheet(
                CellWidget::invalidStyle);
    }
    if (boardData.isValid() && determinedList.size() == 81) {
        QMessageBox::information(this, "完成", "太厉害了。");
    }
}

void MainWindow::add_num(vector<int> numVec) {
    determinedList.emplace_back(numVec[0], numVec[1], numVec[2]);

}

void MainWindow::remove_num() {
    determinedList.pop_back();
}

void MainWindow::receivePuzzleData(vector<CellStruct> data) {
    reset();
    determinedList = std::move(data);
    for (auto &num: determinedList) {
        boardWidget->getBoard()[num.getRow()][num.getColumn()]->setDecidedNum(num.getNum());
    }
    setFixed();
    boardData = BoardData(determinedList);
}

void MainWindow::reset() {
    determinedList = {};
    boardWidget->reset();
    infoWidget->setPath("");
}

void MainWindow::setFixed() {

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (boardWidget->getBoard()[i][j]->getDecidedNum() > 0) {
                boardWidget->getBoard()[i][j]->setFixed(true);
            }
        }
    }
}

void MainWindow::newGameStarted() {
    reset();
}
