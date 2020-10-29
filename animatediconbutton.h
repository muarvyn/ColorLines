/*

Copyright (C) 2018-2020 Volodymyr Kryachko

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

#ifndef ANIMATEDICONBUTTON_H
#define ANIMATEDICONBUTTON_H

#include "iconcellbutton.h"

class AnimatedIconButton : public IconCellButton
{
    Q_OBJECT

public:
    AnimatedIconButton(int r, int c, QIcon *i = nullptr, QWidget *parent = nullptr);
    virtual ~AnimatedIconButton();

    void setupAnimation(
        const QByteArray &propertyName, const QVariant &startValue,
        const QVariant &endValue, int duration, int final_state);
    bool isAnimating();
    void stopAnimation();

public slots:
    void finalizeAnimation(int final_state);
    void startAnimation(int animated_state);

signals:
    void animation_finished();

private:
    QLabel label;
    QGraphicsOpacityEffect effect;
    QPropertyAnimation *animation;

};

#endif // ANIMATEDICONBUTTON_H
