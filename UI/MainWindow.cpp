//
// Created by 16000 on 2022/4/8.
//

#include "MainWindow.h"
#include "iostream"
#include "fstream"
#include "sstream"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

void MainWindow::initUI() {
    this->setWindowTitle("数独");
//    setFixedSize(this->width(), this->height());

    menu->setTitle("打开");
    menu->addAction("自定义游戏", this, &MainWindow::on_new_game_clicked);
    auto *puzzle = new QMenu("谜题");
    puzzle->addAction("简单", this, &MainWindow::on_easy_puzzle_clicked);
    puzzle->addAction("困难", this, &MainWindow::on_hard_puzzle_clicked);
    menu->addMenu(puzzle);
    menu->addAction("说明", this, &MainWindow::on_setting_clicked);
    nextBtn->setText("下一步");
    beginBtn->setText("开始游戏");
    connect(nextBtn, SIGNAL(clicked(bool)), this, SLOT(on_next_clicked()));
    connect(beginBtn, SIGNAL(clicked(bool)), this, SLOT(on_begin_clicked()));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            connect(board[i][j], SIGNAL(num_removed()), this, SLOT(remove_num()));
            connect(board[i][j], SIGNAL(num_clicked(vector<int>)), this, SLOT(add_num(vector<int>)));
        }
    }

    info->setAlignment(Qt::AlignTop);
    info->setFrameShape(QFrame::Box);
    info->setWordWrap(true);
    info->setFrameShadow(QFrame::Raised);

    info->setStyleSheet(
            "border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");
    tip->setText("路径提示");
    tip->setAlignment(Qt::AlignCenter);
    tip->setFixedWidth(400);
    menubar->addMenu(menu);



//    board->verticalHeader()->setVisible(false);

}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), board1({}) {
    menubar = new QMenuBar(this);
    menu = new QMenu();
    nextBtn = new QPushButton(this);
    beginBtn = new QPushButton(this);
    board = vector<vector<CellWidget *>>(9, vector<CellWidget *>(9));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = new CellWidget();
            board[i][j]->setI(i);
            board[i][j]->setJ(j);
            board[i][j]->setText("1 2 3 4 5 6 7 8 9");
            board[i][j]->setWordWrap(true);
            board[i][j]->setAlignment(Qt::AlignCenter);
            board[i][j]->setFixedSize(80, 80);
            board[i][j]->setFrameShape(QFrame::Box);
            board[i][j]->setFrameShadow(QFrame::Raised);

            board[i][j]->setStyleSheet(CellWidget::unDeterminedStyle);

//            board[i][j]->setStyleSheet("background-color: rgb(250, 0, 0);font-size:60px;color:blue");
        }
    }
    info = new QLabel(this);
    tip = new QLabel(this);
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
    auto *tipLayout = new QVBoxLayout;
//    tipLayout->setAlignment(Qt::AlignCenter);
    tipLayout->addWidget(tip);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    info->setFixedWidth(400);
    info->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    info->setScaledContents(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidget(info);
    tipLayout->addWidget(scrollArea);
    mainLayout->addLayout(tipLayout);

    layout->addLayout(mainLayout);

    auto *playLayout = new QHBoxLayout();
    playLayout->addWidget(beginBtn);
    playLayout->addWidget(nextBtn);
    layout->addLayout(playLayout);
    setLayout(layout);
}

void MainWindow::addListener() {

}

void MainWindow::on_new_game_clicked() {
    info->setText("");
    path = "";

    determinedList = {};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j]->SetUndetermined();
            board[i][j]->SetIsFixed(false);
            board[i][j]->setDeterminedNum(-1);
        }
    }

}

void MainWindow::on_easy_puzzle_clicked() {

    path = "";
    info->setText("");

    determinedList = {};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j]->SetUndetermined();
            board[i][j]->SetIsFixed(false);
            board[i][j]->setDeterminedNum(-1);
        }
    }
//    string filename("puzzle2.pz");
//    vector<string> lines;
//    string line;

//    ifstream puzzle_file(filename);
//    vector<vector<int>> tempList;
//    while (getline(puzzle_file, line)) {
//        std::stringstream ss(line);
//        std::string temp;
//        vector<int> tempVec;
//        while (ss >> temp) {
//            tempVec.push_back(std::stoi(temp));
//        }
//        tempList.push_back(tempVec);
//    }
    vector<string> lines;
    string line;

    vector<vector<int>> tempList;
    for (auto &s: easy) {
        std::stringstream ss(s);
        std::string temp;
        vector<int> tempVec;
        while (ss >> temp) {
            tempVec.push_back(std::stoi(temp));
        }
        tempList.push_back(tempVec);
    }

    for (auto &i: tempList) {
        board[i[0]][i[1]]->SetDeterminedNum(i[2]);
    }

//    puzzle_file.close();
}

void MainWindow::on_hard_puzzle_clicked() {
    info->setText("");
    path = "";

    determinedList = {};
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j]->SetUndetermined();
            board[i][j]->SetIsFixed(false);
            board[i][j]->setDeterminedNum(-1);
        }
    }
//    string filename("puzzle2.pz");
    vector<string> lines;
    string line;

//    ifstream puzzle_file(filename);

    vector<vector<int>> tempList;
    for (auto &s: hard) {
        std::stringstream ss(s);
        std::string temp;
        vector<int> tempVec;
        while (ss >> temp) {
            tempVec.push_back(std::stoi(temp));
        }
        tempList.push_back(tempVec);
    }

    for (auto &i: tempList) {
        board[i[0]][i[1]]->SetDeterminedNum(i[2]);
    }

    for (auto &i: tempList) {
        board[i[0]][i[1]]->SetDeterminedNum(i[2]);
    }

//    puzzle_file.close();
}

void MainWindow::on_next_clicked() {
    board1 = Board(determinedList);

    if (determinedList.size() == 81) {
        return;
    }
    Message message = board1.run();

    if (message.type == "invalid") {
        QMessageBox::information(this, "警告", "数独非法");
    } else if (message.type == "idk") {
        QMessageBox::information(this, "说明", "数独信息不够或者我太弱了，等我变强一点。");
    } else {
        determinedList.push_back({message.message[0], message.message[1], message.message[2]});
        board[message.message[0]][message.message[1]]->SetDeterminedNum(message.message[2]);
        path += message.type;
        info->setText(QString::fromStdString(path));
    }

    if (determinedList.size() == 81) {
        QMessageBox::information(this, "完成", "太厉害了。");
    }
}

void MainWindow::on_begin_clicked() {
    path = "";
    info->setText("");
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j]->getDeterminedNum() > 0) {
                board[i][j]->SetFixedNum();
                determinedList.push_back({i, j, board[i][j]->getDeterminedNum()});
            }
        }
    }
    board1 = Board(determinedList);
    if (!board1.IsValid()) {
        QMessageBox::information(this, "警告", "数独非法");
    }
}

void MainWindow::on_setting_clicked() {
    QMessageBox::information(this, "说明", "该软件可以按步骤给出数独求解方案。\n\n"
                                         "点击自定义游戏可以自己创建数独，双击小数字来选择对应数字，再次双击可取消。"
                                         "点击开始游戏即可开始，点击下一步即可给出一步的提示。\n\n"
                                         "点击谜题，软件内部自带了两个的数独。\n\n"
                                         "一些功能尚在学习中，因此可能无法求解一些较难的数独。");
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget::mouseDoubleClickEvent(event);
    board1 = Board(determinedList);
    if (!board1.IsValid()) {
        board[determinedList.back()[0]][determinedList.back()[1]]->setStyleSheet(CellWidget::invalidStyle);
    }
    if (board1.IsValid() && determinedList.size() == 81) {
        QMessageBox::information(this, "完成", "太厉害了。");
    }
}

void MainWindow::add_num(vector<int> numVec) {
    determinedList.push_back({numVec[0], numVec[1], numVec[2]});

}

void MainWindow::remove_num() {
    determinedList.pop_back();
}
