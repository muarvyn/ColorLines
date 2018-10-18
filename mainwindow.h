#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "boardinfo.h"

class GameControl;
class CellGridControl;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow //QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleMove(const BoardInfo::cell_location &loc);
    void makeMove();

private:
    Ui::MainWindow *ui;
    CellGridControl *gridControl;
    GameControl *gameControl;
    std::vector<BallColor::type> cached_colors;

};

#endif // MAINWINDOW_H
