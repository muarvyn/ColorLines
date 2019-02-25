#ifndef BOARDCONTROL_H
#define BOARDCONTROL_H

#include <QObject>
#include "boardinfo.h"
#include "animatediconbutton.h"
#include "cellgridcontrol.h"

QT_BEGIN_NAMESPACE
class GameBoard;
QT_END_NAMESPACE

class BoardControl : public QObject
{
    Q_OBJECT
public:
    explicit BoardControl(CellGridControl *gc, QObject *parent = nullptr);
    static constexpr double OCCUPATION_THRESHOLD = 0.9;

signals:
    void moveFinished(BoardInfo::cell_location);

public slots:
    void handleCellClicked(AnimatedIconButton *clickedButton, CellButton *selectedCell);

private:
    CellGridControl *gridControl;
    CellButton *selectedCell;
    GameBoard *board;
};

#endif // BOARDCONTROL_H
