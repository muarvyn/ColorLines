#include "mainwindow_test.h"

#include <QApplication>
#include <QRandomGenerator>

#include "../highscorestable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HighScoresTable w;
    int score = a.arguments().size() > 1 ? a.arguments()[1].toInt() : QRandomGenerator::global()->bounded(1000);
    w.newScore(score);
    return 0;
}
