#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <QApplication>
#include <QDebug>
#include "Game/BoardData.h"
#include "windows.h"
#include "UI/MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    QApplication a(argc, argv);
    QFile qss("Resources/Diffnes.qss");
    if (qss.open(QFile::ReadOnly)) {
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    MainWindow w;
    QIcon qIcon("Resources/icon/sudoku.ico");
//    if()
    w.setWindowIcon(qIcon);
//    a.setWindowIcon(qIcon);
    w.setGeometry(200, 100, 800, 600);

    w.show();

    return a.exec();
}
