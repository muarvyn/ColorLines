/*

Copyright (C) 2021 Volodymyr Kryachko

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

#ifndef SWAPPABLELAYOUT_H
#define SWAPPABLELAYOUT_H

class QWidget;

class SwappableLayout
{
public:
    enum Orientation { Horizontal, Vertical, Swapped };
    //static const Qt::Alignment default_policy[];

    SwappableLayout(Orientation o = Vertical)
        : ori(o == Vertical ? Vertical : Horizontal) {};

    Orientation orientation() const   { return ori; };
    virtual void setOrientation(Orientation) = 0;

protected:
    Orientation ori;

};



#endif // SWAPPABLELAYOUT_H
