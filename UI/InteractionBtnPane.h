//
// Created by 16000 on 2022/4/13.
//

#ifndef SUDOKU_INTERACTIONBTNPANE_H
#define SUDOKU_INTERACTIONBTNPANE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include <QGridLayout>

class InteractionBtnPane : public QWidget {
Q_OBJECT
private:
    QPushButton *eraseBtn;
    QPushButton *noteBtn;
    QPushButton *hintBtn;

    QLabel *eraseLabel;
    QLabel *noteLabel;
    QLabel *hintLabel;
public:
    QPushButton *getEraseBtn() const;

    QPushButton *getNoteBtn() const;

    QPushButton *getHintBtn() const;

private:
    void initLayout();

    void setObjectName();

    void addListener();

public:
    explicit InteractionBtnPane(QWidget *parent = nullptr);

private slots:


signals:

    void hintClicked();

    void noteClicked();

    void eraseClicked();


};


#endif //SUDOKU_INTERACTIONBTNPANE_H
