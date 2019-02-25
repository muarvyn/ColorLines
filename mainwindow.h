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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "boardinfo.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class GameControl;
class CellGridControl;
class BoardControl;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleMove(const BoardInfo::cell_location &loc);
    void makeMove();

    void on_actionNew_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *spawnColorLabels[SPAWN_BALLS_NUM];
    CellGridControl *gridControl;
    BoardControl *boardControl;
    GameControl *gameControl;
    std::vector<BallColor::type> cached_colors;
    QIcon ballIcons[BallColor::colors_num];
    int score;
    QLabel *scoreLab;

};

#endif // MAINWINDOW_H
