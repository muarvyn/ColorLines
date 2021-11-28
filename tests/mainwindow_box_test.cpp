/*

Copyright (C) 2021 Volodymyr Kryachko

This file is part of ColorLines.

ColorLines is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

ColorLines is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with ColorLines; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#include <QtWidgets>

#include "customtoolbutton.h"
#include "mainwindow_box_test.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , first_item(new QBoxLayout(QBoxLayout::LeftToRight))
    , last_item(new QBoxLayout(QBoxLayout::LeftToRight))
    , main_layout(new QBoxLayout(QBoxLayout::TopToBottom))
{
    first_item->addStretch(1);
    first_item->addWidget(new QLabel("Hello"));
    first_item->addWidget(new QLabel("World"));
    first_item->addStretch(1);

    last_item->addStretch(1);
    for (int i = 0; i < 3; ++i) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setText(QString::number(i+1));
        last_item->addWidget(btn);
    }
    last_item->addStretch(1);
    QToolButton *btn = new CustomToolButton(this);
    btn->setMaximumSize(QSize(200,200));

    main_layout->setEnabled(false);
    main_layout->addStretch(1);
    main_layout->addLayout(first_item);
    main_layout->addWidget(btn, 30);
    connect(btn, &CustomToolButton::clicked, this, &MainWindow::handleButtonClick);
    main_layout->addLayout(last_item, 10);
    main_layout->addStretch(1);
    main_layout->setAlignment(Qt::AlignCenter);

    setLayout(main_layout);
    main_layout->setEnabled(true);

}

void MainWindow::handleButtonClick()
{
    main_layout->setDirection(main_layout->direction() == QBoxLayout::LeftToRight ?
                               QBoxLayout::TopToBottom : QBoxLayout::LeftToRight);
}

MainWindow::~MainWindow()
{
}

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
