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

#include <QDebug>
#include "swaplayout.h"

SwapLayout::SwapLayout(Orientation o, QWidget *parent)
    : QGridLayout(parent)
    , ori(o == Vertical ? Vertical : Horizontal)
{

}

void SwapLayout::addItem(QLayoutItem *item)
{
    int inc_r = int(ori == Vertical), inc_c = int(ori == Horizontal);
    int r = inc_r*count(), c = inc_c*count();
    QGridLayout::addItem(item, r, c);
}

void SwapLayout::addLayout(QLayout *item)
{
    int inc_r = int(ori == Vertical), inc_c = int(ori == Horizontal);
    int r = inc_r*count(), c = inc_c*count();
    QGridLayout::addLayout(item, r, c);
}

void SwapLayout::setOrientation(Orientation o)
{
    if (ori == o) return;
    setEnabled(false);
    QLayoutItem *item;
    QList<QLayoutItem*> list;
    while ((item = takeAt(1)) != nullptr) {
        list.append(item);
    }
    ori = ori == Vertical ? Horizontal : Vertical;
    int r=0, c=0, inc_r = int(ori == Vertical), inc_c = int(ori == Horizontal);
    for(QLayoutItem *item : list) {
        r+=inc_r; c+=inc_c;
        QGridLayout::addItem(item, r, c);
    }
    //qDebug() << "SwapLayout::swap in: " << ori;
    //qDebug() << "SwapLayout::swap upd: " << ori;
    setEnabled(true);
}
