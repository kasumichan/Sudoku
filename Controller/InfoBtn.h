//
// Created by 16000 on 2022/4/11.
//

#ifndef SUDOKU_INFOBTN_H
#define SUDOKU_INFOBTN_H

#include <QPushButton>
#include <vector>
#include "../Message/CellStruct.h"
#include "../Puzzle/Puzzle.h"
#include "../Message/PuzzleDegree.h"

using std::vector;
using std::string;

class InfoBtn : public QPushButton {
Q_OBJECT
private:
    int level;
    PuzzleDegree degree;
public:
    int getLevel() const;

    void setLevel(int level);

    PuzzleDegree getDegree() const;

    void setDegree(PuzzleDegree degree);

    vector<CellStruct> readData();

public:
    explicit InfoBtn(PuzzleDegree degree = PuzzleDegree::EASY, QWidget *parent = nullptr);

protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:

    void sendLevel(int level);

    void sendCellData(vector<CellStruct>);

};


#endif //SUDOKU_INFOBTN_H
