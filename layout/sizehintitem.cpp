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

//#define QT_NO_DEBUG_OUTPUT
#include "sizehintitem.h"

#include <QDebug>
#include <QWidget>

SizeHintItem::SizeHintItem(QWidget *widget)
    : QWidgetItem(widget)
{
    qDebug() << "CustomToolButton::sizeHint: " << hintSize;
    hintSize = widget->sizeHint();
}
