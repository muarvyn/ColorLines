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

#ifndef SWAPLAYOUT_H
#define SWAPLAYOUT_H

#include "swappablelayout.h"

#include <QGridLayout>


class SwapLayout : public QGridLayout, public SwappableLayout
{
    Q_OBJECT
public:
    static const Qt::Alignment default_policy[];

    SwapLayout(Orientation o = Vertical, QWidget *parent = nullptr);

    void addItem(QLayoutItem *item) override;
    void addWidget(QWidget *, Qt::Alignment = Qt::Alignment());
    void addLayout(QLayout *item);

    void setOrientation(Orientation) override;

protected:
    const Qt::Alignment *alignment_policy;
    QList<SwappableLayout*> swappables;

private:
    QPair<int, int> nextPosition();
};


#endif // SWAPLAYOUT_H
