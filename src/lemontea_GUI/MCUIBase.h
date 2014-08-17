#include "monkc.h"
#include "MCArray.h"

#ifndef _MCUIBase_
#define _MCUIBase_

//global draw context
extern xcb_connection_t    *c;
extern xcb_screen_t        *s;
extern xcb_window_t         w;
extern xcb_gcontext_t       g;
extern xcb_generic_event_t *e;

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

extern inline MCRect mcrect(double x, double y, double width, double height);

monkc(MCNode);
    MCRect frame;
    struct MCNode_struct *parent;
    MCArray *children;
end(MCNode);

method(MCNode, MCNode*, initWithFrame, MCRect frame);
method(MCNode, MCNode*, addChild, MCNode* child);
method(MCNode, void, draw, xxx);

#endif
