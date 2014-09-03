#include "monkc.h"

#ifndef _MCUIBase_
#define _MCUIBase_

typedef struct MCPoint_struct {
    double x;
    double y;
} MCPoint;

typedef struct MCSize_struct {
    double width;
    double height;
} MCSize;

typedef struct MCRect_struct {
    MCPoint origin;
    MCSize size;
} MCRect;

typedef struct MCColor_struct {
    unsigned R;
    unsigned G;
    unsigned B;
} MCColor;

extern inline MCPoint mc_point(double x, double y);
extern inline MCPoint* mc_point_copy(MCPoint* A, MCPoint B);

extern inline MCSize  mc_size(double width, double height);
extern inline MCRect  mc_rect(double x, double y, double width, double height);
extern inline MCColor mc_color(unsigned R, unsigned G, unsigned B);
extern inline MCColor mc_color_mix(MCColor A, MCColor B);

const MCPoint mc_point_zero;
const MCSize  mc_size_zero;
const MCRect  mc_rect_zero;

const MCColor mc_color_white;
const MCColor mc_color_black;
const MCColor mc_color_red;
const MCColor mc_color_green;
const MCColor mc_color_blue;

#endif
