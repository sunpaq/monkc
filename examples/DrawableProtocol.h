//please do not include the "MCRuntime.h"
//in protocol file!!!

#ifdef METHOD
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif

#ifdef BIND
binding(DrawableProtocol, draw, xxx);
binding(DrawableProtocol, erase, xxx);
binding(DrawableProtocol, redraw, xxx);
#undef BIND
#endif