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

#ifndef CELLGRIDCONTROL_H
#define CELLGRIDCONTROL_H

#include <QtWidgets>

#include "boardinfo.h"
#include "cellbutton.h"

QT_BEGIN_NAMESPACE
class CellButton;
class AnimatedIconButton;
class GameBoard;
class GameControl;
QT_END_NAMESPACE


class CellGridControl : public QObject, public BoardInterface
{
    Q_OBJECT
public:
    explicit CellGridControl(
        QGridLayout *gridLayout,
        QObject *parent = nullptr);

    BallColor::type getColorAt(int r, int c) const;
    void setColorAt(int r, int c, BallColor::type color);
    AnimatedIconButton *createCell(int r, int c);
    void setButtonAnimation(CellButton &btn);
    void hideAnimation();
    void fitAnimationSize(QSize size);
    void startEliminationAnimation(AnimatedIconButton *btn);
    void startDelayedAnimation(AnimatedIconButton *btn, int animated_state, int delay);
    void removeWithAnimation(const std::vector<BoardInfo::cell_location> &locations);
    void putWithAnimation(
        const std::vector<BoardInfo::cell_location> &locations,
        const std::vector<BallColor::type> &colors);


    static constexpr double movieScale = 1.0;
    static constexpr double OCCUPATION_THRESHOLD = 0.9;

signals:
    void userInput(const BoardInfo::cell_location &loc);
    void animationFinished();

public slots:
    void handleCellClicked();
    //void makeNextMove();
    //void handleMove(AnimatedIconButton *btn);
    void movieResized(CellButton *btn);

protected:
    QMovie *movie;
    QLabel *movieLabel;
    CellButton *selectedCell;
    GameBoard *board;
    QIcon ballIcons[BallColor::colors_num];
    AnimatedIconButton *boardCells[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM];
    //GameControl *gameControl;

};

#endif // CELLGRIDCONTROL_H
