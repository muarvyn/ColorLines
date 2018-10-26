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

#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <QObject>
QT_BEGIN_NAMESPACE
class AnimatedIconButton;
QT_END_NAMESPACE
class DijkstraSearch;
#include "basic_defs.hpp"

class Board : public QObject
{
    Q_OBJECT

public:
    typedef double distance_type;

    static BallColor::type getRandom();

//    bool isOccupied();

    explicit Board(AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM]
        , QObject *parent = nullptr);

    void getOccupiedMap(distance_type wmap[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM]);
//    void getUnoccupied(std::vector<std::pair<int,int>> &unoccupied);
    void makeDijkstraSearch(int r, int c);
    double getReversePathTo(int dest_r, int dest_c, std::vector<std::pair<int,int>> &path);
    distance_type getDistance(int dest_r, int dest_c);
    virtual ~Board() {}
    BallColor::type getColorAt(int r, int c);

signals:

public slots:

protected:
    AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM];
    std::shared_ptr<DijkstraSearch> dijkstra;
};

#endif // BOARD_H
