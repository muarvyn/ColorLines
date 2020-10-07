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
    explicit EditModeControl(CellGridControl *board, CellGridControl *toolbar, QObject *parent = nullptr);
    ~EditModeControl();

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
