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

#ifndef BASIC_DEFS_HPP
#define BASIC_DEFS_HPP

#include <cstddef>
struct BallColor
{
    enum type {brown, red, green, navy, yellow, pink, blue, first=brown, last=blue, none=-1};
    static const std::size_t colors_num = static_cast<std::size_t>(last+1);
};

void operator++(BallColor::type&);

struct BoardDim
{
    static const int ROWS_NUM = 9;
    static const int COLUMNS_NUM = 9;
};

const std::size_t SPAWN_BALLS_NUM = 3;

class ColorCell
{
public:
    virtual BallColor::type getColor() const = 0;
    virtual void setColor(BallColor::type color) = 0;
    virtual ~ColorCell() = default;

    struct LineIterator {
        LineIterator(int r, int c, int ri, int ci)
            : row_inc(ri)
            , column_inc(ci)
            , row(r)
            , column(c)
        {}
        int row_inc;
        int column_inc;
        int row;
        int column;
        void operator ++() {
            row += row_inc;
            column += column_inc;
        }
    };
};

class BoardInterface
{
public:
    virtual BallColor::type getColorAt(int r, int c) const = 0;
    virtual void setColorAt(int r, int c, BallColor::type color) = 0;
    virtual void clear() = 0;
    virtual ~BoardInterface() = default;
};

#endif // BASIC_DEFS_HPP
