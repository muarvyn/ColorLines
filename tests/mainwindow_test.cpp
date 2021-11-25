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
#include "../tradeforsizeroot.h"
#include "../aspectratioitem.h"

int getColor(const AnimatedIconButton *btn)
{
    return btn->getColumn();
}

TradeForSizeItem *newItem(QLayoutItem *i, TradeForSizeItem::InvalidateFunc invalidate_func)
{
    TradeForSizeItem* tfsi = new AspectRatioItem(i, invalidate_func, 1.0);
    return tfsi;
}

AnimatedIconButton *newButton(int r, int c, QIcon *ic, QWidget *parent)
{
    AnimatedIconButton *btn = new AnimatedIconButton(r, c, ic, parent);
    btn->setMaximumSize(120,120);
    return btn;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }

    setCentralWidget(new QWidget(this));
    QMenuBar *menubar = new QMenuBar(this);
    menubar->setGeometry(QRect(0, 0, 615, 22));
    QMenu *menuDo = new QMenu(tr("&Do"), menubar);
    setMenuBar(menubar);

    menubar->addAction(menuDo->menuAction());
    QAction *actionSwap = new QAction(tr("&Swap"),this);
    menuDo->addAction(actionSwap);
    connect(actionSwap, &QAction::triggered, this, &MainWindow::swap);

    main_layout = new TradeForSizeRoot<SwapBoxLayout>(SwappableLayout::Vertical);

    TradeForSizeLayout<QHBoxLayout> *labels_layout = new TradeForSizeLayout<QHBoxLayout>();
    labels_layout->addStretch(1);
    for (int i = 3; i; --i) {
        QLabel *nextLab = new QLabel();
        nextLab->setAlignment(Qt::AlignCenter);
        nextLab->setScaledContents(true);
        nextLab->setMinimumSize(QSize(40,40));
        nextLab->setMaximumSize(QSize(80,80));
        QIcon *ic = &ballIcons[BallColor::last-i];
        nextLab->setPixmap(ic->pixmap(ic->availableSizes()[0]));
        labels_layout->addWidget<TradeForSizeItem::InvalidateFunc>(
                    nextLab,
                    newItem,
                    [this]() { main_layout->invalidateGeom(); }
        );
    }
    labels_layout->addStretch(1);

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(newButton(0, 0, ballIcons, centralWidget()), 0,0);
    grid->addWidget(newButton(0, 1, ballIcons+1, centralWidget()), 0,1);
    grid->addWidget(newButton(1, 0, ballIcons+2, centralWidget()), 1,0);
    grid->addWidget(newButton(1, 1, ballIcons+3, centralWidget()), 1,1);

    TradeForSizeLayout<SwapBoxLayout> *toolbar =
            new TradeForSizeLayout<SwapBoxLayout>(SwappableLayout::Horizontal);

    toolbar->addStretch(1);
    for (BallColor::type color=BallColor::first; color < BallColor::first+3; ++color) {
        AnimatedIconButton *btn = new AnimatedIconButton(0,color,ballIcons,centralWidget());
        btn->setMaximumSize(QSize(80,80));
        btn->setColor(color);
        connect(btn, &AnimatedIconButton::clicked, this, &MainWindow::handleButtonClick);
        button_list.append(btn);
        toolbar->addWidget<TradeForSizeItem::InvalidateFunc>(
                    btn,
                    newItem,
                    [this]() { main_layout->invalidateGeom(); });
    }
    toolbar->addStretch(1);

    main_layout->addLayout(labels_layout);
    main_layout->setAlignment(labels_layout, Qt::AlignCenter);
    main_layout->addItem(new AspectRatioItem(
                             grid,
                             [this](){ main_layout->invalidateGeom(); },
                             1.0f));
    main_layout->addSwappable(toolbar);
    centralWidget()->setLayout(main_layout);
}

void MainWindow::swap()
{
    main_layout->setOrientation(SwappableLayout::Swapped);
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
