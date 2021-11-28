/*

Copyright (C) 2018-2021 Volodymyr Kryachko

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
#include <chrono>
#include <qdebug.h>

#include "board.h"
#include "gamecontrol.h"

GameControl::GameControl(BoardInterface *bs, QObject *parent)
    : QObject(parent)
    , board(bs)
    , generator(std::chrono::system_clock::now().time_since_epoch().count())
{

}

int GameControl::getUnoccupied(std::vector<BoardInfo::cell_location> &unoccupied)
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
    std::vector<BoardInfo::cell_location> &spawn,
    std::vector<BallColor::type> &color)
{
    std::vector<BoardInfo::cell_location> unoccupied;
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

BallColor::type GameControl::getRandomColor()
{
    std::uniform_int_distribution<int> distribution(BallColor::first, BallColor::last);
    return static_cast<BallColor::type>(distribution(generator));
}

void GameControl::getStraitConnection(
    const BoardInfo::cell_location &loc,
    std::vector<BoardInfo::cell_location> &connection)
{
    // TODO: define operator<< for std::pair<>
    //qDebug() << "getStraitConnection: " << loc << " " << board->getColorAt(loc.first, loc.second);
    BoardInfo bi(*board);
    bi.getStraitConnection(loc, connection);
}

void GameControl::getAllConnections(
        const std::vector<BoardInfo::cell_location> &spawn,
        std::vector<BoardInfo::cell_location> &connection)
{
    std::for_each(spawn.cbegin(), spawn.cend(),
        [this, &connection](const BoardInfo::cell_location &loc){ getStraitConnection(loc, connection); });
}

