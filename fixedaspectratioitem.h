/*

Copyright (C) 2018 Volodymyr Kryachko

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

#ifndef FIXEDASPECTRATIOITEM_H
#define FIXEDASPECTRATIOITEM_H

#include <QLayoutItem>
#include <QLayout>

class FixedAspectRatioItem : public QWidgetItem
{
public:
    FixedAspectRatioItem(QWidget *widget, double s = 1.0);
    virtual bool hasHeightForWidth() const override;
    int heightForWidth(int w) const override;
    void setGeometry(const QRect &rect) override;
private:
    double scale;
};

class FixedAspectRatioLayout : public QLayout
{
public:
    explicit FixedAspectRatioLayout(QWidget *parent);
    explicit FixedAspectRatioLayout();
    ~FixedAspectRatioLayout() override;

    void addItem(QLayoutItem *item) override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

private:
    QLayoutItem * item;

};
#endif // FIXEDASPECTRATIOITEM_H
