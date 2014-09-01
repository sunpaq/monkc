
#include "MCUIBase.h"

inline MCRect mc_rect(double x, double y, double width, double height)
{
    MCRect frame;
    frame.origin.x = x;
    frame.origin.y = y;
    frame.size.width = width;
    frame.size.height = height;
    return frame;
}

const MCPoint mc_point_zero = {0,0};
const MCSize mc_size_zero = {0,0};
const MCRect mc_rect_zero = {0,0,0,0};
