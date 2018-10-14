#ifndef CELLGRIDCONTROL_H
#define CELLGRIDCONTROL_H

//#include <QObject>
#include <QtWidgets>
#include "cellbutton.h"

QT_BEGIN_NAMESPACE
class CellButton;
class AnimatedIconButton;
class GameBoard;
class GameControl;
QT_END_NAMESPACE


class CellGridControl : public QObject, public BoardInterface
{
    Q_OBJECT
public:
    explicit CellGridControl(
        QGridLayout *gridLayout,
        QLabel *nextLabels[SPAWN_BALLS_NUM],
        QObject *parent = nullptr);

    BallColor::type getColorAt(int r, int c) const;
    AnimatedIconButton *createCell(int r, int c);
    void setButtonAnimation(CellButton &btn);
    void hideAnimation();
    void fitAnimationSize(QSize size);
    void startEliminationAnimation(AnimatedIconButton *btn);
    void startDelayedAnimation(AnimatedIconButton *btn, int animated_state, int delay);

    static constexpr double movieScale = 1.0;
    static constexpr double OCCUPATION_THRESHOLD = 0.9;

signals:

public slots:
    void handleCellClicked();
    void makeNextMove();
    void handleMove(AnimatedIconButton *btn);
    void movieResized(CellButton *btn);

protected:
    QMovie *movie;
    QLabel *movieLabel;
    CellButton *selectedCell;
    GameBoard *board;
    QIcon ballIcons[BallColor::colors_num];
    AnimatedIconButton *boardCells[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM];
    QLabel *nextMoveLabels[SPAWN_BALLS_NUM];
    GameControl *gameControl;

};

#endif // CELLGRIDCONTROL_H
