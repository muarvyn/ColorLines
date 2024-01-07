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

#ifndef TRANSPOSABLEBUTTON_H
#define TRANSPOSABLEBUTTON_H

#include <QToolButton>
#include "../swappablelayout.h"

class TransposableButton : public QToolButton, public SwappableLayout
{
    Q_OBJECT
public:
    explicit TransposableButton(QWidget *parent = nullptr);

    QSize getMinimumSize() const override {
        return minimumSize();
    }

    QSize sizeHint() const override;

};

#endif // TRANSPOSABLEBUTTON_H
