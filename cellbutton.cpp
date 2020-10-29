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


#include "cellbutton.h"

CellButton::CellButton(int r, int c, QWidget *parent)
    : QPushButton(parent)
    , row(r)
    , column(c)
    , state(-1)
{
    QSizePolicy policy;
    policy.setControlType(QSizePolicy::ToolButton);
    policy.setHorizontalPolicy(QSizePolicy::Preferred);
    policy.setVerticalPolicy(QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
}

QSize CellButton::sizeHint() const
{
    return QSize(40,40);
}

int CellButton::heightForWidth( int w ) const
{
    return w;
}
