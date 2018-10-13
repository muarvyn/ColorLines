#include "iconcellbutton.h"

IconCellButton::IconCellButton(int r, int c, QIcon *i) : CellButton (r,c), icons(i)
{

}

void IconCellButton::setState(int s) {
    state = s;
    if (state == UNOCCUPIED) {
        setIcon(QIcon());
    } else if (icons) {
        setIcon(icons[s]);
        setIconSize(size()/iconScale);
    }
}

void IconCellButton::resizeEvent(QResizeEvent *)
{
    setIconSize(size()/iconScale);
}
