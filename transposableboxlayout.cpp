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

#include <QDebug>
#include "transposableboxlayout.h"

const Qt::Alignment TransposableBoxLayout::default_policy[]=
{
    Qt::AlignRight|Qt::AlignBottom,
    Qt::AlignCenter,
    Qt::AlignLeft|Qt::AlignTop
};

TransposableBoxLayout::TransposableBoxLayout(Orientation o, QWidget *parent)
    : QBoxLayout(o == Vertical ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight, parent)
    , Transposable(o)
    , alignment_policy(default_policy)
{

}

void TransposableBoxLayout::setOrientation(Orientation o)
{
    if (orientation == o) return;

    setEnabled(false);
    orientation = o;

    /*
    Qt::Alignment local_mask, ext_mask;
    if (orientation == Vertical) {
        local_mask = Qt::AlignVertical_Mask;
        ext_mask = Qt::AlignHorizontal_Mask;
    } else {
        local_mask = Qt::AlignHorizontal_Mask;
        ext_mask = Qt::AlignVertical_Mask;
    }

    bool dbg = !objectName().isEmpty();

    if (dbg) qDebug() << "SwapBoxLayout::setOrientation. " << objectName()
                      << ": ori = " << orientation
                      << "; Local alignment: ";
    for (int i=0; i<count(); ++i) {
        Qt::Alignment loca = alignment_policy[qMin(i, qMax(1,i-count()+3))] & local_mask;
        QLayoutItem *item = itemAt(i);
        item->setAlignment(loca | (alignment() & ext_mask));
        if (dbg) qDebug() << QString("%1: %2").arg(i, 2, 10).
                             arg(loca | (alignment() & ext_mask), 10, 2);
    }
*/
    setDirection(orientation == Vertical ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight);
    for (int i = 0; i < count(); ++i) {
        auto item = itemAt(i);
        Transposable *l = dynamic_cast<Transposable *>(item);
        if (l) {
            l->setOrientation(orientation);
        }/* else {
            QWidget *w = item->widget();
            l = dynamic_cast<Transposable *>(w);
        }*/
        //qDebug() << "SwappableLayout::setOrientation. Item " << i << ": alignment is " <<
        //            QString("%1").arg(l->alignment(), 10, 2);
    }

    setEnabled(true);
}

QSize TransposableBoxLayout::sizeHint() const
{
    return QBoxLayout::sizeHint(); //TODO: ??
}
