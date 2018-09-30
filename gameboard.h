#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "board.h"

//typedef std::pair<int,int> Direction;
//const Direction dirs[] =
//        {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};

class GameBoard : public Board
{
    Q_OBJECT

public:
    static const int doze_size = 3;
    static const int MIN_LINE_ELIMINATION_SIZE = 5;

    typedef std::pair<int,int> Direction;
//    static constexpr Direction dirs[] =
//        {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
//    static const int DIRECTIONS_NUM = sizeof(dirs)/sizeof(dirs[0]);
    static constexpr Direction orig_dirs[] = {{-1,0},{-1,-1},{0,-1},{1,-1}};
    static const int ORIG_DIRECTIONS_NUM = sizeof(orig_dirs)/sizeof(orig_dirs[0]);
    //static const Direction orig_dirs[];

    explicit GameBoard(
        AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM]
        , QObject *parent = nullptr);

    bool isInRange(int r, int c) {
        return r>=0 && r<BoardDim::ROWS_NUM && c>=0 && c<BoardDim::COLUMNS_NUM;
    }
    int getUnoccupied(std::vector<const AnimatedIconButton*> &unoccupied);
    bool getRandomVacantDoze(const AnimatedIconButton* vacant[doze_size]);
//    void getRayConnection(int r, int c, std::vector<AnimatedIconButton*> connection);
    void getElimination(int r, int c, std::vector<AnimatedIconButton*> &connection);
    virtual ~GameBoard() {}

private:

};

#endif // GAMEBOARD_H
