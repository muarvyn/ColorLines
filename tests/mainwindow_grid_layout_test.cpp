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
    central->setMaximumSize(QSize(420,420));
    grid_layout->addWidget(central, 1, 1);

    //setupLayout(QBoxLayout::LeftToRight);
    setLayout(grid_layout);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    setupLayout(e->size());
    QWidget::resizeEvent(e);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupLayout(const QSize &size)
{
    auto secondary_size = QSize();
    auto widgets = std::list<std::pair<QWidget*, SwappableLayout*>>();
    while (grid_layout->count()) {
        auto widget = grid_layout->itemAt(0)->widget();
        SwappableLayout *item = dynamic_cast<SwappableLayout*>(widget);
        if (item) secondary_size += item->getMinimumSize();
        widgets.push_back(std::make_pair(widget, item));
        grid_layout->removeWidget(widget);
    }

    auto f = (size.width() - size.height() + secondary_size.height())
            /float(secondary_size.height() + secondary_size.width());
    auto width = 0;
    auto col = 0, row = 0;
    qDebug() << "secondary_size=" << secondary_size << " factor=" << f;
    auto is_horizontal = true;
    for (auto item : widgets) {
        if (!item.second) {
            grid_layout->addWidget(item.first, 1, 1);
            continue;
        }
        is_horizontal = is_horizontal &&
            (width + item.second->getMinimumSize().width()/2.0) < f*secondary_size.width();
        if (is_horizontal) {
            grid_layout->addWidget(item.first, 1, col);
            width += item.second->getMinimumSize().width();
            qDebug() << "Adding at " << "1 " << col << " width=" << width;
            item.second->setOrientation(SwappableLayout::Horizontal);
            col++;
            if (col == 1) col++;
        } else {
            grid_layout->addWidget(item.first, row, 1);
            qDebug() << "Adding at " << row << " 1";
            item.second->setOrientation(SwappableLayout::Vertical);
            row++;
            if (row == 1) row++;
        }
    }
    grid_layout->setRowStretch(0, 1);
    grid_layout->setRowStretch(1, 10);
    grid_layout->setRowStretch(2, 1);
    grid_layout->setRowStretch(3, 1);
    grid_layout->setColumnStretch(0, 1);
    grid_layout->setColumnStretch(1, 10);
    grid_layout->setColumnStretch(2, 1);
    grid_layout->setColumnStretch(3, 1);
}

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
