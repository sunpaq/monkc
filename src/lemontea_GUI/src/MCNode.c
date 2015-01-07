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

method(MCNode, void, bye, xxx)
{
    //clean up
    release(var(children));
}

method(MCNode, MCNode*, findMCNode, xxx)
{
    return obj;
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

protocol(MCTouchbleProtocol, void, onTouchEvent, MCPoint point)
{
    varscope(MCNode);
    if(mc_rect_contains(addrof(obj->frame), point)) {
        var(color) = mc_color_mix(obj->color, mc_color(128,0,0));
    }
}

protocol(MCAccessbleProtocol, void*, access, const char* propertyName)
{
    varscope(MCNode);
         if (SEQ(S(frame),    propertyName)) return addrof(obj->frame);
    else if (SEQ(S(anchor),   propertyName)) return addrof(obj->anchor);
    else if (SEQ(S(position), propertyName)) return addrof(obj->position);
    else if (SEQ(S(color),    propertyName)) return addrof(obj->color);
    else {
        mc_message msg = _response_to(var(super), propertyName, 2);
        if (msg.object)
            _push_jump(msg, propertyName);
        else
            return nil;
    }
}

loader(MCNode)
{
    #include "MCTouchbleProtocol.h"
    #include "MCAccessbleProtocol.h"

    binding(MCNode, void, bye, xxx);
    binding(MCNode, MCNode*, findMCNode, xxx);
    binding(MCNode, MCNode*, initWithFrame, MCRect frame);
    binding(MCNode, MCNode*, initWithSize, MCSize size);
    binding(MCNode, MCNode*, addChild, MCNode* child);
    binding(MCNode, void, draw, xxx);
    return claz;
}
