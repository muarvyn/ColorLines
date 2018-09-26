#ifndef ANIMATEDICONBUTTON_H
#define ANIMATEDICONBUTTON_H

#include "iconcellbutton.h"

class AnimatedIconButton : public IconCellButton
{
    Q_OBJECT

public:
    AnimatedIconButton(int r, int c, QIcon *i = nullptr);
    void startDelayed(int delay);
//    virtual void setState(int s);

//    static const int ANIMATED = -2;

public slots:
    void hideLabel();

signals:

private:
    QLabel label;
    QGraphicsOpacityEffect effect;
};

#endif // ANIMATEDICONBUTTON_H
