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

#include "gameboard.h"
#include "boardcontrol.h"

BoardControl::BoardControl(CellGridControl *gc, QObject *parent)
    : QObject(parent)
    , gridControl(gc)
    , selectedCell(nullptr)
{
    board = new GameBoard(gridControl->getCells(), this);
}

bool BoardControl::selectCell(BoardInfo::cell_location loc)
{
    return selectCell(board->getCell(loc));
}

bool BoardControl::selectCell(AnimatedIconButton *cell)
{
    if (cell == selectedCell || cell->getState() == CellButton::UNOCCUPIED) {
        return false;
    }
    gridControl->setButtonAnimation(*cell);
    selectedCell = cell;
    return true;
}

bool BoardControl::deselect() {
    if (selectedCell == nullptr)
        return false;
    selectedCell=nullptr;
    gridControl->hideAnimation();
    return true;
}

void BoardControl::animatePath(std::vector<BoardInfo::cell_location> &path,
                                AnimatedIconButton *lastButton) {

    int delay = 0;
    BoardInfo::cell_location first_loc = path.back();
    AnimatedIconButton *path_button = gridControl->getCells()[first_loc.first][first_loc.second];
    int st = path_button->getState();
    path_button->setState(AnimatedIconButton::UNOCCUPIED);

    for (std::vector<BoardInfo::cell_location>::reverse_iterator ri = path.rbegin();
        ri != path.rend();
        ++ri) {
        path_button = gridControl->getCells()[ri->first][ri->second];
        path_button->setupAnimation("opacity", 1, 0, 1000);
        gridControl->startDelayedAnimation(path_button, st, AnimatedIconButton::UNOCCUPIED, delay);
        delay+=100;
    }
    connect(path_button, &AnimatedIconButton::animation_finished,
        this,
        [this, lastButton] {
            emit moveFinished(BoardInfo::cell_location(
                lastButton->getRow(), lastButton->getColumn()));
        });
    QTimer::singleShot(
        delay,
        [lastButton, st]{ lastButton->setState(st); });
}

void BoardControl::animateSpawn(
    const std::vector<BoardInfo::cell_location> &locations,
    const std::vector<BallColor::type> &colors)
{
    if (locations.size() > 0) {
        gridControl->hideAnimation();
        AnimatedIconButton *btn;
        for (size_t i = 0;
            i < locations.size();
            ++i) {
            BoardInfo::cell_location loc = locations[i];
            int state = colors[i];
            btn = gridControl->getCells()[loc.first][loc.second];
            btn->setupAnimation("opacity", 0, 1, 600);
            btn->startAnimation(state, state);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit spawnAnimationFinished();
                });
    } else {
        // TODO: handle endgame
        emit gridControl->animationFinished();
    }
}

void BoardControl::animateDisappear(
    const std::vector<BoardInfo::cell_location> &locations)
{
    if (locations.size() > 0) {
        gridControl->hideAnimation();
        AnimatedIconButton *btn;
        for (std::vector<BoardInfo::cell_location>::const_iterator i = locations.begin();
            i < locations.end();
            ++i) {
            btn = gridControl->getCells()[i->first][i->second];
            gridControl->startEliminationAnimation(btn);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit gridControl->animationFinished();
                disconnect(gridControl, &CellGridControl::animationFinished, nullptr,nullptr);});
    } else {
        emit gridControl->animationFinished();
        disconnect(gridControl, &CellGridControl::animationFinished, nullptr,nullptr);
    }

}

void BoardControl::handleClicked( AnimatedIconButton *clickedButton) {
    if (clickedButton==selectedCell) {
        deselect();
        return;
    }
    if (clickedButton->getState() == CellButton::UNOCCUPIED) {
        if (selectedCell != nullptr) {
            board->makeDijkstraSearch(
                selectedCell->getRow(),
                selectedCell->getColumn());

            std::vector<std::pair<int,int>> path;
            Board::distance_type dist = board->getReversePathTo(
                clickedButton->getRow(),
                clickedButton->getColumn(),
                path);

            if (dist < OCCUPATION_THRESHOLD) {
                deselect();
                animatePath(path, clickedButton);
            }
        }
    } else {
        gridControl->setButtonAnimation(*clickedButton);
        selectCell(clickedButton);
    }
}
