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

#ifndef MAINWINDOW_GRID_LAYOUT_TEST_H
#define MAINWINDOW_GRID_LAYOUT_TEST_H

#include <QWidget>
#include <QGridLayout>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setupLayout(const QSize &size);

protected:
    void resizeEvent(QResizeEvent *e) override;

private:
    QGridLayout *grid_layout;

};
#endif // MAINWINDOW_GRID_LAYOUT_TEST_H
