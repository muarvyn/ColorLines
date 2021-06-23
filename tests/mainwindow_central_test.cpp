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
#include "mainwindow_central_test.h"
#include "../centralitemlayout.h"
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
    for (int i = 0; i < 3; ++i) {
        CustomToolButton *btn = new CustomToolButton(this);
        btn->setMaximumSize(QSize(80,80));
        btn->setSizePolicy(sp1);
        button_list.append(btn);
    }
    button_list[1]->setMaximumSize(QSize(600,600));
    button_list[0]->setArrowType(Qt::UpArrow);
    button_list[2]->setArrowType(Qt::DownArrow);

    setupLayout(QBoxLayout::LeftToRight);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QBoxLayout::Direction dir = e->size().width() > e->size().height() ?
        QBoxLayout::LeftToRight : QBoxLayout::TopToBottom;
    setupLayout(dir);
    QWidget::resizeEvent(e);
}

void MainWindow::setupLayout(QBoxLayout::Direction dir)
{
    if (layout()) {
        QBoxLayout::Direction old_dir = qobject_cast<QBoxLayout *>(layout())->direction();
        if (old_dir == dir) return;
        delete layout();
    }
    const Qt::Alignment alignment[2][3] = {
        { Qt::AlignHCenter | Qt::AlignBottom, Qt::AlignCenter, Qt::AlignHCenter | Qt::AlignTop },
        { Qt::AlignVCenter | Qt::AlignRight, Qt::AlignCenter, Qt::AlignVCenter | Qt::AlignLeft }
    };
    const Qt::Alignment *al;
    CentralItemLayout<QBoxLayout> *box_layout = nullptr;
    if (dir == QBoxLayout::LeftToRight) {
        box_layout = (CentralItemLayout<QBoxLayout> *) new CentralItemLayout<QHBoxLayout>();
        al = alignment[1];
    } else {
        box_layout = (CentralItemLayout<QBoxLayout> *) new CentralItemLayout<QVBoxLayout>();
        al = alignment[0];
    }

    int i = 0;
    for (CustomToolButton *btn : qAsConst(button_list)) {
        if (i != 1) {
            box_layout->addWidget(btn);
            box_layout->setAlignment(btn, al[i]);
        } else {
            //qDebug() << "MainWindow::setupLayout: btn->maximumSize = " << btn->maximumSize();
            box_layout->addCentralWidget(btn, newItem);
            //qDebug() << "MainWindow::setupLayout: maximumSize = "
            //    << box_layout->itemAt(box_layout->count()-1)->maximumSize();
        }
        i++;
    }
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
