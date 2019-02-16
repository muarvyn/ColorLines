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

#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fixedaspectratioitem.h"
#include "cellgridcontrol.h"
#include "gamecontrol.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , score(0)
{
    ui->setupUi(this);
    QGridLayout *grid_layout = new QGridLayout();

    FixedAspectRatioLayout * square_layout = new FixedAspectRatioLayout();
    QVBoxLayout * vbox = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    vbox->addLayout(square_layout);
    QWidget * dull_widget = new QWidget();
    square_layout->addWidget(dull_widget);
    dull_widget->setLayout(grid_layout);

    gridControl = new CellGridControl(grid_layout, this);
    gameControl = new GameControl(gridControl, this);
    connect(gridControl, &CellGridControl::userInput, this, &MainWindow::handleMove);

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
        c=static_cast<BallColor::type>(c+1)) //TOFIX: define operator++?
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    QTimer::singleShot(600, this, &MainWindow::makeMove);
}

void MainWindow::handleMove(const BoardInfo::cell_location &loc)
{
    qDebug() << "GameControl::handleMove: cell location is " << loc << "\n";

    std::vector<BoardInfo::cell_location> connection;
    gameControl->getStraitConnection(loc, connection);
    score += connection.size();
    scoreLab->setText(QString::number(score));
    if (!connection.empty()) {
        /*
        connect(
            gridControl, &CellGridControl::animationFinished,
            this, &MainWindow::makeMove);
        */
        gridControl->removeWithAnimation(connection);
    } else {
        makeMove();
    }
}

void MainWindow::makeMove()
{
    std::vector<BallColor::type> spawn_colors;
    std::vector<BoardInfo::cell_location> spawn_pos;
    gameControl->generateRandomSpawn(spawn_pos, spawn_colors);

    gridControl->putWithAnimation(spawn_pos, cached_colors);
    std::copy(spawn_colors.begin(), spawn_colors.end(), cached_colors.begin());

    for (size_t i=0; i<SPAWN_BALLS_NUM; ++i) {
        const QIcon icon = ballIcons[cached_colors[i]];
        QLabel *lab = spawnColorLabels[i];
        lab->setPixmap(icon.pixmap(lab->size()/2));
        lab->setAlignment(Qt::AlignCenter);
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
    QTimer::singleShot(600, this, &MainWindow::makeMove);
}
