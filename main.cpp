#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <QApplication>
#include "Board.h"
#include "UI/MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {


    QApplication a(argc, argv);
    MainWindow w;

    w.setGeometry(200, 100,800,600);

    w.show();

    return a.exec();
}
