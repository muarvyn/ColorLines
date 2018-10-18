#include <utility>
#include <qdebug.h>
#include <QRandomGenerator>

#include "board.h"
#include "gamecontrol.h"

GameControl::GameControl(BoardInterface *bs, QObject *parent)
    : QObject(parent)
    , board(bs)
{

}

int GameControl::getUnoccupied(std::vector<std::pair<int,int>> &unoccupied)
{
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            if (board->getColorAt(r,c) == BallColor::none) {
                unoccupied.push_back(std::make_pair(r,c));
            }
        }
    }
    return static_cast<int>(unoccupied.size());
}

bool GameControl::generateRandomSpawn(
    std::vector<std::pair<int,int>> &spawn,
    std::vector<BallColor::type> &color)
{
    std::vector<std::pair<int,int>> unoccupied;
    getUnoccupied(unoccupied);
    std::random_shuffle(unoccupied.begin(), unoccupied.end());
    std::copy(unoccupied.begin(),
        std::min(unoccupied.end(), unoccupied.begin()+SPAWN_BALLS_NUM),
        std::back_inserter(spawn));

    for (int i=0; i<SPAWN_BALLS_NUM; ++i) {
        color.push_back(getRandomColor());
    }
    return spawn.size()<SPAWN_BALLS_NUM;
}

void GameControl::makeNextMove()
{
    //TOFIX: never called
}

BallColor::type GameControl::getRandomColor()
{
    return static_cast<BallColor::type>(
        QRandomGenerator::global()->bounded(BallColor::yellow+1/*BallColor::last+1*/));
}
/*
void GameControl::updateNextSpawn()
{
    for (BallColor::type *sc = &next_spawn[0];
        sc < &next_spawn[SPAWN_BALLS_NUM];
        ++sc) {
        *sc = getRandomColor();
    }
}

std::pair<BallColor::type *, BallColor::type *> GameControl::getNextSpawn()
{
    return std::make_pair(&next_spawn[0], &next_spawn[SPAWN_BALLS_NUM]);
}
*/
void GameControl::getStraitConnection(
    const BoardInfo::cell_location &loc,
    std::vector<BoardInfo::cell_location> &connection)
{
    BoardInfo bi(*board);
    bi.getStraitConnection(
        BoardInfo::cell_location(loc.first, loc.second),
        connection);
}

void GameControl::handleMove(const BoardInfo::cell_location &loc)
{
    //TOFIX: never called
    qDebug() << "GameControl::handleMove: cell location is " << loc << "\n";

    std::vector<BoardInfo::cell_location> connection;
    BoardInfo bi(*board);
    bi.getStraitConnection(
        BoardInfo::cell_location(loc.first, loc.second),
        connection);
}

