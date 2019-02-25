/*

Copyright (C) 2018 Volodymyr Kryachko

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

#include "gameboard.h"
#include "gamecontrol.h"
#include "animatediconbutton.h"
#include "cellgridcontrol.h"

CellGridControl::CellGridControl(
    int rows_num,
    int columns_num,
    QGridLayout *gridLayout,
    QObject *parent
    )
    : QObject(parent)
    , selectedCell(nullptr)
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
        c=static_cast<BallColor::type>(c+1)) //TOFIX: define operator++?
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    for (int r = 0; r < boardCells.size(); ++r) {
        for (int c = 0; c < boardCells[r].size(); ++c) {
            boardCells[r][c] = createCell(r,c);
            gridLayout->addWidget(boardCells[r][c], r, c);
        }
    }
    gridLayout->update();
}

BallColor::type CellGridControl::getColorAt(int r, int c) const
{
    return static_cast<BallColor::type>(boardCells[r][c]->getState());
}

void CellGridControl::setColorAt(int r, int c, BallColor::type color)
{
    boardCells[r][c]->setState(color);
}

AnimatedIconButton *CellGridControl::createCell(int r, int c)
{
    AnimatedIconButton * cell = new AnimatedIconButton(r,c,ballIcons);
    connect(cell, SIGNAL(clicked()), this, SLOT(handleCellClicked()));
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
    selectedCell=nullptr;
    //fitAnimationSize(btn->size());
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
    btn->setupAnimation("iconSize", btn->size(), QSize(5,5),
        600, AnimatedIconButton::UNOCCUPIED);
    btn->startAnimation(btn->getState());
}

void CellGridControl::handleCellClicked()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    emit userInput(clickedButton, selectedCell);
}

void CellGridControl::startDelayedAnimation(
    AnimatedIconButton *btn, int animated_state, int delay)
{
    QTimer::singleShot(delay, btn,
        [btn, animated_state]{ btn->startAnimation(animated_state); });
}

void CellGridControl::removeWithAnimation(
    const std::vector<BoardInfo::cell_location> &locations)
{
    if (locations.size() > 0) {
        hideAnimation();
        AnimatedIconButton *btn;
        for (std::vector<BoardInfo::cell_location>::const_iterator i = locations.begin();
            i < locations.end();
            ++i) {
            btn = boardCells[i->first][i->second];
            startEliminationAnimation(btn);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit animationFinished();
                disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);});
    } else {
        emit animationFinished();
        disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);
    }
}

void CellGridControl::putWithAnimation(
    const std::vector<BoardInfo::cell_location> &locations,
    const std::vector<BallColor::type> &colors)
{
    if (locations.size() > 0) {
        hideAnimation();
        AnimatedIconButton *btn;
//        for (std::vector<BoardInfo::cell_location>::iterator i = locations.begin();
//            i < locations.end();
        for (size_t i = 0;
            i < locations.size();
            ++i) {
            BoardInfo::cell_location loc = locations[i];
            int state = colors[i];
            btn = boardCells[loc.first][loc.second];
            btn->setupAnimation("opacity", 0, 1, 600, state);
            btn->startAnimation(state);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit animationFinished();
                disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);});
    } else {
        emit animationFinished();
        disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);
    }
}
