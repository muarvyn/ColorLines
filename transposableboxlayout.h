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

#ifndef TRANSPOSABLEBOXLAYOUT_H
#define TRANSPOSABLEBOXLAYOUT_H

#include "transposable.h"

#include <QBoxLayout>


class TransposableBoxLayout : public QBoxLayout, public Transposable
{
    Q_OBJECT
public:
    static const Qt::Alignment default_policy[];

    TransposableBoxLayout(Transposable::Orientation o = Vertical, QWidget *parent = nullptr);

    QSize getMinimumSize() const override {
        return minimumSize();
    }

    using QBoxLayout::addWidget;
    using QBoxLayout::addLayout;
    using QBoxLayout::sizeHint;

    void setOrientation(Orientation) override;
    QSize sizeHint() const override;

protected:
    const Qt::Alignment *alignment_policy;

};


#endif // TRANSPOSABLEBOXLAYOUT_H
