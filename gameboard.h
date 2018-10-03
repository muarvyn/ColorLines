#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "board.h"

class GameBoard : public Board
{
    Q_OBJECT

public:
    static const int doze_size = 3;
    static const int MIN_LINE_ELIMINATION_SIZE = 5;

    typedef std::pair<int,int> Direction;
    static constexpr Direction orig_dirs[] = {{-1,0},{-1,-1},{0,-1},{1,-1}};
    static const int ORIG_DIRECTIONS_NUM = sizeof(orig_dirs)/sizeof(orig_dirs[0]);

    explicit GameBoard(
        AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM]
        , QObject *parent = nullptr);

    bool isInRange(int r, int c) {
        return r>=0 && r<BoardDim::ROWS_NUM && c>=0 && c<BoardDim::COLUMNS_NUM;
    }
    int getUnoccupied(std::vector<const AnimatedIconButton*> &unoccupied);
    bool getRandomVacantDoze(const AnimatedIconButton* vacant[doze_size]);
    void getElimination(int r, int c, std::vector<AnimatedIconButton*> &connection);
    virtual ~GameBoard() {}

private:

};

#endif // GAMEBOARD_H
