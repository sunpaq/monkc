#include "MCXCBContext.h"

#define DEBUG_SCREEN_INFO

/*
typedef struct {
    xcb_window_t   root;
    xcb_colormap_t default_colormap;
    uint32_t       white_pixel;
    uint32_t       black_pixel;
    uint32_t       current_input_masks;
    uint16_t       width_in_pixels;
    uint16_t       height_in_pixels;
    uint16_t       width_in_millimeters;
    uint16_t       height_in_millimeters;
    uint16_t       min_installed_maps;
    uint16_t       max_installed_maps;
    xcb_visualid_t root_visual;
    uint8_t        backing_stores;
    uint8_t        save_unders;
    uint8_t        root_depth;
    uint8_t        allowed_depths_len;
} xcb_screen_t;
*/
static printScreenInfo(xcb_screen_t* screen)
{
    printf("------ X Screen Info ------\n");
    printf("white_pixel:%d\n",           screen->white_pixel);
    printf("black_pixel:%d\n",           screen->black_pixel);
    printf("current_input_masks:%d\n",   screen->current_input_masks);
    printf("---------------------------\n");
    printf("width_in_pixels:%d\n",       screen->width_in_pixels);
    printf("height_in_pixels:%d\n",      screen->height_in_pixels);
    printf("width_in_millimeters:%d\n",  screen->width_in_millimeters);
    printf("height_in_millimeters:%d\n", screen->height_in_millimeters);
    printf("min_installed_maps:%d\n",    screen->min_installed_maps);
    printf("max_installed_maps:%d\n",    screen->max_installed_maps);
    printf("---------------------------\n");
    printf("backing_stores:%d\n",        screen->backing_stores);
    printf("save_unders:%d\n",           screen->save_unders);
    printf("root_depth:%d\n",            screen->root_depth);
    printf("allowed_depths_len:%d\n",    screen->allowed_depths_len);
    printf("---------------------------\n");
}

initer(MCXCBContext)
{
    obj->super = nil;
    obj->winframe = mc_rect(0,0,800,600);
    obj->wincolor = mc_color(41,41,41);
    obj->touch_observers = new(MCArray);

    //connet to X server
    obj->connection = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(obj->connection)) {
        printf("XCB cannot open display\n");
        exit(1);
    }

    //get the first screen from connection
    obj->screen = xcb_setup_roots_iterator(xcb_get_setup(obj->connection)).data;
#ifdef DEBUG_SCREEN_INFO
    printScreenInfo(obj->screen);
#endif

    //alloc background color
    MCColorReply* bgreply = MCXCBContext_allocColorFor(obj, obj->wincolor);
    MCPixel bgpixel = bgreply->pixel;
    free(bgreply);

    //alloc foreground color
    MCColorReply* fgreply = MCXCBContext_allocColorFor(obj, mc_color(255,255,255));
    MCPixel fgpixel = fgreply->pixel;
    free(fgreply);

    //create window
    obj->mask = XCB_CW_BACK_PIXEL
              | XCB_CW_EVENT_MASK;
    obj->value[0] = bgpixel;
    obj->value[1] = XCB_EVENT_MASK_EXPOSURE
                  | XCB_EVENT_MASK_KEY_PRESS
                  | XCB_EVENT_MASK_BUTTON_PRESS
                  | XCB_EVENT_MASK_POINTER_MOTION
                  | XCB_EVENT_MASK_BUTTON_MOTION;
    obj->window = xcb_generate_id(obj->connection);
    xcb_create_window(obj->connection,
                      XCB_COPY_FROM_PARENT,               //depth same as root
                      obj->window,
                      obj->screen->root,
                      obj->winframe.origin.x,             //x, y
                      obj->winframe.origin.y,
                      obj->winframe.size.width,
                      obj->winframe.size.height,          //width, height
                      1,                                  //border_width
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      obj->screen->root_visual,
                      obj->mask,
                      obj->value);

    //show (map) the window on screen
    xcb_map_window(obj->connection, obj->window);

    //create graphic context
    obj->gctx = xcb_generate_id(obj->connection);
    obj->mask = XCB_GC_FOREGROUND
              | XCB_GC_GRAPHICS_EXPOSURES;
    obj->value[0] = fgpixel;
    obj->value[1] = 0;
    xcb_create_gc(obj->connection,
                  obj->gctx,
                  obj->screen->root,
                  obj->mask,
                  obj->value);

    //used to flush all the pending requests, make sure command are sent
    xcb_flush(obj->connection);
    //xcb_aux_sync(obj->connection);

    //finish the X window initialize
    return obj;
}

static MCXCBContext* _instance = nil;
MCXCBContext* MCXCBContext_instance()
{
    if(!_instance) {
        _instance = new(MCXCBContext);
    }
    return _instance;
}

void MCXCBContext_releaseInstance()
{
    release(_instance);
    _instance = nil;
}

void MCXCBContext_flush()
{
    xcb_flush(_instance->connection);
}

MCColorReply* MCXCBContext_allocColor(MCColor color)
{
    return MCXCBContext_allocColorFor(_instance, color);
}

MCColorReply* MCXCBContext_allocColorFor(MCXCBContext* obj, MCColor color)
{
    MCColorReply* pointer;
    xcb_alloc_color_cookie_t cookie;
    cookie = xcb_alloc_color(obj->connection,
                             obj->screen->default_colormap,
                             color.R*255, color.G*255, color.B*255);
    pointer = xcb_alloc_color_reply(obj->connection, cookie, NULL);
    return pointer;
}

void MCXCBContext_fillRect(MCRect *rect)
{
    if(_instance && rect) {
        xcb_rectangle_t xrect = {rect->origin.x,
                                 rect->origin.y,
                                 rect->size.width,
                                 rect->size.height};

        xcb_poly_fill_rectangle(_instance->connection,
                                _instance->window,
                                _instance->gctx,
                                1, &xrect);
    }
}

void MCXCBContext_fillRectColor(MCRect *rect, MCColor color)
{
    MCPixel drawpixel = MCXCBContext_allocColorFor(_instance, color)->pixel;
    call(_instance, MCXCBContext, changeAttribute, XCB_GC_FOREGROUND, drawpixel);
    MCXCBContext_fillRect(rect);
}

void MCXCBContext_clearRect(MCRect *rect)
{
    MCXCBContext_fillRectColor(rect, _instance->wincolor);
}

void MCXCBContext_clear()
{
    MCXCBContext_fillRectColor(&_instance->winframe, _instance->wincolor);
}

method(MCXCBContext, void, bye, xxx)
{
    //cleanup here
    xcb_disconnect(obj->connection);
}

method(MCXCBContext, MCXCBContext*, findMCXCBContext, xxx)
{
    return obj;
}

method(MCXCBContext, void, updateAttribute, xxx)
{
    obj->cookie = xcb_change_gc(obj->connection,
                                obj->gctx,
                                obj->mask,
                                obj->value);
}

method(MCXCBContext, void, changeAttribute, MCXCBContextMask mask, const uint32_t *valuelist)
{
    obj->mask = mask;
    obj->value[0] = valuelist;
    call(obj, MCXCBContext, updateAttribute, nil);
}

method(MCXCBContext, void, registerTouchObserver, mo observer)
{
    call(obj->touch_observers, MCArray, addItem, observer);
}

method(MCXCBContext, void, unregisterTouchObserver, mo observer)
{
    call(obj->touch_observers, MCArray, removeItem, observer);
}

static void visiter(_lamda, void* item, int index, void* data)
{
    mo observer = cast(mo, item);
    MCPoint* point = cast(MCPoint*, data);
    ff(observer, onTouchEvent, *point);
}

method(MCXCBContext, void, notifyTouchObservers, MCPoint point)
{
    MCArray* array = obj->touch_observers;
    ff(array, visiteEachWithData, lamda(visiter), &point);

    // int i;
    // for(i=0; i<array->count; i++) {
    //    mo item = call(array, MCArray, getItemByIndex, i);
    //    ff(item, onTouchEvent, point);
    // }
}

loader(MCXCBContext)
{
    binding(MCXCBContext, void, bye, xxx);
    binding(MCXCBContext, MCXCBContext*, findMCXCBContext, xxx);
    binding(MCXCBContext, void, updateAttribute, xxx);
    binding(MCXCBContext, void, changeAttribute, uint32_t mask, const uint32_t *valuelist);
    binding(MCXCBContext, void, registerTouchObserver, mo observer);
    binding(MCXCBContext, void, unregisterTouchObserver, mo observer);
    binding(MCXCBContext, void, notifyTouchObservers, xxx);
    return claz;
}
