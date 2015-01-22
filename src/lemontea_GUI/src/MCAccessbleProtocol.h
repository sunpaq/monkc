binding(MCAccessbleProtocol, void*, access, const char* varname);

/*
protocol(MCAccessbleProtocol, void*, access, const char* varname)
{
    varscope(CLASS);
    if (SEQ(S(AAAA), varname)) return addrof(obj->AAAA);
    if (SEQ(S(BBBB), varname)) return addrof(obj->BBBB);
    if (SEQ(S(CCCC), varname)) return addrof(obj->CCCC);
    if (SEQ(S(DDDD), varname)) return addrof(obj->DDDD);
    void* varp = nil;
    varp = ff(obj->super, access, varname);
    return varp;
}
*/