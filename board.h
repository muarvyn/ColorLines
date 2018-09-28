#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <QObject>
QT_BEGIN_NAMESPACE
class AnimatedIconButton;
QT_END_NAMESPACE
class DijkstraSearch;
#include "basic_defs.hpp"

class Board : public QObject
{
    Q_OBJECT

public:
    typedef double distance_type;

    static BallColor::type getRandom();

//    bool isOccupied();

    explicit Board(AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM]
        , QObject *parent = nullptr);

    void getOccupiedMap(distance_type wmap[BoardDim::ROWS_NUM*BoardDim::COLUMNS_NUM]);
//    void getUnoccupied(std::vector<std::pair<int,int>> &unoccupied);
    void makeDijkstraSearch(int r, int c);
    double getReversePathTo(int dest_r, int dest_c, std::vector<std::pair<int,int>> &path);
    distance_type getDistance(int dest_r, int dest_c);
    virtual ~Board() {}

signals:

public slots:

protected:
    AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM];
    std::shared_ptr<DijkstraSearch> dijkstra;
};

#endif // BOARD_H
