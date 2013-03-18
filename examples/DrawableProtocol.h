//please do not include the "MCRuntime.h"
//in protocol file!!!

#ifdef METHOD
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif

#ifdef BIND
binding(MSNA, DrawableProtocol, draw, xxx);
binding(MSNA, DrawableProtocol, erase, xxx);
binding(MSNA, DrawableProtocol, redraw, xxx);
#undef BIND
#endif