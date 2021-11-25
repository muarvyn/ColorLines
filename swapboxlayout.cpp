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
#include "swapboxlayout.h"

const Qt::Alignment SwapBoxLayout::default_policy[]=
{
    Qt::AlignRight|Qt::AlignBottom,
    Qt::AlignCenter,
    Qt::AlignLeft|Qt::AlignTop
};

SwapBoxLayout::SwapBoxLayout(Orientation o, QWidget *parent)
    : QBoxLayout(o == Vertical ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight, parent)
    , SwappableLayout(o)
    , alignment_policy(default_policy)
{

}

void SwapBoxLayout::addSwappable(QLayout *item)
{
    if (SwappableLayout *swap = dynamic_cast<SwappableLayout *>(item)) {
        swappables.append(swap);
    }
    QBoxLayout::addLayout(item);
}

void SwapBoxLayout::setOrientation(Orientation o)
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

    bool dbg = !objectName().isEmpty();

    if (dbg) qDebug() << "SwapBoxLayout::setOrientation. " << objectName()
                      << ": ori = " << ori
                      << "; Local alignment: ";
    for (int i=0; i<count(); ++i) {
        Qt::Alignment loca = alignment_policy[qMin(i, qMax(1,i-count()+3))] & local_mask;
        QLayoutItem *item = itemAt(i);
        item->setAlignment(loca | (alignment() & ext_mask));
        if (dbg) qDebug() << QString("%1: %2").arg(i, 2, 10).
                             arg(loca | (alignment() & ext_mask), 10, 2);
    }

    setDirection(ori == Vertical ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight);
    for (int i=0; i<swappables.count(); ++i) {
        SwappableLayout *l = swappables[i];
        l->setOrientation(o);
        //qDebug() << "SwappableLayout::setOrientation. Item " << i << ": alignment is " <<
        //            QString("%1").arg(l->alignment(), 10, 2);
    }

    setEnabled(true);
}

QSize SwapBoxLayout::sizeHint(SwappableLayout::Orientation o) const
{
    return QBoxLayout::sizeHint();
}
