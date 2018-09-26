#include "animatediconbutton.h"

AnimatedIconButton::AnimatedIconButton(int r, int c, QIcon *i)
    : IconCellButton(r,c,i)
    , label(this)
    , effect(this)

{
    label.setGraphicsEffect(&this->effect);
}
/*
void AnimatedIconButton::setState(int s) {
    int new_state = s;
    if (state == ANIMATED) {
        setIcon(QIcon());
    } else if (icons) {
        setIcon(icons[s]);
        setIconSize(size()/iconScale);
    }
}
*/
void AnimatedIconButton::startDelayed(int delay)
{
    const QIcon icon = this->icon();
    this->setState(UNOCCUPIED);
    QLabel *label = &this->label;
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setBackgroundRole(QPalette::Dark);
    //label->setAutoFillBackground(true);
    label->resize(this->size());
    label->setAutoFillBackground(false);
    label->setPixmap(icon.pixmap(this->size()));
//    label->setGraphicsEffect(&this->effect);
    QPropertyAnimation *a = new QPropertyAnimation(&this->effect, "opacity");
    a->setDuration(1000);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    QTimer::singleShot(delay, a, SLOT(start()));
    //a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this,SLOT(hideLabel()));
    label->show();
}

void AnimatedIconButton::hideLabel()
{
    label.hide();
}
