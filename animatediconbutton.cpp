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

#include "animatediconbutton.h"

AnimatedIconButton::AnimatedIconButton(int r, int c, QIcon *i, QWidget *parent)
    : IconCellButton(r,c,i,parent)
    , label(this)
    , effect(this)
    , animation(new QPropertyAnimation(&this->effect, "opacity"))
{
    label.setGraphicsEffect(&this->effect);
    connect(animation, &QPropertyAnimation::finished,
            this, &AnimatedIconButton::finalizeAnimation);
}

AnimatedIconButton::~AnimatedIconButton()
{
    if (isAnimating()) {
        stopAnimation();
    }
    delete animation;
}

bool AnimatedIconButton::isAnimating()
{
    return animation->state() != QAbstractAnimation::Stopped;
}

void AnimatedIconButton::stopAnimation()
{
    if (isAnimating()) {
        animation->stop();
        finalizeAnimation();
    }
}

void AnimatedIconButton::setupAnimation(
    const QByteArray &propertyName, const QVariant &startValue,
    const QVariant &endValue, int duration)
{
    if (isAnimating()) {
        stopAnimation();
    }
    animation->setPropertyName(""); // this prevents QPropertyAnimation from a warning at runtime
    if (propertyName == "opacity") {
        animation->setTargetObject(&effect);
    } else if (propertyName == "iconSize") {
        animation->setTargetObject(this);
    } else {
        animation->setTargetObject(&label);
    }
    animation->setDuration(duration);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setPropertyName(propertyName);
}

void AnimatedIconButton::finalizeAnimation()
{
    label.hide();
    emit animation_finished();
    setState(state);
}

void AnimatedIconButton::startAnimation(int animation_state, int final_state)
{
    const QIcon icon = (animation_state != UNOCCUPIED) ? icons[animation_state] : QIcon();
    if (animation->propertyName() == "iconSize") {
        setIcon(icon);
    } else {
        label.setAlignment(Qt::AlignCenter);
        label.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        label.setBackgroundRole(QPalette::Dark);
        label.resize(this->size());
        label.setAutoFillBackground(false);
        label.setPixmap(icon.pixmap(this->size()));
        effect.update();
        label.show();
    }
    state = final_state;
    this->animation->start();
}
