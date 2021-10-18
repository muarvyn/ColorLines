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

#include "mainwindow_test.h"
#include "../basic_defs.hpp"
#include "../swapboxlayout.h"
//#include "../intermediateitemlayout.h"

int getColor(const AnimatedIconButton *btn)
{
    return btn->getColumn();
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    for (BallColor::type color=BallColor::first; color < BallColor::first+3; ++color) {
        AnimatedIconButton *btn = new AnimatedIconButton(0,color,ballIcons,this);
        btn->setMaximumSize(QSize(80,80));
        btn->setColor(color);
        connect(btn, &AnimatedIconButton::clicked, this, &MainWindow::handleButtonClick);
        button_list.append(btn);
    }
    button_list[1]->setMaximumSize(QSize(600,600));

    setupLayout(QBoxLayout::LeftToRight);
}

void MainWindow::handleButtonClick()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    if (clickedButton->isAnimating()) {
        qDebug() << "Clicked button state at animation time: " << clickedButton->getState();
        clickedButton->stopAnimation();
        qDebug() << "Clicked button state immediately after animation stop: " << clickedButton->getState();
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
    AnimatedIconButton *senderButton = qobject_cast<AnimatedIconButton *>(sender());
    qDebug() << "Button animation has finished. State is : " << senderButton->getState();
    qDebug() << "AnimatedIconButton::isAnimating returned " << senderButton->isAnimating();
}
/*
void MainWindow::resizeEvent(QResizeEvent *e)
{
    QBoxLayout::Direction dir = e->size().width() > e->size().height() ?
        QBoxLayout::LeftToRight : QBoxLayout::TopToBottom;
    QWidget::resizeEvent(e);
}
*/
MainWindow::~MainWindow()
{
}

/*
TradeForSizeItem *newItem(QLayoutItem *i) {
    TradeForSizeItem* tfsi = new FixedAspectRatioItem(i);
    //qDebug() << "newItem: maximumsize = " << tfsi->maximumSize();
    tfsi->assignSize(QSize(160,160));
    return tfsi;
}
*/

void MainWindow::setupLayout(QBoxLayout::Direction dir)
{
    const Qt::Alignment alignment[3] =
        { Qt::AlignHCenter | Qt::AlignBottom, Qt::AlignCenter, Qt::AlignHCenter | Qt::AlignTop };

    SwapBoxLayout *swap_box = new SwapBoxLayout(SwappableLayout::Vertical, this);
    swap_box->addStretch(1);
    swap_box->setAlignment(Qt::AlignCenter);
    setLayout(swap_box);

    int i = 0;
    for (AnimatedIconButton *btn : qAsConst(button_list)) {
        swap_box->addWidget(btn);
        swap_box->setAlignment(btn, alignment[i]);
        i++;
    }
    setLayout(swap_box);
}

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
