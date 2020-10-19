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

#include "boardinfo.h"

BoardInfo::BoardInfo(BoardInterface &b)
    : board(b)
{

}

constexpr BoardInfo::Direction BoardInfo::orig_dirs[];

void BoardInfo::getStraitConnection( cell_location start,
        std::vector<cell_location> &connection)
{
    int state = board.getColorAt(start.first, start.second);
    if (state == BallColor::none) return;

    for (const Direction *dir = &orig_dirs[0];
        dir < &orig_dirs[ORIG_DIRECTIONS_NUM];
        ++dir) {
        int row=start.first, column=start.second;
        std::vector<cell_location> line;

        while (true) {
            row += dir->first;
            column += dir->second;
            if (!isInRange(row,column)) break;
            if (board.getColorAt(row,column) != state) break;
            line.push_back(cell_location(row,column));
        }
        row=start.first; column=start.second;
        while (true) {
            row -= dir->first;
            column -= dir->second;
            if (!isInRange(row,column)) break;
            if (board.getColorAt(row,column) != state) break;
            line.push_back(cell_location(row,column));
        }
        if (line.size() >= MIN_LINE_ELIMINATION_SIZE-1) { //TOFIX: isn't this exactly expected behaviour?
            std::copy(line.begin(), line.end(), std::back_inserter(connection));
        }
        line.clear();
    }
    if (!connection.empty()) { connection.push_back(start); }
}
