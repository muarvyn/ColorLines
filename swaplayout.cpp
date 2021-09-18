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

const Qt::Alignment SwapLayout::default_policy[]=
{
    Qt::AlignRight|Qt::AlignBottom,
    Qt::AlignCenter,
    Qt::AlignLeft|Qt::AlignTop
};


SwapLayout::SwapLayout(Orientation o, QWidget *parent)
    : QGridLayout(parent)
    , ori(o == Vertical ? Vertical : Horizontal)
    , alignment_policy(default_policy)
{

}

void SwapLayout::addItem(QLayoutItem *item)
{
    int inc_r = int(ori == Vertical), inc_c = int(ori == Horizontal);
    int r = inc_r*count(), c = inc_c*count();
    QGridLayout::addItem(item, r, c);
}

void SwapLayout::addWidget(QWidget *w, Qt::Alignment a)
{
    int inc_r = int(ori == Vertical), inc_c = int(ori == Horizontal);
    int r = inc_r*count(), c = inc_c*count();
    QGridLayout::addWidget(w, r, c, a);
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
    ori = ori == Vertical ? Horizontal : Vertical;
    Qt::Alignment local_mask, ext_mask;
    if (ori == Vertical) {
        local_mask = Qt::AlignVertical_Mask;
        ext_mask = Qt::AlignHorizontal_Mask;
    } else {
        local_mask = Qt::AlignHorizontal_Mask;
        ext_mask = Qt::AlignVertical_Mask;
    }

    QLayoutItem *item = itemAt(0);
    item->setAlignment(alignment_policy[0] & local_mask | alignment() & ext_mask);
    qDebug() << "SwapLayout::setOrientation. item 0 alignment: " <<
                QString("%1").arg(alignment_policy[0] & local_mask, 10, 2);
    QList<QLayoutItem*> list;
    while ((item = takeAt(1)) != nullptr) {
        list.append(item);
    }

    int r=0, c=0, inc_r = int(ori == Vertical), inc_c = int(ori == Horizontal);
    for (int i=0; i<list.count(); ++i) {
        item = list[i];
        r+=inc_r; c+=inc_c;
        Qt::Alignment loca = alignment_policy[qMax(1,i-list.count()+3)] & local_mask;
        QGridLayout::addItem(item, r, c, 1, 1, loca);
        qDebug() << QString("%1").arg(loca, 10, 2);
    }
    setEnabled(true);
}
