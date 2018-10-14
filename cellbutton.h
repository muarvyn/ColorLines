#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QtWidgets>
#include "board.h"

class CellButton : public QPushButton, public ColorCell
{
    Q_OBJECT

public:
    CellButton(int r, int c);

    QSize sizeHint() const override;

    inline int getRow() const { return row; }
    inline int getColumn() const { return column; }
    inline int getState() const { return state; }
    virtual void setState(int s) { state = s; }
    virtual void setColor(BallColor::type color) override { setState(color); }
    virtual BallColor::type getColor() const override
        { return static_cast<BallColor::type>(getState()); }
    
    static const int UNOCCUPIED = -1;

signals:
    void resized(QResizeEvent * event);

protected:
    void resizeEvent(QResizeEvent * event) override { emit resized(event); }

protected:
    int row, column, state;
    BallColor::type color;

private:
    virtual int heightForWidth( int w ) const override;
    virtual bool hasHeightForWidth() const override { return true; }
};

#endif // CELLBUTTON_H
