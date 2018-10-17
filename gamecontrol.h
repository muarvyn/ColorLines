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
    void updateNextSpawn();
    std::pair<BallColor::type *, BallColor::type *> getNextSpawn();
    int getUnoccupied(std::vector<std::pair<int,int>> &unoccupied);
    bool generateRandomSpawn(std::vector<std::pair<int,int>> &spawn);
    static BallColor::type getRandomColor();

signals:

public slots:
    void makeNextMove();
//    void handleMove(AnimatedIconButton *btn);
    void handleMove(const BoardInfo::cell_location &loc);

private:
    BallColor::type next_spawn[SPAWN_BALLS_NUM];
    BoardInterface *board;
};

#endif // GAMECONTROL_H
