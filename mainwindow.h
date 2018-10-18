#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "boardinfo.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class GameControl;
class CellGridControl;

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

private:
    Ui::MainWindow *ui;
    QLabel *spawnColorLabels[SPAWN_BALLS_NUM];
    CellGridControl *gridControl;
    GameControl *gameControl;
    std::vector<BallColor::type> cached_colors;
    QIcon ballIcons[BallColor::colors_num];

};

#endif // MAINWINDOW_H
