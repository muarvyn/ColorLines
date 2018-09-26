#ifndef ANIMATEDICONBUTTON_H
#define ANIMATEDICONBUTTON_H

#include "iconcellbutton.h"

class AnimatedIconButton : public IconCellButton
{
    Q_OBJECT

public:
    AnimatedIconButton(int r, int c, QIcon *i = nullptr);
    void startDelayed(int state, int delay);
//    virtual void setState(int s);

//    static const int ANIMATED = -2;

public slots:
//    void hideLabel();
    void finalizeAnimation();
    void start();

signals:

private:
    QLabel label;
    QGraphicsOpacityEffect effect;
    QPropertyAnimation *animation;
    int animation_state;

};

#endif // ANIMATEDICONBUTTON_H
