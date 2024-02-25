/*

Copyright (C) 2020-2024 Volodymyr Kryachko

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
#include "../layout/transposable.h"
#include "../layout/transposableboxlayout.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , grid_layout(new QGridLayout())
    , first_item(new TransposableBoxLayout(Transposable::Horizontal))
    , last_item(new TransposableBoxLayout(Transposable::Horizontal))
{
    auto space = new QWidget();
    space->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    grid_layout->addWidget(space);
    first_item->addStretch(1);
    auto lab = new QLabel("Hello");
    lab->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    first_item->addWidget(lab);
    lab = new QLabel("World");
    lab->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    first_item->addWidget(lab);
    first_item->addStretch(1);
    grid_layout->addLayout(first_item, 1, 0);

    setupButtons(*last_item);
    grid_layout->addLayout(last_item, 1, 1);
    CustomToolButton *btn = new CustomToolButton(this);
    btn->setText("Center");
    btn->setSizeHint(QSize(300,300));
    btn->setMaximumSize(QSize(620,620));
    grid_layout->addWidget(btn);
    grid_layout->addWidget(new QWidget());

    setLayout(grid_layout);
}

void MainWindow::setupButtons(TransposableBoxLayout &swap_box) {
    const QString str[] = {"nothing", "switch", "swap"};
    swap_box.addStretch(1);
    swap_box.setAlignment(Qt::AlignCenter);
    CustomToolButton *btn;
    for (int i = 0; i < 3; ++i) {
        btn = new CustomToolButton(this);
        btn->setText(str[i]);
        btn->setMaximumSize(QSize(80,80));
        swap_box.addWidget(btn);
    }
    swap_box.addStretch(1);
}

MainWindow::~MainWindow()
{
}

// teke it from layout/util.cpp
void setupCenterLayout(QGridLayout &grid_layout, const QPoint center, const QSize &size);

void MainWindow::resizeEvent(QResizeEvent *e)
{
    setupCenterLayout(*grid_layout, QPoint(1,1), e->size());
    QWidget::resizeEvent(e);
}

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
