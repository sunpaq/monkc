#include <xcb/xcb.h>

#include "monkc.h"
#include "MCUIBase.h"

inline MCRect mcrect(double x, double y, double width, double height)
{
    MCRect frame;
    frame.origin.x = x;
    frame.origin.y = y;
    frame.size.width = width;
    frame.size.height = height;
    return frame;
}

initer(MCNode)
{
    obj->super = nil;
    obj->children = new(MCArray);
    return obj;
}

method(MCNode, void, bye, xxx)
{
    //clean up
    release(obj->children);
}

method(MCNode, MCNode*, initWithFrame, MCRect frame)
{
    obj->frame = frame;
    return obj;
}

method(MCNode, MCNode*, addChild, MCNode* child)
{
    retain(child);
    call(obj->children, MCArray, addItem, child);
    return child;
}

static draw_use_xcb(xcb_rectangle_t *xcb_rect)
{
    xcb_poly_fill_rectangle(c, w, g, 1, xcb_rect);
}

method(MCNode, void, draw, xxx)
{
    //draw self
    xcb_rectangle_t rect = {obj->frame.origin.x,
                            obj->frame.origin.y,
                            obj->frame.size.width,
                            obj->frame.size.height};
    draw_use_xcb(&rect);
    //draw children
    int i;
    for(i=0; i<obj->children->count; i++)
    {
        MCNode* child = call(obj->children, MCArray, getItemByIndex, i);
        if(child)
          call(child, MCNode, draw, nil);
    }
    return;
}

loader(MCNode)
{
    binding(MCNode, MCNode*, initWithFrame, MCRect frame);
    binding(MCNode, MCNode*, addChild, MCNode* child);
    binding(MCNode, void, draw, xxx);
    return claz;
}
