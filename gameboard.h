#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "board.h"

class GameBoard : public Board
{
    Q_OBJECT

public:
    static const int doze_size = 3;

    explicit GameBoard(
        AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM]
        , QObject *parent = nullptr);

    int getUnoccupied(std::vector<const AnimatedIconButton*> &unoccupied);
    bool getRandomVacantDoze(const AnimatedIconButton* vacant[doze_size]);
    virtual ~GameBoard() {}

private:
    //std::vector<AnimatedIconButton*> unocccupied;

};

#endif // GAMEBOARD_H
