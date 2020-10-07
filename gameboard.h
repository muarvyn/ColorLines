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

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "board.h"
#include "boardinfo.h"

class GameBoard : public Board
{
    Q_OBJECT

public:
    static const int doze_size = 3;
    static const int MIN_LINE_ELIMINATION_SIZE = 5;

    typedef std::pair<int,int> Direction;
    static constexpr Direction orig_dirs[] = {{-1,0},{-1,-1},{0,-1},{1,-1}};
    static const int ORIG_DIRECTIONS_NUM = sizeof(orig_dirs)/sizeof(orig_dirs[0]);

    explicit GameBoard(
        const std::vector<std::vector<AnimatedIconButton*>> &board
        , QObject *parent = nullptr);

    AnimatedIconButton* getCell(BoardInfo::cell_location loc);
    bool isInRange(int r, int c) {
        return r>=0 && r<BoardDim::ROWS_NUM && c>=0 && c<BoardDim::COLUMNS_NUM;
    }
    int getUnoccupied(std::vector<const AnimatedIconButton*> &unoccupied);
    bool getRandomVacantDoze(const AnimatedIconButton* vacant[doze_size]);
    void getElimination(int r, int c, std::vector<AnimatedIconButton*> &connection);
    virtual ~GameBoard() {}

private:

};

#endif // GAMEBOARD_H
