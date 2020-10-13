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

    bool selectCell(BoardInfo::cell_location);
    bool selectCell(AnimatedIconButton *cell);
    bool deselect();

    void animatePath(std::vector<BoardInfo::cell_location> &path,
                    AnimatedIconButton *lastButton);
    void animateSpawn(
         const std::vector<BoardInfo::cell_location> &locations,
         const std::vector<BallColor::type> &colors);
    void animateDisappear(const std::vector<BoardInfo::cell_location> &locations);

signals:
    void moveFinished(BoardInfo::cell_location);

public slots:
    void handleCellClicked(AnimatedIconButton *clickedButton, CellButton *selectedCell);
    void handleClicked( AnimatedIconButton *clickedButton);

private:
    CellGridControl *gridControl;
    CellButton *selectedCell;
    GameBoard *board;
};

#endif // BOARDCONTROL_H
