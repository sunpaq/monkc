#include "monkc.h"

#ifndef _MCUIBase_
#define _MCUIBase_

monkc(MCPoint);
    double x;
    double y;
end(MCPoint);

monkc(MCSize);
    double width;
    double height;
end(MCSize);

monkc(MCRect);
    MCPoint origin;
    MCSize size;
end(MCRect);

extern inline MCRect mc_rect(double x, double y, double width, double height);

extern const MCPoint mc_point_zero;
extern const MCSize  mc_size_zero;
extern const MCRect  mc_rect_zero;

#endif
