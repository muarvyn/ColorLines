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

#include "transposable.h"

#include <QtWidgets>

void setupCenterLayout(QGridLayout &grid_layout, const QPoint c, const QSize &size)
{
    auto secondary_size = QSize();
    auto items = std::list<std::tuple<QWidget*, QLayout*, Transposable*>>();
    while (grid_layout.count()) {
        Transposable *transposable;
        auto grid_item = grid_layout.takeAt(0);
        Q_ASSERT(!grid_item->isEmpty());
        auto widget = grid_item->widget();
        auto layout = grid_item->layout();
        if(layout) {
            transposable = dynamic_cast<Transposable*>(layout);
        } else {
            transposable = dynamic_cast<Transposable*>(widget);
        }
        if (transposable) secondary_size += transposable->getMinimumSize();
        items.push_back(std::make_tuple(widget, layout, transposable));
    }

    auto f = (size.width() - size.height() + secondary_size.height())
            /float(secondary_size.height() + secondary_size.width());
    auto width = 0;
    auto line_pos = 1;
    const auto center = c + QPoint(1,1);
    //auto grid_rect = QRect(center, QSize(1,1));
    qDebug() << "secondary_size=" << secondary_size << " factor=" << f;
    auto is_horizontal = true;
    auto is_vertical = true;
    auto item_orientation = Transposable::Vertical;
    auto is_space = true;
    for (auto item : items) {
        auto transposable = std::get<2>(item);
        auto pos = center;
        if (transposable) {
            is_space = false;
            is_horizontal = is_horizontal &&
                (width + transposable->getMinimumSize().width()/2.0) < f*secondary_size.width();

            //qDebug() << "line_pos:" << line_pos;
            int dpos;
            if (is_horizontal) {
                is_vertical = false;
                pos = QPoint(line_pos, center.y());
                width += transposable->getMinimumSize().width();
                dpos = (pos.x()+1 == center.x()) ? 2 : 1;
                //grid_rect.setLeft(0);
                //grid_rect.setRight(std::max(line_pos, center.x()));
            } else {
                if (item_orientation == Transposable::Vertical) {
                    line_pos = 1;
                }
                pos = QPoint(center.x(), line_pos);
                item_orientation = Transposable::Horizontal;
                dpos = (pos.y()+1 == center.y()) ? 2 : 1;
                //grid_rect.setTop(0);
                //grid_rect.setBottom(std::max(line_pos, center.y()));
            }
            transposable->setOrientation(item_orientation);
            line_pos += dpos;
        } else {
            if (is_space) {
                if (std::get<0>(item)) {
                    delete std::get<0>(item);
                } else {
                    delete std::get<1>(item);
                }
                continue;
            } else {
                is_space = true;
            }
        }
        if (std::get<0>(item)) {
            qDebug() << "Adding widget at (" << pos.y() << ":" << pos.x() << ")";
            grid_layout.addWidget(std::get<0>(item), pos.y(), pos.x());
        } else {
            qDebug() << "Adding layout at (" << pos.y() << ":" << pos.x() << ")";
            grid_layout.addLayout(std::get<1>(item), pos.y(), pos.x());
        }
    }
    if (is_horizontal) {
        grid_layout.addWidget(new QWidget(), center.y(), 0);
        grid_layout.addWidget(new QWidget(), center.y(), line_pos);
    } else if (is_vertical) {
        grid_layout.addWidget(new QWidget(), 0, center.x());
        grid_layout.addWidget(new QWidget(), line_pos, center.x());
    }
/*
    for (auto pos = 0; pos < grid_layout.count(); pos++) {
        auto stretch = pos==center.y() ? 10 :
                       (grid_rect.top() <= pos) && (pos <= grid_rect.bottom()) ? 1 : 0;
        grid_layout.setRowStretch(pos, stretch);

        stretch = pos==center.x() ? 10 :
                       (grid_rect.left() <= pos) && (pos <= grid_rect.right()) ? 1 : 0;
        grid_layout.setColumnStretch(pos, stretch);
    }
*/
}
