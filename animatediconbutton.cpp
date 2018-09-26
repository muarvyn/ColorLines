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
    label->setPixmap(icon.pixmap(QSize(this->size())));
//    label->setGraphicsEffect(&this->effect);
    QPropertyAnimation *a = new QPropertyAnimation(&this->effect, "opacity");
    a->setDuration(350);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    QTimer::singleShot(delay, a, SLOT(start(QPropertyAnimation::DeleteWhenStopped)));
    //a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this,SLOT(hideLabel()));
    label->show();
}

void AnimatedIconButton::hideLabel()
{
    label.hide();
}
