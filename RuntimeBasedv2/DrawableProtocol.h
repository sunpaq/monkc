//please do not include the "MCRuntime.h"
//in protocol file!!!

#ifdef METHOD
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif

#ifdef BIND
have_method(DrawableProtocol, draw);
have_method(DrawableProtocol, erase);
have_method(DrawableProtocol, redraw);
#undef BIND
#endif