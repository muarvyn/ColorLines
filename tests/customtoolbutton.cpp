/*

Copyright (C) 2020 Volodymyr Kryachko

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

#define QT_NO_DEBUG_OUTPUT

#include <QDebug>
#include <QResizeEvent>
#include "customtoolbutton.h"

CustomToolButton::CustomToolButton(QWidget *parent)
    : QToolButton(parent)
    , hintSize(QSize(80,80))
{
    setMinimumSize(QSize(40,40));
    setMaximumSize(QSize(120,120));
}

QSize CustomToolButton::sizeHint() const
{
    qDebug() << "CustomToolButton::sizeHint: " << hintSize;
    return hintSize;
}

void CustomToolButton::resizeEvent(QResizeEvent * event)
{
    qDebug() << "CustomToolButton::resizeEvent: " << event->size();

    QToolButton::resizeEvent(event);
}
