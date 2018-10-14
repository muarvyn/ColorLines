//#include <utility>
#include <QRandomGenerator>

#include "board.h"
#include "gamecontrol.h"

GameControl::GameControl(BoardInterface *bs, QObject *parent)
    : QObject(parent)
    , board(bs)
{
    updateNextSpawn();
}

void GameControl::makeNextMove()
{
    updateNextSpawn();
/*
    const AnimatedIconButton *first_doze[GameBoard::doze_size];
    if (board->getRandomVacantDoze(first_doze)) {
        for (int i=0; i<GameBoard::doze_size; ++i) {
            AnimatedIconButton *btn =
                boardCells[first_doze[i]->getRow()][first_doze[i]->getColumn()];
            int state = Board::getRandom();
            btn->setupAnimation("opacity", 0, 1, 600, state);
            btn->startAnimation(state);
        }
    }
*/
}

BallColor::type GameControl::getRandomColor()
{
    return static_cast<BallColor::type>(
        QRandomGenerator::global()->bounded(BallColor::yellow+1/*BallColor::last+1*/));
}

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

/*
void GameControl::handleMove(AnimatedIconButton *btn)
{
    std::vector<AnimatedIconButton*> connection;
    board->getElimination(btn->getRow(), btn->getColumn(), connection);

    if (connection.size() > 0) {
        for (std::vector<AnimatedIconButton*>::iterator i = connection.begin();
            i < connection.end();
            ++i) {
            startEliminationAnimation(*i);
        }
        connect(btn, &AnimatedIconButton::animation_finished, this,
            [this
//            , btn
            ] {
//                disconnect(btn, &AnimatedIconButton::animation_finished, nullptr, nullptr);
                this->makeNextMove();
            });
        startEliminationAnimation(btn);
    } else {
        this->makeNextMove();
    }
}
*/
