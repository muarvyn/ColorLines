#ifndef EDITTOOLBARCONTROL_H
#define EDITTOOLBARCONTROL_H

#include <QObject>
#include "basic_defs.hpp"

class CellGridControl;
class AnimatedIconButton;
class CellButton;

class EditModeControl : public QObject
{
    Q_OBJECT
public:
    explicit EditModeControl(CellGridControl *board,
                             CellGridControl *toolbar,
                             ColorCell::LineIterator line,
                             QObject *parent = nullptr);
    ~EditModeControl() override;

signals:

public slots:
    void handleBoardInput( AnimatedIconButton *clickedButton);
    void handleToolbarInput( AnimatedIconButton *clickedButton);

private:
    CellGridControl *board;
    CellGridControl *toolbar;
    BallColor::type selectedColor;

};

#endif // EDITTOOLBARCONTROL_H
