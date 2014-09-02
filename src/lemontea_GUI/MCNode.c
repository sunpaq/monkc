#include <xcb/xcb.h>
#include "MCUIBase.h"
#include "MCNode.h"
#include "MCXCBContext.h"

initer(MCNode)
{
    obj->super = nil;

    obj->frame = mc_rect_zero;
    obj->anchor = mc_point_zero;
    obj->position = mc_point_zero;
    obj->parent = nil;
    obj->children = new(MCArray);

    return obj;
}

method(MCNode, void, bye, xxx)
{
    //clean up
    release(obj->children);
}

method(MCNode, MCNode*, findMCNode, xxx)
{
    return obj;
}

method(MCNode, MCNode*, initWithFrame, MCRect frame)
{
    obj->frame = frame;
    return obj;
}

method(MCNode, MCNode*, initWithSize, MCSize size)
{
    obj->frame = mc_rect(0, 0, size.width, size.height);
    return obj;
}

method(MCNode, MCNode*, addChild, MCNode* child)
{
    retain(child);
    child->parent = obj;
    call(obj->children, MCArray, addItem, child);
    return child;
}

method(MCNode, void, draw, xxx)
{
    //draw self
    MCXCBContext_fillRect(&(obj->frame));

    //draw children
    int i;
    for(i=0; i<obj->children->count; i++)
    {
        MCNode* child = call(obj->children, MCArray, getItemByIndex, i);
        if(child)
          call(child, MCNode, draw, nil);
    }

    MCXCBContext_flush();
    return;
}

loader(MCNode)
{
    binding(MCNode, void, bye, xxx);
    binding(MCNode, MCNode*, findMCNode, xxx);
    binding(MCNode, MCNode*, initWithFrame, MCRect frame);
    binding(MCNode, MCNode*, initWithSize, MCSize size);
    binding(MCNode, MCNode*, addChild, MCNode* child);
    binding(MCNode, void, draw, xxx);
    return claz;
}
