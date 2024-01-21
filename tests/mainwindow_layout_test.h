/*

Copyright (C) 2020-2024 Volodymyr Kryachko

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

#ifndef MAINWINDOW_LAYOUT_TEST_H
#define MAINWINDOW_LAYOUT_TEST_H

#include <QWidget>

class CustomToolButton;
class TransposableBoxLayout;
class QGridLayout;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void setupButtons(TransposableBoxLayout &swap_box);
    void resizeEvent(QResizeEvent *e) override;

private:
    QGridLayout *grid_layout;
    TransposableBoxLayout *first_item;
    TransposableBoxLayout *last_item;

};
#endif // MAINWINDOW_LAYOUT_TEST_H
