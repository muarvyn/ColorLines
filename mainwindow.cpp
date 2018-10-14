#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cellgridcontrol.h"
#include "fixedaspectratioitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *grid_layout = new QGridLayout();

    FixedAspectRatioLayout * square_layout = new FixedAspectRatioLayout();
    QVBoxLayout * vbox = qobject_cast<QVBoxLayout*>(ui->centralwidget->layout());
    vbox->addLayout(square_layout);
    QWidget * dull_widget = new QWidget();
    square_layout->addWidget(dull_widget);
    dull_widget->setLayout(grid_layout);

    QLabel *labs[] = {ui->nextColor1, ui->nextColor2, ui->nextColor3};
    CellGridControl *gridcontrol = new CellGridControl(
        grid_layout,
        labs,
        this
        );
    //setWindowTitle(tr("Color Lines"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
