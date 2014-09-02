#include <xcb/xcb.h>

#include "monkc.h"
#include "MCUIBase.h"

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

monkc(MCXCBContext);
    MCRect              rootrect;
    xcb_connection_t    *connection;
    xcb_screen_t        *screen;
    xcb_drawable_t      window;
    xcb_void_cookie_t   cookie;
    xcb_gcontext_t      gctx;
    uint32_t            mask;
    uint32_t            value[GC_ENUM_MAX];
end(MCXCBContext);

extern MCXCBContext* MCXCBContext_instance();
extern void MCXCBContext_releaseInstance();
extern void MCXCBContext_flush();

//draw primitives
typedef xcb_gcontext_t MCUIAttribute;
extern void MCXCBContext_fillRect(MCRect *rect);

method(MCXCBContext, void, bye, xxx);
method(MCXCBContext, MCXCBContext*, findMCXCBContext, xxx);

method(MCXCBContext, void, changeAttribute, uint32_t mask, const uint32_t *valuelist);
method(MCXCBContext, void, updateAttribute, xxx);

#endif
