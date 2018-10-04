#include "animatediconbutton.h"

AnimatedIconButton::AnimatedIconButton(int r, int c, QIcon *i)
    : IconCellButton(r,c,i)
    , label(this)
    , effect(this)
    , animation(new QPropertyAnimation(&this->effect, "opacity"))
{
    label.setGraphicsEffect(&this->effect);
}

void AnimatedIconButton::setupAnimation(
    const QByteArray &propertyName, const QVariant &startValue,
    const QVariant &endValue, int duration, int final_state)
{
    if (!animation->Stopped) {
        animation->stop();
    }
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
    connect(animation, &QPropertyAnimation::finished, this,
        [this, final_state] () {finalizeAnimation(final_state);});
//    animation->setEasingCurve(QEasingCurve::OutBack);

}

void AnimatedIconButton::setDelayed(int state, int delay)
{
    QTimer::singleShot(delay, this, [this, state] () { this->setState(state); });
}

void AnimatedIconButton::finalizeAnimation(int final_state)
{
    label.hide();
    setState(final_state);
    emit animation_finished();
    disconnect(this, &AnimatedIconButton::animation_finished, nullptr, nullptr);
}

void AnimatedIconButton::startAnimation(int animated_state)
{
    setState(UNOCCUPIED);
    const QIcon icon = icons[animated_state];
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
    this->animation->start();
}
