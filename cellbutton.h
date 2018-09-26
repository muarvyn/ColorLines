#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QtWidgets>
#include "board.h"

class CellButton : public QPushButton
{
    Q_OBJECT

public:
    CellButton(int r, int c);

    QSize sizeHint() const override;

    inline int getRow() { return row; }
    inline int getColumn() { return column; }
    inline int getState() { return state; }
    virtual void setState(int s) { state = s; }
    
    static const int UNOCCUPIED = -1;

signals:
    void resized(QResizeEvent * event);

protected:
    void resizeEvent(QResizeEvent * event) override { emit resized(event); }

protected:
    int row, column, state;
    BallColor::type color;
};

#endif // CELLBUTTON_H
