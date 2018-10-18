#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "basic_defs.hpp"
#include "boardinfo.h"

class BoardState;

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(BoardInterface *bs, QObject *parent = nullptr);
    //void updateNextSpawn();
    //std::pair<BallColor::type *, BallColor::type *> getNextSpawn();
    int getUnoccupied(std::vector<std::pair<int,int>> &unoccupied);
    bool generateRandomSpawn(
        std::vector<std::pair<int,int>> &spawn,
        std::vector<BallColor::type> &color);

    static BallColor::type getRandomColor();
    void getStraitConnection(
        const BoardInfo::cell_location &loc,
        std::vector<BoardInfo::cell_location> &connection);

signals:

public slots:
    void makeNextMove();
//    void handleMove(AnimatedIconButton *btn);
    void handleMove(const BoardInfo::cell_location &loc);

private:
    //BallColor::type next_spawn[SPAWN_BALLS_NUM];
    BoardInterface *board;
};

#endif // GAMECONTROL_H
