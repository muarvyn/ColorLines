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

#ifndef TESTWIDGETITEM_H
#define TESTWIDGETITEM_H

#include <QWidgetItem>

class TradeForSizeItem;

class TestWidgetItem : public QLayoutItem
{
public:
    TestWidgetItem(QLayout *l, TradeForSizeItem *item = nullptr);
    ~TestWidgetItem() override = default;

    QSize sizeHint() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    Qt::Orientations expandingDirections() const override;
    bool isEmpty() const override;
    void setGeometry(const QRect&) override;
    QRect geometry() const override;
    void addCentralWidget(QWidget *widget);

protected:
    //QList<QLayoutItem *> list;
    TradeForSizeItem *centralItem;
    QLayout *layout;
};

#endif // TESTWIDGETITEM_H
