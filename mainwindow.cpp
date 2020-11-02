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

#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fixedaspectratioitem.h"
#include "cellgridcontrol.h"
#include "boardcontrol.h"
#include "editmodecontrol.h"
#include "gamecontrol.h"
#include "highscorestable.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , editControl(nullptr)
    , score(0)
{
    ui->setupUi(this);
    QGridLayout *grid_layout = new QGridLayout();
    QGridLayout *editTB_layout = new QGridLayout();

    FixedAspectRatioLayout * square_layout = new FixedAspectRatioLayout();
    QWidget * dull_widget = new QWidget();
    square_layout->addWidget(dull_widget);
    dull_widget->setLayout(grid_layout);

    gridControl = new CellGridControl(BoardDim::ROWS_NUM, BoardDim::COLUMNS_NUM, grid_layout, this);
    editToolbar = new CellGridControl(BallColor::colors_num, 1, editTB_layout, this);
    boardControl = new BoardControl(gridControl);
    gameControl = new GameControl(gridControl, this);
    connect(gridControl, &CellGridControl::userInput, boardControl, &BoardControl::handleClicked);
    connect(boardControl, &BoardControl::spawnAnimationFinished, this, &MainWindow::finalizeSpawn);
    connect(boardControl, &BoardControl::moveFinished, this, &MainWindow::handleMove);

    QHBoxLayout * hbox = qobject_cast<QHBoxLayout*>(ui->centralRowLayout);
    hbox->addLayout(editTB_layout);
    hbox->setAlignment(editTB_layout, Qt::AlignRight | Qt::AlignVCenter);
    hbox->addLayout(square_layout);

    for (size_t i=0; i<SPAWN_BALLS_NUM; ++i) {
        cached_colors.push_back(GameControl::getRandomColor());
    }

    scoreLab = ui->scoreLab;
    scoreLab->setText("0");
    spawnColorLabels[0] = ui->nextColor1;
    spawnColorLabels[1] = ui->nextColor2;
    spawnColorLabels[2] = ui->nextColor3;
    for (QLabel **nextLab=&spawnColorLabels[0];
        nextLab < &spawnColorLabels[SPAWN_BALLS_NUM];
        ++nextLab) {
        (*nextLab)->setMinimumSize(QSize(40,40)); //TOFIX: magic numbers
    }
    //TOFIX: duplicate code
    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    QTimer::singleShot(600, this, &MainWindow::makeSpawn);
}

void MainWindow::handleMove(const BoardInfo::cell_location &loc)
{
    qDebug() << "GameControl::handleMove: cell location is " << loc << "\n";

    std::vector<BoardInfo::cell_location> connection;
    gameControl->getStraitConnection(loc, connection);
    score += connection.size();
    scoreLab->setText(QString::number(score));
    if (!connection.empty()) {
        boardControl->animateDisappear(connection);
    } else {
        makeSpawn();
    }
}

void MainWindow::makeSpawn()
{
    std::vector<BallColor::type> spawn_colors;
    spawn_locations.clear();
    gameControl->generateRandomSpawn(spawn_locations, spawn_colors);

    boardControl->animateSpawn(spawn_locations, cached_colors);

    std::copy(spawn_colors.begin(), spawn_colors.end(), cached_colors.begin());

    for (size_t i=0; i<SPAWN_BALLS_NUM; ++i) {
        const QIcon icon = ballIcons[cached_colors[i]];
        QLabel *lab = spawnColorLabels[i];
        lab->setPixmap(icon.pixmap(lab->size()/2));
        lab->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::finalizeSpawn()
{
    std::vector<BoardInfo::cell_location> connection;
    gameControl->getAllConnections(spawn_locations, connection);
    if (!connection.empty()) {
        boardControl->animateDisappear(connection);
    } else {
        emit gridControl->animationFinished();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    gameControl->clear();
    scoreLab->setText("0");
    QTimer::singleShot(600, this, &MainWindow::makeSpawn);
}

void MainWindow::on_actionEdit_toggled(bool isEditMode)
{
    if (isEditMode && !editControl) {
        disconnect(gridControl, &CellGridControl::userInput,
                    boardControl, &BoardControl::handleClicked);
        editControl = new EditModeControl(gridControl, editToolbar);
    }
    else if(!isEditMode && editControl) {
        delete editControl;
        editControl = nullptr;
        connect(gridControl, &CellGridControl::userInput, boardControl, &BoardControl::handleClicked);
    }
}

void MainWindow::on_actionHighest_scores_triggered()
{
    QDialog *table = new HighScoresTable(this);
    table->exec();
}
