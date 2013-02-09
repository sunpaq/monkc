//please do not include the "MCRuntime.h"
//in protocol file!!!

#ifdef METHOD
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif

#ifdef BIND
have_method(DrawableProtocol, draw, xxx);
have_method(DrawableProtocol, erase, xxx);
have_method(DrawableProtocol, redraw, xxx);
#undef BIND
#endif