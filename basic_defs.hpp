#ifndef BASIC_DEFS_HPP
#define BASIC_DEFS_HPP

#include <cstddef>
struct BallColor
{
    enum type {brown, red, green, blue, yellow, pink, navy, first=brown, last=navy};
    static const std::size_t colors_num = static_cast<std::size_t>(last+1);
};

struct BoardDim
{
    static const int ROWS_NUM = 9;
    static const int COLUMNS_NUM = 9;
};

#endif // BASIC_DEFS_HPP
