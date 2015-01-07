binding(MCTouchbleProtocol, void, onTouchEvent, MCPoint point);

/*
protocol(MCTouchbleProtocol, void, onTouchEvent, MCPoint point)
{
    MCNode* node = cast(MCNode*, obj);
    if(mc_rect_contains(&node->frame, point)) {
        node->color = mc_color_mix(node->color, mc_color(128,0,0));
    }
}
*/