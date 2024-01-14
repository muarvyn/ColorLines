/*

Copyright (C) 2024 Volodymyr Kryachko

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

#ifndef TRANSPOSABLE_H
#define TRANSPOSABLE_H

#include <QSize>

class Transposable
{
public:
    enum Orientation {Horizontal, Vertical};

    Transposable(Orientation o = Vertical)
        : orientation(o) {};

    Orientation getOrientation() const   { return orientation; };
    virtual void setOrientation(const Orientation o) { orientation = o; };
    virtual QSize getMinimumSize() const = 0;

    static Orientation transpose(const Orientation o) {
        return o == Vertical ? Horizontal : Vertical;
    };

protected:
    Orientation orientation;

};

#endif // TRANSPOSABLE_H
