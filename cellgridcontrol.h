#ifndef CELLGRIDCONTROL_H
#define CELLGRIDCONTROL_H

#include <QObject>
#include "cellbutton.h"

QT_BEGIN_NAMESPACE
class CellButton;
class AnimatedIconButton;
class GameBoard;
QT_END_NAMESPACE


class CellGridControl : public QObject
{
    Q_OBJECT
public:
    explicit CellGridControl(QGridLayout *gridLayout, QObject *parent = nullptr);

    AnimatedIconButton *createCell(int r, int c);
    void setButtonAnimation(CellButton &btn);
    void hideAnimation();
    void fitAnimationSize(QSize size);

    static constexpr double movieScale = 1.0;
    static constexpr double OCCUPATION_THRESHOLD = 0.9;

signals:

public slots:
    void handleCellClicked();
    void makeNextMove();

protected:
    QMovie *movie;
    QLabel *movieLabel;
    CellButton *selectedCell;
    GameBoard *board;
    QIcon ballIcons[BallColor::colors_num];
    AnimatedIconButton *boardCells[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM];

};

#endif // CELLGRIDCONTROL_H
