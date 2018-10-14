#ifndef BASIC_DEFS_HPP
#define BASIC_DEFS_HPP

#include <cstddef>
struct BallColor
{
    enum type {brown, red, green, blue, yellow, pink, navy, first=brown, last=navy, none=-1};
    static const std::size_t colors_num = static_cast<std::size_t>(last+1);
};

struct BoardDim
{
    static const int ROWS_NUM = 9;
    static const int COLUMNS_NUM = 9;
};

const std::size_t SPAWN_BALLS_NUM = 3;

class ColorCell
{
public:
    virtual BallColor::type getColor() const = 0;
    virtual void setColor(BallColor::type color) = 0;
    virtual ~ColorCell();
};

class BoardInterface
{
public:
    virtual BallColor::type getColorAt(int r, int c) const = 0;
//    virtual ColorCell &getCellAt(int r, int c) const = 0;
    virtual ~BoardInterface();
};

#endif // BASIC_DEFS_HPP
