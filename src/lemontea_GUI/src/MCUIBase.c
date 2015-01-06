
#include "MCUIBase.h"

inline MCPoint mc_point(double x, double y)
{
    MCPoint point = {x, y};
    return point;
}

inline MCPoint* mc_point_copy(MCPoint* A, MCPoint B)
{
    A->x = B.x;
    A->y = B.y;
    return A;
}

inline MCSize mc_size(double width, double height)
{
    MCSize point = {width, height};
    return point;
}

inline MCRect mc_rect(double x, double y, double width, double height)
{
    MCRect frame = {{x, y}, {width, height}};
    return frame;
}

inline int mc_rect_contains(MCRect* rect, MCPoint point)
{
    double deltax = point.x - rect->origin.x;
    double deltay = point.y - rect->origin.y;
    if(deltax >= 0 && deltax <= rect->size.width)
       if(deltay >= 0 && deltay <= rect->size.height)
         return 1;
    return 0;
}

inline MCColor mc_color(unsigned R, unsigned G, unsigned B)
{
    MCColor color = {R, G, B};
    return color;
}

inline MCColor mc_color_mix(MCColor A, MCColor B)
{
    MCColor mixed = {A.R+B.R, A.G+B.G, A.B+B.B};
    return mixed;
}

const MCPoint mc_point_zero = {0,0};
const MCSize mc_size_zero   = {0,0};
const MCRect mc_rect_zero   = {0,0,0,0};

const MCColor mc_color_white  = {255,255,255};
const MCColor mc_color_black  = {0,0,0};
const MCColor mc_color_red    = {255,0,0};
const MCColor mc_color_green  = {0,255,0};
const MCColor mc_color_blue   = {0,0,255};
