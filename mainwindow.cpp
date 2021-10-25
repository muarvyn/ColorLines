/*

Copyright (C) 2018-2021 Volodymyr Kryachko

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
#include "swapboxlayout.h"
#include "tradeforsizeroot.h"
#include "aspectratioitem.h"
#include "cellgridcontrol.h"
#include "boardcontrol.h"
#include "editmodecontrol.h"
#include "gamecontrol.h"
#include "highscorestable.h"
#include "settings.h"
#include "app_defs.h"


TradeForSizeItem *newFixedAspectRatioItem(
        QLayoutItem *i,
        TradeForSizeItem::InvalidateFunc invalidate_func)
{
    TradeForSizeItem* tfsi = new AspectRatioItem(i, invalidate_func, 1.0);
    return tfsi;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , editControl(nullptr)
{
    ui->setupUi(this);
    QSettings load_settings(OrganizationName, ApplicationName);
    restoreGeometry(load_settings.value("geometry").toByteArray());
    restoreState(load_settings.value("windowState").toByteArray());

    QGridLayout *grid_layout = new QGridLayout();
    TradeForSizeLayout<SwapBoxLayout> *editTB_layout =
            new TradeForSizeLayout<SwapBoxLayout>(SwappableLayout::Horizontal);

    QWidget * dull_widget = new QWidget();
    dull_widget->setLayout(grid_layout);

    gridControl = new CellGridControl(
                BoardDim::ROWS_NUM,
                BoardDim::COLUMNS_NUM,
                [grid_layout](QWidget* w, int r, int c) { grid_layout->addWidget(w,r,c); },
                this);
    editToolbar = new CellGridControl(
                1,
                BallColor::colors_num,
                [editTB_layout](QWidget* w, int, int){ editTB_layout->addWidget(w); },
                this);
    boardControl = new BoardControl(gridControl);
    gameControl = new GameControl(gridControl, this);
    connect(gridControl, &CellGridControl::userInput, boardControl, &BoardControl::handleClicked);
    connect(boardControl, &BoardControl::spawnAnimationFinished, this, &MainWindow::finalizeSpawn);
    connect(boardControl, &BoardControl::moveFinished, this, &MainWindow::handleMove);

    QHBoxLayout *spawnTB_layout = new QHBoxLayout();
    spawnTB_layout->addStretch(1);
    for (QLabel **nextLab=&spawnColorLabels[0];
        nextLab < &spawnColorLabels[SPAWN_BALLS_NUM];
        ++nextLab) {
        *nextLab = new QLabel();
        (*nextLab)->setMinimumSize(QSize(40,40)); //TOFIX: magic numbers
        (*nextLab)->setMaximumSize(QSize(80,80));
        spawnTB_layout->addWidget(*nextLab);
    }
    //TOFIX: duplicate code
    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        ++c)
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    Settings s;
    int score;
    std::size_t balls_num = s.loadGame(*gridControl, score);
    scoreLab = new QLabel();
    scoreLab->setText(QString::number(score));
    spawnTB_layout->addWidget(scoreLab);
    spawnTB_layout->addStretch(1);

    TradeForSizeRoot<SwapBoxLayout> *main_layout =
            new TradeForSizeRoot<SwapBoxLayout>(SwappableLayout::Vertical);

    main_layout->addLayout(spawnTB_layout);
    main_layout->addWidget<TradeForSizeItem::InvalidateFunc>(
                dull_widget,
                newFixedAspectRatioItem,
                [main_layout](){ main_layout->invalidateGeom(); });
    main_layout->addSwappable(editTB_layout);
    main_layout->setAlignment(editTB_layout, Qt::AlignTop | Qt::AlignHCenter);
    ui->centralwidget->setLayout(main_layout);

    gameControl->generateRandomSpawn(spawn_locations, cached_colors);
    showNextSpawn();
    if (balls_num < SPAWN_BALLS_NUM) {
        QTimer::singleShot(600, this, &MainWindow::makeSpawn);
    }
}

void MainWindow::handleMove(const BoardInfo::cell_location &loc)
{
    std::vector<BoardInfo::cell_location> connection;
    gameControl->getStraitConnection(loc, connection);
    scoreLab->setText(QString::number(scoreLab->text().toUInt()+connection.size()));
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
    if (spawn_locations.size() < SPAWN_BALLS_NUM) {
        handleEndGame();
        return;
    }

    boardControl->animateSpawn(spawn_locations, cached_colors);

    std::copy(spawn_colors.begin(), spawn_colors.end(), cached_colors.begin());
    showNextSpawn();
}

void MainWindow::showNextSpawn()
{
    for (size_t i=0; i<SPAWN_BALLS_NUM; ++i) {
        const QIcon icon = ballIcons[cached_colors[i]];
        QLabel *lab = spawnColorLabels[i];
        lab->setPixmap(icon.pixmap(lab->size()/2));
        lab->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::finalizeSpawn()
{
    qDebug() << "MainWindow::finalizeSpawn: entry.";
    std::vector<BoardInfo::cell_location> connection;
    gameControl->getAllConnections(spawn_locations, connection);
    if (!connection.empty()) {
        boardControl->animateDisappear(connection);
    } else {
        std::vector<BoardInfo::cell_location> unoccupied;
        gameControl->getUnoccupied(unoccupied);
        if (unoccupied.size() == 0) {
            handleEndGame();
        } else {
            emit gridControl->animationFinished(); // TOFIX: Not a good practice
        }
    }
}

void MainWindow::handleEndGame()
{
    qDebug() << "Endgame is occured.";
    HighScoresTable *table = new HighScoresTable(this);
    table->newScore(scoreLab->text().toInt());

    on_actionNew_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    gridControl->clear();
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    {
        Settings s;
        s.saveGame(*gridControl, scoreLab->text().toInt());
    }
    {
        QSettings settings(OrganizationName, ApplicationName);
        settings.setValue("geometry", saveGeometry());
        settings.setValue("windowState", saveState());
    }
    QMainWindow::closeEvent(event);
}
