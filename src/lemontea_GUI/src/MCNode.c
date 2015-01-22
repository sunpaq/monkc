#include <xcb/xcb.h>
#include "MCUIBase.h"
#include "MCNode.h"
#include "MCXCBContext.h"

initer(MCNode)
{
    var(super) = nil;

    var(frame) = mc_rect_zero;
    var(anchor) = mc_point_zero;
    var(position) = mc_point_zero;
    var(color) = mc_color_white;
    var(parent) = nil;
    var(children) = new(MCArray);

    return obj;
}

protocol(MCAccessbleProtocol, void*, access, const char* varname)
{
    varscope(MCNode);
    if (SEQ(S(frame),    varname)) return addrof(obj->frame);
    if (SEQ(S(anchor),   varname)) return addrof(obj->anchor);
    if (SEQ(S(position), varname)) return addrof(obj->position);
    if (SEQ(S(color),    varname)) return addrof(obj->color);
    void* varp = nil;
    varp = ff(obj->super, access, varname);
    return varp;
}

protocol(MCTouchbleProtocol, void, onTouchEvent, MCPoint point)
{
    varscope(MCNode);
    if(mc_rect_contains(addrof(obj->frame), point)) {
        var(color) = mc_color_mix(obj->color, mc_color(128,0,0));
    }
}

method(MCNode, void, bye, xxx)
{
    //clean up
    release(var(children));
}

method(MCNode, MCNode*, initWithFrame, MCRect frame)
{
    var(frame) = frame;
    return obj;
}

method(MCNode, MCNode*, initWithSize, MCSize size)
{
    var(frame) = mc_rect(0, 0, size.width, size.height);
    return obj;
}

method(MCNode, MCNode*, addChild, MCNode* child)
{
    retain(child);
    child->parent = obj;
    call(var(children), MCArray, addItem, child);
    return child;
}

static inline MCRect calculate_drawframe(MCNode* obj)
{
    MCNode* p = var(parent);
    if(p){
        MCRect frame = {
            p->frame.origin.x + var(position).x - var(anchor).x * var(frame).size.width,
            p->frame.origin.y + var(position).y - var(anchor).y * var(frame).size.height,
            var(frame).size.width,
            var(frame).size.height
        };
        var(frame) = frame;
        return frame;
    }else{
        //root node position and anchor are ignored
        return var(frame);
    }
}

method(MCNode, void, draw, xxx)
{
    //draw self
    MCRect drawframe = calculate_drawframe(obj);
    MCXCBContext_fillRectColor(&drawframe, var(color));

    //draw children
    int i;
    for(i=0; i<var(children)->count; i++)
    {
        MCNode* child = call(var(children), MCArray, getItemByIndex, i);
        if(child)
          call(child, MCNode, draw, nil);
    }

    MCXCBContext_flush();
    return;
}

loader(MCNode)
{
    #include "MCAccessbleProtocol.h"
    #include "MCTouchbleProtocol.h"
    binding(MCNode, void, bye, xxx);
    binding(MCNode, MCNode*, initWithFrame, MCRect frame);
    binding(MCNode, MCNode*, initWithSize, MCSize size);
    binding(MCNode, MCNode*, addChild, MCNode* child);
    binding(MCNode, void, draw, xxx);
    return claz;
}
