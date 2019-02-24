#include "basic_defs.hpp"

void operator++(BallColor::type& c)
{
    c=static_cast<BallColor::type>(c+1);
}
