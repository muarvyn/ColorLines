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

#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QToolButton>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CustomToolButton(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void setSizeHint(const QSize s) {
        hintSize = s;
    };

protected:
    void resizeEvent(QResizeEvent * event) override;

private:
    QSize hintSize;

};

#endif // CUSTOMTOOLBUTTON_H
