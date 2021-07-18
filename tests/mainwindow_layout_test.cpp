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
#include "../centralitemlayout.h"

TradeForSizeItem *newItem(QLayoutItem *i) {
    TradeForSizeItem* tfsi = new FixedAspectRatioItem(i, 1.0f);
    tfsi->assignSize(QSize(120,120));
    return tfsi;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *toolbar_layout = new QGridLayout();
    for (int i = 0; i < 3; ++i) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setText(QString::number(i+1));
        btn->setMaximumSize(QSize(80,80));
        toolbutton_list.append(btn);
        toolbar_layout->addWidget(btn, 0, i);
    }

    CentralItemLayout<QVBoxLayout> *v_layout = new CentralItemLayout<QVBoxLayout>();

    v_layout->addLayout(toolbar_layout);
    v_layout->setAlignment(toolbar_layout, Qt::AlignBottom | Qt::AlignHCenter);
    QToolButton *btn = new CustomToolButton(this);
    btn->setMaximumSize(QSize(400,400));
    v_layout->addCentralWidget(btn, newItem);

    btn = new CustomToolButton(this);
    btn->setArrowType(Qt::DownArrow);
    v_layout->addWidget(btn);
    v_layout->setAlignment(btn, Qt::AlignHCenter | Qt::AlignTop);

    v_layout->addStretch(1);

    setLayout(v_layout);
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
