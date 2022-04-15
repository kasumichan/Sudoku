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
#include "InteractionBtnPane.h"
#include "FillInBtnPane.h"

using std::vector;

class MainWindow : public QWidget {
Q_OBJECT
private:
    BoardPane *boardPane;
    InfoPane *infoPane;
    InteractionBtnPane *interactionBtnPane;
    FillInBtnPane *fillInBtnPane;
    BoardData boardData;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:

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

    void nextClicked();

    void receivePuzzleData(vector<CellStruct>);

    void modifyList(CellStruct cell);

    void erase(CellStruct data);


};


#endif //SUDOKU_MAINWINDOW_H
