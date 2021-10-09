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
#include "mainwindow_fixed_test.h"
#include "../intermediateitemlayout.h"
#include "../fixedaspectratioitem2.h"

TradeForSizeItem *newItem(QLayoutItem *i) {
    TradeForSizeItem* tfsi = new TradeForSizeItem(i); //new FixedAspectRatioItem(i);
    tfsi->assignSize(QSize(120,120));
    return tfsi;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    const QSizePolicy sp1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    const QString name[3] = {"up", "center", "down"};

    for (int i = 0; i < 3; ++i) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setObjectName(name[i]);
        btn->setMaximumSize(QSize(80,80));
        btn->setSizePolicy(sp1);
        button_list.append(btn);
    }
    button_list[0]->setArrowType(Qt::UpArrow);
    button_list[2]->setArrowType(Qt::DownArrow);

    setupLayout();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupLayout()
{
    const Qt::Alignment al[3] =
        { Qt::AlignVCenter | Qt::AlignRight, Qt::AlignCenter, Qt::AlignVCenter | Qt::AlignLeft };
    IntermediateItemLayout<QBoxLayout> *box_layout = new IntermediateItemLayout<QBoxLayout>();

    box_layout->addStretch(1);
    int i = 0;
    for (CustomToolButton *btn : qAsConst(button_list)) {
        box_layout->addWidget(btn, newItem);
        box_layout->setAlignment(btn, al[i]);
        ++i;
    }
    box_layout->addStretch(1);
    setLayout(box_layout);
}

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
