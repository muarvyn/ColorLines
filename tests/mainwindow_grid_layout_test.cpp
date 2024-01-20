/*

Copyright (C) 2024 Volodymyr Kryachko

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
#include <QDebug>
#include <QSize>

#include "mainwindow_grid_layout_test.h"
#include "transposablebutton.h"

const QPoint MainWindow::center;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , grid_layout(new QGridLayout())
{
    QSizePolicy sp1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sp1.setHeightForWidth(true);
    sp1.setWidthForHeight(true);
    sp1.setHorizontalStretch(1);
    sp1.setVerticalStretch(1);
    TransposableButton *btn;
    for (int i = 0; i < 3; ++i) {
        btn = new TransposableButton(this);
        btn->setText(QString::number(i+1));
        grid_layout->addWidget(btn, (i+1)/2, (i+1)%2);
    }
    QToolButton *central = new QToolButton();
    central->setMaximumSize(QSize(640,640));
    grid_layout->addWidget(central, 1, 1);

    setLayout(grid_layout);
}

// teke it from layout/util.cpp
void setupCenterLayout(QGridLayout &grid_layout, const QPoint center, const QSize &size);

void MainWindow::resizeEvent(QResizeEvent *e)
{
    setupCenterLayout(*grid_layout, center, e->size());
    QWidget::resizeEvent(e);
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
