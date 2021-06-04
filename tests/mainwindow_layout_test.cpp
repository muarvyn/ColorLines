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
#include "../centralitemlayout.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    CentralItemLayout<QVBoxLayout> *v_layout = new CentralItemLayout<QVBoxLayout>();

    QHBoxLayout *h_layout = new QHBoxLayout();
    //h_layout->setDirection(QBoxLayout::LeftToRight);
    QSizePolicy size_policy = QSizePolicy(QSizePolicy::Maximum,
                                          QSizePolicy::Maximum,
                                          QSizePolicy::ToolButton);
//    QSizePolicy size_policy = QSizePolicy(QSizePolicy::MinimumExpanding,
//                                          QSizePolicy::MinimumExpanding,
//                                          QSizePolicy::ToolButton);
    QSizePolicy size_policy_central = QSizePolicy(QSizePolicy::MinimumExpanding,
                                          QSizePolicy::MinimumExpanding,
                                          QSizePolicy::ToolButton);
    h_layout->addStretch(1);
    QToolButton *btn = new CustomToolButton(this);
    btn->setArrowType(Qt::LeftArrow);
    btn->setSizePolicy(size_policy);
    h_layout->addItem(new FixedAspectRatioItem(btn));
    h_layout->setStretch(h_layout->count()-1,10);

    btn = new CustomToolButton(this);
    btn->setSizePolicy(size_policy_central);
    h_layout->addItem(new FixedAspectRatioItem(btn));
    h_layout->setStretch(h_layout->count()-1,100);

    btn = new CustomToolButton(this);
    btn->setSizePolicy(size_policy);
    btn->setArrowType(Qt::RightArrow);

    h_layout->addItem(new FixedAspectRatioItem(btn));
    h_layout->setStretch(h_layout->count()-1,10);
    h_layout->addStretch(1);

    v_layout->addStretch(1);
    btn = new CustomToolButton(this);
    btn->setArrowType(Qt::UpArrow);

    v_layout->addWidget(btn);
    v_layout->setAlignment(btn, Qt::AlignHCenter | Qt::AlignBottom);
    v_layout->addCentralLayout(h_layout);
    //v_layout->setStretch(v_layout->count()-1, 100);
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

