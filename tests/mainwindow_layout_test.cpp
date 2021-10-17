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
#include "../swapboxlayout.h"
#include "../intermediateitemlayout.h"
#include "../aspectratioitem.h"

TradeForSizeItem *newItem(QLayoutItem *i, TradeForSizeItem::InvalidateFunc invalidate_func)
{
    TradeForSizeItem* tfsi = new AspectRatioItem(i, invalidate_func, 1.0, QSize(120,120));
    return tfsi;
}

TradeForSizeItem *newItem2(QLayoutItem *i,
                           TradeForSizeItem::InvalidateFunc invalidate_func,
                           QString n)
{
    TradeForSizeItem* tfsi = new AspectRatioItem(i, invalidate_func, 1.0, QSize(120,120));
    tfsi->setName(n);
    return tfsi;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , first_item(new MainLayout(SwappableLayout::Horizontal))
    , last_item(new MainLayout(SwappableLayout::Horizontal))
    , main_layout(new MainLayout(SwappableLayout::Vertical))
{
    first_item->addStretch(1);
    first_item->addWidget(new QLabel("Hello"));
    first_item->addWidget(new QLabel("World"));
    first_item->addStretch(1);

    last_item->addStretch(1);
    for (int i = 0; i < 3; ++i) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setText(QString::number(i+1));
        last_item->addWidget(btn); //, newItem);
    }
    last_item->addStretch(1);
    last_item->setObjectName("toolbar");
    QToolButton *btn = new CustomToolButton(this);
    btn->setMaximumSize(QSize(400,400));

    main_layout->setEnabled(false);
    main_layout->addStretch(1);
    main_layout->addSwappable(first_item);
    //btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    main_layout->addWidget(btn, newItem2, QString("Center"));
    assert(main_layout->setStretchFactor(btn, 30));
    // TODO: Why doesn't this work right?
    // main_layout->addWidget(btn, Qt::AlignCenter);
    connect(btn, &CustomToolButton::clicked, this, &MainWindow::handleButtonClick);
    main_layout->addSwappable(last_item);
    main_layout->setStretchFactor(last_item, 5);
    main_layout->addStretch(1);
    //main_layout->setObjectName("center");
    //main_layout->setAlignment(Qt::AlignCenter);

    setLayout(main_layout);
    main_layout->setEnabled(true);

}

void MainWindow::handleButtonClick()
{
    main_layout->setOrientation(SwappableLayout::Swapped);
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
