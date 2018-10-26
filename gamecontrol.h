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

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "basic_defs.hpp"
#include "boardinfo.h"

class BoardState;

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(BoardInterface *bs, QObject *parent = nullptr);
    //void updateNextSpawn();
    //std::pair<BallColor::type *, BallColor::type *> getNextSpawn();
    int getUnoccupied(std::vector<std::pair<int,int>> &unoccupied);
    bool generateRandomSpawn(
        std::vector<std::pair<int,int>> &spawn,
        std::vector<BallColor::type> &color);

    static BallColor::type getRandomColor();
    void getStraitConnection(
        const BoardInfo::cell_location &loc,
        std::vector<BoardInfo::cell_location> &connection);

signals:

public slots:
    void makeNextMove();
//    void handleMove(AnimatedIconButton *btn);
    void handleMove(const BoardInfo::cell_location &loc);

private:
    //BallColor::type next_spawn[SPAWN_BALLS_NUM];
    BoardInterface *board;
};

#endif // GAMECONTROL_H
