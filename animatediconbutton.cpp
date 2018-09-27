#include "animatediconbutton.h"

AnimatedIconButton::AnimatedIconButton(int r, int c, QIcon *i)
    : IconCellButton(r,c,i)
    , label(this)
    , effect(this)
    , animation(new QPropertyAnimation(&this->effect, "opacity"))

{
    this->label.setGraphicsEffect(&this->effect);
}

void AnimatedIconButton::startDelayed(int state, int delay)
{
    if (state == UNOCCUPIED) {
        this->animation->stop();
        return;
    }
    this->animation->setDuration(2000);
    this->animation->setStartValue(1);
    this->animation->setEndValue(0);
    this->animation->setEasingCurve(QEasingCurve::OutBack);
    QTimer::singleShot(delay, this, [this, state] () { this->start(state); });
}

void AnimatedIconButton::setDelayed(int state, int delay)
{
    QTimer::singleShot(delay, this, [this, state] () { this->setState(state); });
}

void AnimatedIconButton::finalizeAnimation()
{
    this->label.hide();
}

void AnimatedIconButton::start(int state)
{
    const QIcon icon = icons[state];
    QLabel *label = &this->label;
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setBackgroundRole(QPalette::Dark);
    label->resize(this->size());
    label->setAutoFillBackground(false);
    label->setPixmap(icon.pixmap(this->size()));
    this->setState(UNOCCUPIED);
    label->show();
    connect(this->animation, SIGNAL(finished()),this,SLOT(finalizeAnimation()));
    this->animation->start();
}
