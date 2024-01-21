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
#include "mainwindow_swaplayout_test.h"
#include "../swaplayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)

{
    swap_grid = new SwapLayout(SwapLayout::Vertical, this);
    setLayout(swap_grid);
    CustomToolButton *btn;
    for (int i = 0; i < 3; ++i) {
        btn = new CustomToolButton(this);
        btn->setText(QString::number(i+1));
        btn->setMaximumSize(QSize(80,80));
        swap_grid->addWidget(btn);
    }
    connect(btn, &CustomToolButton::clicked, this, &MainWindow::handleButtonClick);
}

void MainWindow::handleButtonClick()
{
    swap_grid->setOrientation(SwapLayout::transpose(swap_grid->getOrientation()));
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
