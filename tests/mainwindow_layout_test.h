/*

Copyright (C) 2020-2021 Volodymyr Kryachko

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
class SwapBoxLayout;
template <typename T>
class IntermediateItemLayout;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    typedef IntermediateItemLayout<SwapBoxLayout> MainLayout;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void handleButtonClick();

protected:
    QList<CustomToolButton *> toolbutton_list;
    MainLayout *first_item, *last_item;
    MainLayout *main_layout;

};
#endif // MAINWINDOW_LAYOUT_TEST_H
