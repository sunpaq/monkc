#include <xcb/xcb.h>

#include "monkc.h"
#include "MCUIBase.h"
#include "MCArray.h"

#ifndef MCXCBContext_
#define MCXCBContext_

typedef enum {
    GC_FUNCTION,
    GC_PLANE_MASK,
    GC_FOREGROUND,
    GC_BACKGROUND,
    GC_LINE_WIDTH,
    GC_LINE_STYLE,
    GC_CAP_STYLE,
    GC_JOIN_STYLE,
    GC_FILL_STYLE,
    GC_FILL_RULE,
    GC_TILE,
    GC_STIPPLE,
    GC_TILE_STIPPLE_ORIGIN_X,
    GC_TILE_STIPPLE_ORIGIN_Y,
    GC_FONT,
    GC_SUBWINDOW_MODE,
    GC_GRAPHICS_EXPOSURES,
    GC_CLIP_ORIGIN_X,
    GC_CLIP_ORIGIN_Y,
    GC_CLIP_MASK,
    GC_DASH_OFFSET,
    GC_DASH_LIST,
    GC_ARC_MODE,
    GC_ENUM_MAX
} MCXCBContextMask;

typedef uint32_t                MCPixel;
typedef xcb_alloc_color_reply_t MCColorReply;
typedef xcb_gcontext_t          MCUIAttribute;

monkc(MCXCBContext);
    MCRect              winframe;
    MCColor             wincolor;
    xcb_connection_t    *connection;
    xcb_screen_t        *screen;
    xcb_drawable_t      window;
    xcb_void_cookie_t   cookie;
    xcb_gcontext_t      gctx;
    uint32_t            mask;
    uint32_t            value[GC_ENUM_MAX];
    MCArray*            touch_observers;
end(MCXCBContext);

//MCXCBContext is singleton class
extern MCXCBContext* MCXCBContext_instance();
extern void MCXCBContext_releaseInstance();

//color
extern MCColorReply* MCXCBContext_allocColor(MCColor color);
extern MCColorReply* MCXCBContext_allocColorFor(MCXCBContext* obj, MCColor color);

//draw primitives
extern void MCXCBContext_flush();
extern void MCXCBContext_fillRect(MCRect *rect);
extern void MCXCBContext_fillRectColor(MCRect *rect, MCColor color);
extern void MCXCBContext_clearRect(MCRect *rect);
extern void MCXCBContext_clear();

//special used methods
method(MCXCBContext, void, bye, xxx);
method(MCXCBContext, MCXCBContext*, findMCXCBContext, xxx);

//handle attribute
method(MCXCBContext, void, changeAttribute, MCXCBContextMask mask, const uint32_t *valuelist);
method(MCXCBContext, void, updateAttribute, xxx);

//touch event
method(MCXCBContext, void, registerTouchObserver, mo observer);
method(MCXCBContext, void, unregisterTouchObserver, mo observer);
method(MCXCBContext, void, notifyTouchObservers, MCPoint point);

#endif
