#ifndef ICONCELLBUTTON_H
#define ICONCELLBUTTON_H

#include "cellbutton.h"

class IconCellButton : public CellButton
{
    Q_OBJECT
public:
    IconCellButton(int r, int c, QIcon *i = nullptr);

    virtual void setState(int s) override;
//    virtual void resize(const QSize &s) override;
    void setIcons(const QIcon *i) { icons = i; }

    static constexpr double iconScale = 1.0;

signals:
//    void resized(QResizeEvent * event);

protected:
    void resizeEvent(QResizeEvent * event) override;

protected:
    const QIcon *icons;
};

#endif // ICONCELLBUTTON_H
