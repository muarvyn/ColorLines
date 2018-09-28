#include <QtWidgets>

#include "mainwindow.h"
#include "cellgridcontrol.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);

    CellGridControl *gridcontrol = new CellGridControl(gridLayout, this);
    setWindowTitle(tr("Color Lines"));
}

MainWindow::~MainWindow()
{

}
