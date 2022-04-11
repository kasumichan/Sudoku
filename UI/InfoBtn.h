//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_INFOBTN_H
#define SUDOKU_INFOBTN_H

#include <QPushButton>
#include <vector>
#include "../CellData.h"
#include "../Puzzle/Puzzle.h"

using std::vector;
using std::string;

class InfoBtn : public QPushButton {
Q_OBJECT
private:
    int level;
    string degree;
public:
    int getLevel() const;

    void setLevel(int level);

    const string &getDegree() const;

    void setDegree(const string &degree);

    vector<CellData> readData();
public:
    explicit InfoBtn(const QString &text, string degree = "", QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *e) override;

signals:

    void sendLevel(int level);

    void sendCellData(vector<CellData>);

};


#endif //SUDOKU_INFOBTN_H
