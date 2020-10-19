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

#include <utility>
#include <qdebug.h>
#include <QRandomGenerator>

#include "board.h"
#include "gamecontrol.h"

GameControl::GameControl(BoardInterface *bs, QObject *parent)
    : QObject(parent)
    , board(bs)
{

}

int GameControl::getUnoccupied(std::vector<std::pair<int,int>> &unoccupied)
{
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            if (board->getColorAt(r,c) == BallColor::none) {
                unoccupied.push_back(std::make_pair(r,c));
            }
        }
    }
    return static_cast<int>(unoccupied.size());
}

bool GameControl::generateRandomSpawn(
    std::vector<std::pair<int,int>> &spawn,
    std::vector<BallColor::type> &color)
{
    std::vector<std::pair<int,int>> unoccupied;
    getUnoccupied(unoccupied);
    std::random_shuffle(unoccupied.begin(), unoccupied.end());
    std::copy(unoccupied.begin(),
        std::min(unoccupied.end(), unoccupied.begin()+SPAWN_BALLS_NUM),
        std::back_inserter(spawn));

    for (size_t i=0; i<SPAWN_BALLS_NUM; ++i) {
        color.push_back(getRandomColor());
    }
    return spawn.size()<SPAWN_BALLS_NUM;
}

void GameControl::clear()
{
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            board->setColorAt(r,c,BallColor::none);
        }
    }
}

void GameControl::makeNextMove()
{
    //TOFIX: never called
}

BallColor::type GameControl::getRandomColor()
{
    return static_cast<BallColor::type>(
        QRandomGenerator::global()->bounded(BallColor::yellow+1/*BallColor::last+1*/));
}
/*
void GameControl::updateNextSpawn()
{
    for (BallColor::type *sc = &next_spawn[0];
        sc < &next_spawn[SPAWN_BALLS_NUM];
        ++sc) {
        *sc = getRandomColor();
    }
}

std::pair<BallColor::type *, BallColor::type *> GameControl::getNextSpawn()
{
    return std::make_pair(&next_spawn[0], &next_spawn[SPAWN_BALLS_NUM]);
}
*/
void GameControl::getStraitConnection(
    const BoardInfo::cell_location &loc,
    std::vector<BoardInfo::cell_location> &connection)
{
    BoardInfo bi(*board);
    bi.getStraitConnection(
        BoardInfo::cell_location(loc.first, loc.second),
        connection);
}

void GameControl::getAllConnections(
        const std::vector<BoardInfo::cell_location> &spawn,
        std::vector<BoardInfo::cell_location> &connection)
{
    std::for_each(spawn.cbegin(), spawn.cend(),
        [this, &connection](const BoardInfo::cell_location &loc){ getStraitConnection(loc, connection); });
}

void GameControl::handleMove(const BoardInfo::cell_location &loc)
{
    //TOFIX: never called
    qDebug() << "GameControl::handleMove: cell location is " << loc << "\n";

    std::vector<BoardInfo::cell_location> connection;
    BoardInfo bi(*board);
    bi.getStraitConnection(
        BoardInfo::cell_location(loc.first, loc.second),
        connection);
}

