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

#ifndef BOARDINFO_H
#define BOARDINFO_H

#include <vector>
#include <utility>
#include "basic_defs.hpp"

class BoardInfo
{
public:
    typedef std::pair<int,int> cell_location;
    typedef std::pair<int,int> Direction;
    static constexpr Direction orig_dirs[] = {{-1,0},{-1,-1},{0,-1},{1,-1}};
    static const int ORIG_DIRECTIONS_NUM = sizeof(orig_dirs)/sizeof(orig_dirs[0]);
    static const int MIN_LINE_ELIMINATION_SIZE = 5;

    BoardInfo(BoardInterface &);
    void getStraitConnection( cell_location start,
        std::vector<cell_location> &connection);
    bool isInRange(int r, int c) {
        return r>=0 && r<BoardDim::ROWS_NUM && c>=0 && c<BoardDim::COLUMNS_NUM;
    }

private:
    BoardInterface &board;
};

#endif // BOARDINFO_H
