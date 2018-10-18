#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fixedaspectratioitem.h"
#include "cellgridcontrol.h"
#include "gamecontrol.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//    , gridControl(new CellGridControl())
//    , gameControl(new GameControl(gridControl))
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

    QLabel *labs[] = {ui->nextColor1, ui->nextColor2, ui->nextColor3};
    for (QLabel **nextLab=&labs[0];
        nextLab < &labs[SPAWN_BALLS_NUM];
        ++nextLab) {
        (*nextLab)->setMinimumSize(QSize(40,40)); //TOFIX: magic numbers
    }
    show();
    makeMove();
}

void MainWindow::handleMove(const BoardInfo::cell_location &loc)
{
    qDebug() << "GameControl::handleMove: cell location is " << loc << "\n";

    std::vector<BoardInfo::cell_location> connection;
    gameControl->getStraitConnection(loc, connection);
    if (!connection.empty()) {
        connect(
            gridControl, &CellGridControl::animationFinished,
            this, &MainWindow::makeMove);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

