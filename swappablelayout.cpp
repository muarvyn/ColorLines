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
#include "swappablelayout.h"

SwappableLayout::SwappableLayout(Orientation o, QWidget *parent)
    : SwapLayout(o, parent)
{

}

void SwappableLayout::addLayout(QLayout *l)
{
    if (SwapLayout *swap = qobject_cast<SwapLayout *>(l)) {
        swappables.append(swap);
    }
    SwapLayout::addLayout(l);
}

void SwappableLayout::setOrientation(Orientation o)
{
    SwapLayout::setOrientation(o);

    for (int i=0; i<swappables.count(); ++i) {
        SwapLayout *l = swappables[i];
        l->setOrientation(o);
        //qDebug() << "SwappableLayout::setOrientation. Item " << i << ": alignment is " <<
        //            QString("%1").arg(l->alignment(), 10, 2);
    }
}
