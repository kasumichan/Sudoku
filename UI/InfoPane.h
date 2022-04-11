//
// Created by 16000 on 2022/4/10.
//

#ifndef SUDOKU_INFOPANE_H
#define SUDOKU_INFOPANE_H

#include <QVBoxLayout>
#include <QLabel>
#include <string>
using std::string;

class InfoPane : public QWidget {
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
    explicit InfoPane(QWidget *parent = nullptr);
};


#endif //SUDOKU_INFOPANE_H
