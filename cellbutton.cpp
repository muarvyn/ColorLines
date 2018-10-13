
#include "cellbutton.h"

CellButton::CellButton(int r, int c) : row(r), column(c), state(-1)
{
    QSizePolicy policy;
    policy.setControlType(QSizePolicy::ToolButton);
    policy.setHorizontalPolicy(QSizePolicy::Preferred);
    policy.setVerticalPolicy(QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
}

QSize CellButton::sizeHint() const
{
    return QSize(40,40);
}

int CellButton::heightForWidth( int w ) const
{
    return w;
}
