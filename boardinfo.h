#ifndef BOARDINFO_H
#define BOARDINFO_H

#include <vector>
#include <utility>
#include "basic_defs.hpp"

class BoardInfo
{
public:
    typedef std::pair<int,int> cell_location;
    typedef std::pair<int,int> Direction;
    static constexpr Direction orig_dirs[] = {{-1,0},{-1,-1},{0,-1},{1,-1}};
    static const int ORIG_DIRECTIONS_NUM = sizeof(orig_dirs)/sizeof(orig_dirs[0]);
    static const int MIN_LINE_ELIMINATION_SIZE = 5;

    BoardInfo(BoardInterface &);
    void getStraitConnection( cell_location start,
        std::vector<cell_location> &connection);
    bool isInRange(int r, int c) {
        return r>=0 && r<BoardDim::ROWS_NUM && c>=0 && c<BoardDim::COLUMNS_NUM;
    }

private:
    BoardInterface &board;
};

#endif // BOARDINFO_H
