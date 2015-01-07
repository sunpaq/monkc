binding(MCAccessbleProtocol, void*, access, const char* propertyName);

/*
protocol(MCAccessbleProtocol, void*, access, const char* propertyName)
{
    MCNode* node = cast(MCNode*, obj);
         if (SEQ(S(frame),    propertyName)) return addrof(node->frame);
    else if (SEQ(S(anchor),   propertyName)) return addrof(node->anchor);
    else if (SEQ(S(position), propertyName)) return addrof(node->position);
    else if (SEQ(S(color),    propertyName)) return addrof(node->color);
    else {
        mc_message msg = _response_to(node->super, propertyName);
        if (msg.object)
            _push_jump(msg, propertyName);
        else
            return nil;
    }
}
*/