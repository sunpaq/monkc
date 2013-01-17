//please do not include the "MCRuntime.h"
//in protocol file!!!

#ifdef METHOD 
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif

#ifdef BIND
bind_method(this, MK(draw), MV(DrawableProtocol, draw));
bind_method(this, MK(erase), MV(DrawableProtocol, erase));
bind_method(this, MK(redraw), MV(DrawableProtocol, redraw));
#undef BIND
#endif