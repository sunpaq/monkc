//please do not include the "MCRuntime.h"
//in protocol file!!!

#ifdef METHOD 
protocol(DrawableProtocol, draw, xxx);
protocol(DrawableProtocol, erase, xxx);
protocol(DrawableProtocol, redraw, xxx);
#undef METHOD
#endif

#ifdef BIND
bind(this, MK(draw), MV(DrawableProtocol, draw));
bind(this, MK(erase), MV(DrawableProtocol, erase));
bind(this, MK(redraw), MV(DrawableProtocol, redraw));
#undef BIND
#endif