#include <memory>

#include <QRandomGenerator>

#include "animatediconbutton.h"
#include "board.h"
#include "dijkstra_search.hpp"

Board::Board(AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM],
    QObject *parent) : QObject(parent), board(board), dijkstra(nullptr)
{

}

BallColor::type Board::getRandom()
{
    return static_cast<BallColor::type>(QRandomGenerator::global()->bounded(5));
}

void Board::getOccupiedMap(distance_type wmap[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM])
{
    int i=0;
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            wmap[i++] = board[r][c]->getState() == CellButton::UNOCCUPIED ? 1.E-5 : 1.;
        }
    }
}

void Board::makeDijkstraSearch(int start_r, int start_c)
{
    distance_type wmap[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM];
    getOccupiedMap(wmap);
    dijkstra = std::make_shared<DijkstraSearch>(
        DijkstraSearch::board_graph::vertex_descriptor (start_r,start_c), wmap
        );
}

Board::distance_type Board::getDistance(int dest_r, int dest_c)
{
    return dijkstra != nullptr ? dijkstra->getDistance(dest_r, dest_c) : -1.;
}

Board::distance_type Board::getReversePathTo(int dest_r, int dest_c,
    std::vector<std::pair<int,int>> &path)
{
    if (dijkstra == nullptr) return -1.;
    distance_type d = dijkstra->getDistance(dest_r,dest_c);
    for (std::pair<int,int> predecessor = dijkstra->getPredecessor(dest_r,dest_c);
        !(predecessor.first == dest_r && predecessor.second == dest_c);
        dest_r = predecessor.first, dest_c = predecessor.second,
        predecessor = dijkstra->getPredecessor(dest_r,dest_c))
    {
        path.push_back(predecessor);
    }
    return d;
}
