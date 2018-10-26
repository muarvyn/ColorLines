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

#include "iconcellbutton.h"

IconCellButton::IconCellButton(int r, int c, QIcon *i) : CellButton (r,c), icons(i)
{

}

void IconCellButton::setState(int s) {
    state = s;
    if (state == UNOCCUPIED) {
        setIcon(QIcon());
    } else if (icons) {
        setIcon(icons[s]);
        setIconSize(size()/iconScale);
    }
}

void IconCellButton::resizeEvent(QResizeEvent * e)
{
    CellButton::resizeEvent(e);
    setIconSize(size()/iconScale);
}
