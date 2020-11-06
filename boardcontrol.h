/*

Copyright (C) 2018-2020 Volodymyr Kryachko

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

#ifndef BOARDCONTROL_H
#define BOARDCONTROL_H

#include <QObject>
#include "boardinfo.h"
#include "animatediconbutton.h"
#include "cellgridcontrol.h"

QT_BEGIN_NAMESPACE
class Board;
QT_END_NAMESPACE

class BoardControl : public QObject
{
    Q_OBJECT
public:
    explicit BoardControl(CellGridControl *gc, QObject *parent = nullptr);
    static constexpr double OCCUPATION_THRESHOLD = 0.9;

    bool selectCell(BoardInfo::cell_location);
    bool selectCell(AnimatedIconButton *cell);
    bool deselect();

    void animatePath(std::vector<BoardInfo::cell_location> &path,
                    AnimatedIconButton *lastButton);
    void animateSpawn(
         const std::vector<BoardInfo::cell_location> &locations,
         const std::vector<BallColor::type> &colors);
    void animateDisappear(const std::vector<BoardInfo::cell_location> &locations);

signals:
    void moveFinished(BoardInfo::cell_location);
    void spawnAnimationFinished();

public slots:
    void handleClicked( AnimatedIconButton *clickedButton);

private:
    CellGridControl *gridControl;
    CellButton *selectedCell;
    Board *board;
};

#endif // BOARDCONTROL_H
