#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QIcon>

#include "../basic_defs.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleButtonClick();
    void handleAnimationFinished();

private:
    QIcon ballIcons[BallColor::colors_num];

};
#endif // MAINWINDOW_H
