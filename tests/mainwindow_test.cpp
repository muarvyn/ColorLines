/*

Copyright (C) 2020 Volodymyr Kryachko

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

#include "mainwindow_test.h"
#include "ui_mainwindow_test.h"
#include "../basic_defs.hpp"
#include "../animatediconbutton.h"

int getColor(const AnimatedIconButton *btn)
{
    return btn->getColumn();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }

    QGridLayout *grid = ui->gridLayout;
    for (BallColor::type color=BallColor::first; color < BallColor::first+3; ++color) {
        AnimatedIconButton *btn = new AnimatedIconButton(0,color,ballIcons,this);
        btn->setColor(color);
        grid->addWidget(btn, btn->getRow(), btn->getColumn());
        connect(btn, &AnimatedIconButton::clicked, this, &MainWindow::handleButtonClick);
    }
}

void MainWindow::handleButtonClick()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    if (clickedButton->isAnimating()) {
        clickedButton->stopAnimation();
    } else if (clickedButton->getState()==AnimatedIconButton::UNOCCUPIED) {
        int st = getColor(clickedButton);
        clickedButton->setupAnimation("opacity", 0, 1, 600, st);
        clickedButton->startAnimation(st);
    } else {
        clickedButton->setupAnimation("iconSize", clickedButton->size(), QSize(5,5),
            600, AnimatedIconButton::UNOCCUPIED);
        clickedButton->startAnimation(clickedButton->getState());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

