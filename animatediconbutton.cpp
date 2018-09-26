#include "animatediconbutton.h"

AnimatedIconButton::AnimatedIconButton(int r, int c, QIcon *i)
    : IconCellButton(r,c,i)
    , label(this)
    , effect(this)
    , animation(nullptr)//&this->effect, "opacity")
    , animation_state(UNOCCUPIED)

{
    label.setGraphicsEffect(&this->effect);
    //QPropertyAnimation *a = new QPropertyAnimation(&this->effect, "opacity");
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
void AnimatedIconButton::startDelayed(int state, int delay)
{
    animation_state = state;
    if (animation_state < 0) return;
    this->animation = new QPropertyAnimation(&this->effect, "opacity");
    this->animation->setDuration(2000);
    this->animation->setStartValue(1);
    this->animation->setEndValue(0);
    this->animation->setEasingCurve(QEasingCurve::OutBack);
    QTimer::singleShot(delay, this, SLOT(start()));
}

void AnimatedIconButton::finalizeAnimation()
{
    this->label.hide();
    delete this->animation;
    this->animation = nullptr;
}

void AnimatedIconButton::start()
{
    this->setState(animation_state);
    const QIcon icon = this->icon();
    QLabel *label = &this->label;
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setBackgroundRole(QPalette::Dark);
    //label->setAutoFillBackground(true);
    label->resize(this->size());
    label->setAutoFillBackground(false);
    label->setPixmap(icon.pixmap(this->size()));
//    label->setGraphicsEffect(&this->effect);
    this->setState(UNOCCUPIED);
    this->label.show();
//    this->animation.setDuration(2000);
//    this->animation.setStartValue(1);
//    this->animation.setEndValue(0);
//    this->animation.setEasingCurve(QEasingCurve::OutBack);
//    this->animation.start();
    connect(this->animation, SIGNAL(finished()),this,SLOT(finalizeAnimation()));
    this->animation->start();
}
