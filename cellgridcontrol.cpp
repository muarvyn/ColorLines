/*

Copyright (C) 2018-2020 Volodymyr Kryachko

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

#include "gamecontrol.h"
#include "animatediconbutton.h"
#include "cellgridcontrol.h"

CellGridControl::CellGridControl(
    int rows_num,
    int columns_num,
    addWidgetFunc addWidget,
    QWidget *parent
    )
    : QObject(parent)
    , boardCells(rows_num, std::vector<AnimatedIconButton*>(columns_num,nullptr))
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    movieLabel = new QLabel();
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
    movieLabel->setMovie(movie);

    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    for (std::size_t r = 0; r < boardCells.size(); ++r) {
        for (std::size_t c = 0; c < boardCells[r].size(); ++c) {
            boardCells[r][c] = createCell(r,c,parent);
            addWidget(boardCells[r][c], r, c);
        }
    }
}

BallColor::type CellGridControl::getColorAt(int r, int c) const
{
    return static_cast<BallColor::type>(boardCells[r][c]->getState());
}

void CellGridControl::setColorAt(int r, int c, BallColor::type color)
{
    boardCells[r][c]->setState(color);
}

void CellGridControl::clear()
{
    for (int r = 0; r < boardCells.size(); ++r) {
        for (int c = 0; c < boardCells[r].size(); ++c) {
            boardCells[r][c]->setState(BallColor::none);
        }
    }
}

AnimatedIconButton *CellGridControl::createCell(int r, int c, QWidget *parent)
{
    AnimatedIconButton * cell = new AnimatedIconButton(r,c,ballIcons,parent);
    cell->setMaximumSize(70,70);
    connect(cell, &AnimatedIconButton::clicked, this, &CellGridControl::handleCellClicked);
    return cell;
}

void CellGridControl::setButtonAnimation(CellButton &btn)
{
    movie->stop();
    if (btn.getState() == CellButton::UNOCCUPIED) return;
    movie->setFileName(QString(":/images/ball")+QString::number(btn.getState())+".gif");
    movieLabel->setParent(&btn);
    fitAnimationSize(btn.size());
    connect(&btn, &CellButton::resized, this, [this,&btn] { this->movieResized(&btn);} );
    movieLabel->show();
    movie->start();
}

void CellGridControl::movieResized(CellButton *btn)
{
    // just drop selection
    hideAnimation();
    disconnect(btn, &CellButton::resized,nullptr, nullptr);
}

void CellGridControl::hideAnimation()
{
    movie->stop();
    movieLabel->setParent(nullptr);
}

void CellGridControl::fitAnimationSize(QSize size)
{
    movieLabel->resize(size);
    movieLabel->setAutoFillBackground(false);
    movie->setScaledSize( movieLabel->frameSize()/movieScale);
}

void CellGridControl::startEliminationAnimation(AnimatedIconButton *btn)
{
    btn->setupAnimation("iconSize", btn->size(), QSize(5,5), 600);
    btn->startAnimation(btn->getState(), AnimatedIconButton::UNOCCUPIED);
}

void CellGridControl::handleCellClicked()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    emit userInput(clickedButton);
}

void CellGridControl::startDelayedAnimation(
    AnimatedIconButton *btn, int animated_state, int final_state, int delay)
{
    QTimer::singleShot(delay, btn,
        [btn, animated_state, final_state]{ btn->startAnimation(animated_state, final_state); });
}
