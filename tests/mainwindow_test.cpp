/*

Copyright (C) 2020-2024 Volodymyr Kryachko

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

#include "mainwindow_test.h"
#include "../animatediconbutton.h"
#include "../layout/transposable.h"
#include "../layout/transposableboxlayout.h"

static
int getColor(const AnimatedIconButton *btn)
{
    return btn->getColumn();
}

static
AnimatedIconButton *newButton(int r, int c, QIcon *ic, QWidget *parent)
{
    AnimatedIconButton *btn = new AnimatedIconButton(r, c, ic, parent);
    btn->setMaximumSize(320,320);
    btn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    btn->setColor(BallColor::green);
    return btn;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , main_layout(new QGridLayout())
{
    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }

    TransposableBoxLayout *labels_layout = new TransposableBoxLayout(Transposable::Vertical);
    labels_layout->addStretch(1);
    for (int i = 3; i; --i) {
        QLabel *nextLab = new QLabel();
        nextLab->setAlignment(Qt::AlignCenter);
        nextLab->setScaledContents(true);
        nextLab->setMinimumSize(QSize(40,40));
        nextLab->setMaximumSize(QSize(80,80));
        QIcon *ic = &ballIcons[BallColor::colors_num-i];
        nextLab->setPixmap(ic->pixmap(ic->availableSizes()[0]));
        labels_layout->addWidget(nextLab);
    }
    labels_layout->addStretch(1);

    grid = new SizeHintGridLayout();
    grid->addWidget(newButton(0, 0, ballIcons, nullptr), 0,0);
    grid->addWidget(newButton(0, 1, ballIcons+1, nullptr), 0,1);
    grid->addWidget(newButton(1, 0, ballIcons+2, nullptr), 1,0);
    grid->addWidget(newButton(1, 1, ballIcons+3, nullptr), 1,1);

    TransposableBoxLayout *toolbar = new TransposableBoxLayout(Transposable::Horizontal);

    toolbar->addStretch(1);
    for (BallColor::type color=BallColor::first; color < BallColor::first+3; ++color) {
        AnimatedIconButton *btn = new AnimatedIconButton(0, color, ballIcons, nullptr);
        btn->setMaximumSize(QSize(80,80));
        btn->setColor(color);
        connect(btn, &AnimatedIconButton::clicked, this, &MainWindow::handleButtonClick);
        button_list.append(btn);
        toolbar->addWidget(btn);
    }
    toolbar->addStretch(1);

    main_layout->addLayout(labels_layout, 0, 0);
    main_layout->setAlignment(labels_layout, Qt::AlignCenter);
    main_layout->addLayout(grid, 0, 1);
    main_layout->addLayout(toolbar, 1, 0);
    setLayout(main_layout);
}

// take it from layout/util.cpp
void setupCenterLayoutItems(QGridLayout &grid_layout, const QPoint c, const QSize &size);

void MainWindow::resizeEvent(QResizeEvent *e)
{
    auto m = std::min(e->size().width(), e->size().height());
    auto s = QSize(m,m).boundedTo(grid->maximumSize());
    qDebug() << "new hint size=" << s;
    grid->setSizeHint(s);

    setupCenterLayoutItems(*main_layout, QPoint(1,1), e->size());
    QWidget::resizeEvent(e);
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
