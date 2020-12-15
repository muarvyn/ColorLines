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

#include "customtoolbutton.h"
#include "mainwindow_layout_test.h"
#include "../fixedaspectratioitem.h"
#include "testwidgetitem.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QBoxLayout *v_layout = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::LeftToRight);
    QSizePolicy size_policy = QSizePolicy(QSizePolicy::Maximum,
                                          QSizePolicy::Maximum,
                                          QSizePolicy::ToolButton);
//    QSizePolicy size_policy = QSizePolicy(QSizePolicy::MinimumExpanding,
//                                          QSizePolicy::MinimumExpanding,
//                                          QSizePolicy::ToolButton);
    QSizePolicy size_policy_central = QSizePolicy(QSizePolicy::MinimumExpanding,
                                          QSizePolicy::MinimumExpanding,
                                          QSizePolicy::ToolButton);
    layout->addStretch(1);
    QAbstractButton *btn = new CustomToolButton(this);
    btn->setSizePolicy(size_policy);
    //layout->addWidget(btn);
    layout->addItem(new FixedAspectRatioItem(btn));
    layout->setStretch(layout->count(),1);

    btn = new CustomToolButton(this);
    btn->setSizePolicy(size_policy_central);
    TestWidgetItem *item = new TestWidgetItem(layout);
    item->addCentralWidget(btn);
    layout->setStretch(layout->count(),10);

    btn = new CustomToolButton(this);
    btn->setSizePolicy(size_policy);
//    layout->addWidget(btn);
    layout->addItem(new FixedAspectRatioItem(btn));
    layout->setStretch(layout->count(),1);
    layout->addStretch(1);

    //v_layout->addStretch(1);
    v_layout->addItem(item);
    //v_layout->addStretch(1);

    setLayout(v_layout);
}

MainWindow::~MainWindow()
{
}

