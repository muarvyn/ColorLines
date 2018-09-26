
#include "cellbutton.h"

CellButton::CellButton(int r, int c) : row(r), column(c), state(-1)
{

}

QSize CellButton::sizeHint() const
{
    return QSize(40,40);
}

