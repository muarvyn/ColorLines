/*

Copyright (C) 2020-2021 Volodymyr Kryachko

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
#include "mainwindow_layout_test.h"
#include "../fixedaspectratioitem2.h"
#include "../swappablelayout.h"

static const Qt::Alignment local_alignments[]=
{
    Qt::AlignRight|Qt::AlignBottom,
    Qt::AlignCenter,
    Qt::AlignLeft|Qt::AlignTop
};

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , first_item(new SwapLayout(SwapLayout::Horizontal))
    , last_item(new SwapLayout(SwapLayout::Horizontal))
    , main_layout(new SwappableLayout)
{
    first_item->addWidget(new QLabel("Hello"), local_alignments[0]);
    first_item->addWidget(new QLabel("World"), local_alignments[2]);
    for (int i = 0; i < 3; ++i) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setText(QString::number(i+1));
        btn->setMaximumSize(QSize(80,80));
        last_item->addWidget(btn, local_alignments[i]);
    }
    QToolButton *btn = new CustomToolButton(this);
    btn->setMaximumSize(QSize(400,400));

    main_layout->addLayout(first_item);
    main_layout->addWidget(btn);
    connect(btn, &CustomToolButton::clicked, this, &MainWindow::handleButtonClick);
    main_layout->addLayout(last_item);
    setLayout(main_layout);
}

void MainWindow::handleButtonClick()
{
    main_layout->setOrientation(SwapLayout::Swapped);
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
