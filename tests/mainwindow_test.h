/*

Copyright (C) 2020-2024 Volodymyr Kryachko

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

#ifndef MAINWINDOW_TEST_H
#define MAINWINDOW_TEST_H

#define QT_NO_DEBUG_OUTPUT

#include <QDebug>
#include <QWidget>
#include <QList>
#include <QGridLayout>
#include <QIcon>

#include "../basic_defs.hpp"

class AnimatedIconButton;

class SizeHintGridLayout: public QGridLayout
{
    Q_OBJECT
public:
    SizeHintGridLayout() : QGridLayout() {};
    ~SizeHintGridLayout() {};

    QSize sizeHint() const override {
        qDebug() << "SizeHintGridLayout::sizeHint: " << hintSize <<
                    "\nSizeHintGridLayout::geometry=" << geometry();
        return hintSize.isEmpty() ? QGridLayout::sizeHint() : hintSize;
    };
    void setSizeHint(const QSize s) {
        hintSize = s;
    };

private:
    QSize hintSize;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void resizeEvent(QResizeEvent *e) override;

public slots:
    void handleButtonClick();
    void handleAnimationFinished();

private:
    QGridLayout *main_layout;
    SizeHintGridLayout *grid;

    QList<AnimatedIconButton *> button_list;
    QIcon ballIcons[BallColor::colors_num];

};

#endif // MAINWINDOW_TEST_H
