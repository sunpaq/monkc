
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

inline MCColor mc_color(unsigned R, unsigned G, unsigned B)
{
    MCColor color = {R, G, B};
    return color;
}

const MCPoint mc_point_zero = {0,0};
const MCSize mc_size_zero   = {0,0};
const MCRect mc_rect_zero   = {0,0,0,0};

const MCColor mc_color_white  = {255,255,255};
const MCColor mc_color_black  = {0,0,0};
const MCColor mc_color_red    = {255,0,0};
const MCColor mc_color_green  = {0,255,0};
const MCColor mc_color_blue   = {0,0,255};
