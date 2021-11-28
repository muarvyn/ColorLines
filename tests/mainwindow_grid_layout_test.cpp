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
#include <QDebug>

#include "mainwindow_grid_layout_test.h"
#include "../basic_defs.hpp"
#include "../fixedaspectratioitem.h"
#include "testwidgetitem.h"

int getColor(const AnimatedIconButton *btn)
{
    return btn->getColumn();
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , main_layout(new QBoxLayout(QBoxLayout::LeftToRight, this))
{
    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }

    QSizePolicy sp1(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sp1.setHeightForWidth(true);
    sp1.setWidthForHeight(true);
    sp1.setHorizontalStretch(1);
    sp1.setVerticalStretch(1);
//    const QSizePolicy sp2(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    const QSizePolicy sp1(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QSizePolicy sp2(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp2.setHeightForWidth(true);
    sp2.setWidthForHeight(true);
    sp2.setHorizontalStretch(10);
    sp2.setVerticalStretch(10);
    for (BallColor::type color=BallColor::first; color < BallColor::first+3; ++color) {
        AnimatedIconButton *btn = new AnimatedIconButton(0,color,ballIcons,this);
        btn->setColor(color);
        if (color == BallColor::red) {
            btn->setSizePolicy(sp2);
        } else {
            btn->setSizePolicy(sp2);
        }
        connect(btn, &AnimatedIconButton::clicked, this, &MainWindow::handleButtonClick);
        button_list.append(btn);
    }

    QGridLayout *box = new QGridLayout(this);

    box->addItem(new FixedAspectRatioItem(button_list[0]), 1, 0);
    TestWidgetItem *item = new TestWidgetItem(box);
    item->setCentralWidget(button_list[1]);
    box->addItem(item->getCentralItem(), 0, 1, 3, 3);
    box->addItem(new FixedAspectRatioItem(button_list[2]), 1, 4);

    //setupLayout(QBoxLayout::LeftToRight);
    main_layout->addItem(item);
    setLayout(main_layout);
}

void MainWindow::handleButtonClick()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    if (clickedButton->isAnimating()) {
        clickedButton->stopAnimation();
    } else if (clickedButton->getState()==AnimatedIconButton::UNOCCUPIED) {
        int st = getColor(clickedButton);
        clickedButton->setupAnimation("opacity", 0, 1, 600);
        clickedButton->startAnimation(st, st);
        connect(clickedButton, &AnimatedIconButton::animation_finished,
                this, &MainWindow::handleAnimationFinished);
    } else {
        int anim_st = clickedButton->getState();
        clickedButton->setupAnimation("iconSize", clickedButton->size(), QSize(5,5), 600);
        clickedButton->startAnimation(anim_st, AnimatedIconButton::UNOCCUPIED);
        connect(clickedButton, &AnimatedIconButton::animation_finished,
                this, &MainWindow::handleAnimationFinished);
    }
}

void MainWindow::handleAnimationFinished()
{
    //AnimatedIconButton *senderButton = qobject_cast<AnimatedIconButton *>(sender());
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QBoxLayout::Direction dir = e->size().width() > e->size().height() ?
        QBoxLayout::LeftToRight : QBoxLayout::TopToBottom;
    setupLayout(dir);
    QWidget::resizeEvent(e);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupLayout(QBoxLayout::Direction dir)
{
    if (main_layout->direction() == dir) return;
}
