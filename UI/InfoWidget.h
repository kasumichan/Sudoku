//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_INFOWIDGET_H
#define SUDOKU_INFOWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include <string>
using std::string;

class InfoWidget : public QWidget {
Q_OBJECT
private:
    string path;
public:
    const string &getPath() const;

    void setPath(const string &path);

private:
    QLabel *info;
    QLabel *tipPanel;

public:
    explicit InfoWidget(QWidget *parent = nullptr);
};


#endif //SUDOKU_INFOWIDGET_H
