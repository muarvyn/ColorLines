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

#include "customtoolbutton.h"
#include "mainwindow_swapboxlayout_test.h"
#include "../layout/transposableboxlayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , swap_box(new TransposableBoxLayout(Transposable::Vertical, this))
{
    const QString str[] = {"nothing", "switch", "swap"};
    swap_box->addStretch(1);
    swap_box->setAlignment(Qt::AlignCenter);
    setLayout(swap_box);
    CustomToolButton *btn;
    for (int i = 0; i < 3; ++i) {
        btn = new CustomToolButton(this);
        btn->setText(str[i]);
        btn->setMaximumSize(QSize(80,80));
        swap_box->addWidget(btn);
    }
    swap_box->addStretch(1);
    connect(btn, &CustomToolButton::clicked, this, &MainWindow::swapLayout);
}

void MainWindow::swapLayout()
{
    swap_box->setOrientation(Transposable::transpose(swap_box->getOrientation()));
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
