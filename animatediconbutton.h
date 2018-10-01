#ifndef ANIMATEDICONBUTTON_H
#define ANIMATEDICONBUTTON_H

#include "iconcellbutton.h"

class AnimatedIconButton : public IconCellButton
{
    Q_OBJECT

public:
    AnimatedIconButton(int r, int c, QIcon *i = nullptr);

    void setDelayed(int state, int delay);

    void setupAnimation(
        const QByteArray &propertyName, const QVariant &startValue,
        const QVariant &endValue, int duration, int final_state);

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
