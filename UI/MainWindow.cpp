//
// Created by 16000 on 2022/4/8.
//

#include "MainWindow.h"

#include <utility>
#include <QDebug>
#include "iostream"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

void MainWindow::initUI() {
    MainWindow::setWindowTitle("数独");
//    setFixedSize(this->width(), this->height());


}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), boardData({}) {
    menubar = new MenuBarPane(this);
    infoPane = new InfoPane(this);
    boardPane = new BoardPane(this);
    interactionBtnPane = new InteractionBtnPane(this);
    fillInBtnPane = new FillInBtnPane(this);
    initUI();
    initLayout();
    addListener();
}

void MainWindow::initLayout() {
    auto *layout = new QVBoxLayout();
    layout->addWidget(menubar);

    auto *mainLayout = new QHBoxLayout();

    auto boardLayout = new QVBoxLayout();
    boardLayout->addWidget(boardPane);
    boardLayout->addWidget(fillInBtnPane);

    auto *playLayout = new QVBoxLayout();
    playLayout->addWidget(infoPane);
    playLayout->addWidget(interactionBtnPane);

    mainLayout->addLayout(boardLayout);
    mainLayout->addLayout(playLayout);

    layout->addLayout(mainLayout);

//    auto *playLayout = new QHBoxLayout();
//    playLayout->addWidget(beginBtn);
//    playLayout->addWidget(nextBtn);
//    layout->addLayout(playLayout);
    setLayout(layout);
}

void MainWindow::addListener() {
    connect(interactionBtnPane, &InteractionBtnPane::hintClicked, this, &MainWindow::nextClicked);

    connect(interactionBtnPane, &InteractionBtnPane::noteClicked, boardPane, &BoardPane::receiveNoteMod);

    connect(interactionBtnPane, &InteractionBtnPane::eraseClicked, boardPane, &BoardPane::receiveErase);

    connect(boardPane, &BoardPane::sendData, this, &MainWindow::modifyList);

    connect(boardPane, &BoardPane::sendErase, this, &MainWindow::erase);

    connect(menubar->getPuzzle(), &PuzzleMenu::sendPuzzleData, this, &MainWindow::receivePuzzleData);

    connect(menubar, &MenuBarPane::startNewGame, this, &MainWindow::newGameStarted);

    connect(fillInBtnPane, &FillInBtnPane::sendNum, boardPane, &BoardPane::receiveNum);
}


void MainWindow::nextClicked() {

    if (determinedList.size() == 81) {
        return;
    }
    Message message = boardData.run();

    switch (message.boardStatus) {
        case BoardStatus::INVALID:
            QMessageBox::information(this, "警告", "你之前有地方填错了！");
            break;
        case BoardStatus::VAGUE:
            QMessageBox::information(this, "说明", "数独信息不够或者我太弱了，等我变强一点。");
            break;
        case BoardStatus::XWING_ROW_FOUND:
            for (int k = 0; k < 9; ++k) {
                if (k != message.excludeData[0].getRow() && k != message.excludeData[2].getRow()) {
                    boardData.getBoard()[k][message.excludeData[0].getColumn()].rmvNum(message.excludeData[0].getNum());
                    boardData.getBoard()[k][message.excludeData[1].getColumn()].rmvNum(message.excludeData[0].getNum());
                }
            }
            infoPane->setPath(infoPane->getPath() + message.solution);
            break;
        case BoardStatus::XWING_COL_FOUND:
            for (int k = 0; k < 9; ++k) {
                if (k != message.excludeData[0].getColumn() && k != message.excludeData[1].getColumn()) {
                    boardData.getBoard()[message.excludeData[0].getRow()][k].rmvNum(message.excludeData[0].getNum());
                    boardData.getBoard()[message.excludeData[2].getRow()][k].rmvNum(message.excludeData[0].getNum());
                }
            }
            infoPane->setPath(infoPane->getPath() + message.solution);
            break;
        case BoardStatus::INTERSECTION_FOUND:
            for (auto data: message.excludeData) {
                boardData.getBoard()[data.getRow()][data.getColumn()].rmvNum(data.getNum());
            }
            infoPane->setPath(infoPane->getPath() + message.solution);
            break;
        case BoardStatus::VALID:
            determinedList.emplace_back(message.cellData.getRow(), message.cellData.getColumn(),
                                        message.cellData.getNum());
            boardPane->getBoard()[message.cellData.getRow()][message.cellData.getColumn()]->setStyleSheet(
                    CellWidget::unselectedStyle);
            boardPane->getBoard()[message.cellData.getRow()][message.cellData.getColumn()]->setDecidedNum(
                    message.cellData.getNum());
            infoPane->setPath(infoPane->getPath() + message.solution);
            break;
        default:
            break;
    }


    if (determinedList.size() == 81) {
        setFixed();
        QMessageBox::information(this, "完成", "太厉害了。");
    }
}


void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
}


void MainWindow::receivePuzzleData(vector<CellStruct> data) {
    reset();
    determinedList = std::move(data);
    for (auto &num: determinedList) {
        boardPane->getBoard()[num.getRow()][num.getColumn()]->setDecidedNum(num.getNum());
        boardPane->getBoard()[num.getRow()][num.getColumn()]->setStyleSheet(CellWidget::fixedStyle);
    }
    setFixed();
    boardData = BoardData(determinedList);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!boardPane->getBoard()[i][j]->isFixed()) {
                boardPane->getBoard()[i][j]->setStyleSheet(CellWidget::selectedStyle);
                boardPane->setPeriStyle(i, j);
                return;
            }
        }
    }
}

void MainWindow::reset() {
    determinedList = {};
    boardData = BoardData(determinedList);
    boardPane->reset();
    infoPane->setPath("");
}

void MainWindow::setFixed() {

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (boardPane->getBoard()[i][j]->getDecidedNum() > 0) {
                boardPane->getBoard()[i][j]->setFixed(true);
            }
        }
    }
}

void MainWindow::newGameStarted() {
    reset();
}

void MainWindow::modifyList(CellStruct cell) {
    for (auto num: determinedList) {
        if (num.getRow() == cell.getRow() && num.getColumn() == cell.getColumn()) {
            num.setNum(cell.getNum());
            return;
        }
    }
    determinedList.push_back(cell);
    boardData = BoardData(determinedList);
    if (boardData.isValid() && determinedList.size() == 81) {
        QMessageBox::information(this, "完成", "太厉害了。");
    }
}

void MainWindow::erase(CellStruct data) {
    vector<CellStruct> newList;
    for (auto a: determinedList) {
        if (a.getRow() == data.getRow() && a.getColumn() == data.getColumn()) {
            continue;
        }
        newList.push_back(a);
    }
    determinedList = newList;
    boardData = BoardData(determinedList);

}
