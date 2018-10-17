#include "boardinfo.h"

BoardInfo::BoardInfo(BoardInterface &b)
    : board(b)
{

}

constexpr BoardInfo::Direction BoardInfo::orig_dirs[];

void BoardInfo::getStraitConnection( cell_location start,
        std::vector<cell_location> &connection)
{
    connection.clear();
    int state = board.getColorAt(start.first, start.second);
    if (state == BallColor::none) return;

    for (const Direction *dir = &orig_dirs[0];
        dir < &orig_dirs[ORIG_DIRECTIONS_NUM];
        ++dir) {
        int row=start.first, column=start.second;
        std::vector<cell_location> line;

        while (true) {
            row += dir->first;
            column += dir->second;
            if (!isInRange(row,column)) break;
            if (board.getColorAt(row,column) != state) break;
            line.push_back(cell_location(row,column));
        }
        row=start.first; column=start.second;
        while (true) {
            row -= dir->first;
            column -= dir->second;
            if (!isInRange(row,column)) break;
            if (board.getColorAt(row,column) != state) break;
            line.push_back(cell_location(row,column));
        }
        if (line.size() >= MIN_LINE_ELIMINATION_SIZE-1) { //TOFIX: it is not exactly expected behaviour
            std::copy(line.begin(), line.end(), std::back_inserter(connection));
        }
        line.clear();
    }
}
