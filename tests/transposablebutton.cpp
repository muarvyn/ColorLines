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

#include "transposablebutton.h"

TransposableButton::TransposableButton(QWidget *parent)
    : QToolButton(parent)
{
    setMinimumSize(QSize(40,40));
    setMaximumSize(QSize(420,420));
}

QSize TransposableButton::sizeHint() const {
    QSize hint = getMinimumSize();
    if (getOrientation() == Horizontal) {
        hint.setWidth(maximumWidth());
    } else {
        hint.setHeight(maximumHeight());
    }
    return hint;
}

