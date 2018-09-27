#ifndef ANIMATEDICONBUTTON_H
#define ANIMATEDICONBUTTON_H

#include "iconcellbutton.h"

class AnimatedIconButton : public IconCellButton
{
    Q_OBJECT

public:
    AnimatedIconButton(int r, int c, QIcon *i = nullptr);
    void startDelayed(int state, int delay);
    void setDelayed(int state, int delay);

public slots:
    void finalizeAnimation();
    void start(int state);

signals:

private:
    QLabel label;
    QGraphicsOpacityEffect effect;
    QPropertyAnimation *animation;

};

#endif // ANIMATEDICONBUTTON_H
