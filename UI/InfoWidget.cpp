//
// Created by 16000 on 2022/4/10.
//

#include "InfoWidget.h"
#include <QScrollArea>

InfoWidget::InfoWidget(QWidget *parent) : QWidget(parent) {
    info = new QLabel(this);
    info->setText("路径提示");
//    info->setAlignment(Qt::AlignCenter);

    tipPanel = new QLabel(this);
    info->setFixedWidth(400);
    tipPanel->setAlignment(Qt::AlignTop);
    tipPanel->setFrameShape(QFrame::Box);
    tipPanel->setWordWrap(true);
    tipPanel->setFrameShadow(QFrame::Raised);

    tipPanel->setStyleSheet(
            "border-width: 1px;border-style: solid;border-color: rgb(0, 0, 0);background-color: rgb(255, 255, 255);");


    auto *layout = new QVBoxLayout;
    layout->addWidget(info);
    auto *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    tipPanel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    tipPanel->setScaledContents(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidget(tipPanel);
    layout->addWidget(scrollArea);
    setLayout(layout);
}

const string &InfoWidget::getPath() const {
    return path;
}

void InfoWidget::setPath(const string &path) {
    InfoWidget::path = path;
    tipPanel->setText(QString::fromStdString(path));
}
