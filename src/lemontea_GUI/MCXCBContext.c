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

    //create window
    obj->window = xcb_generate_id(obj->connection);
    xcb_create_window(obj->connection,
                      XCB_COPY_FROM_PARENT, //depth same as root
                      obj->window,
                      obj->screen->root,
                      0, 0,                 //x, y
                      800, 600,             //width, height
                      1,                    //border_width
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      obj->screen->root_visual,
                      0,
                      NULL);

    //show (map) the window on screen
    xcb_map_window(obj->connection, obj->window);

    //create graphic context
    obj->gctx = xcb_generate_id(obj->connection);
    obj->mask = XCB_GC_FOREGROUND;
    obj->value[0] = obj->screen->black_pixel;
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
    MCXCBContext_instance();
    xcb_flush(_instance->connection);
}

void MCXCBContext_fillRect(MCRect *rect)
{
    MCXCBContext_instance();
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

method(MCXCBContext, void, changeAttribute, uint32_t mask, const uint32_t *valuelist)
{
    obj->mask = mask;
    obj->value[0] = valuelist;
    call(obj, MCXCBContext, updateAttribute, nil);
}

loader(MCXCBContext)
{
    binding(MCXCBContext, void, bye, xxx);
    binding(MCXCBContext, MCXCBContext*, findMCXCBContext, xxx);
    binding(MCXCBContext, void, updateAttribute, xxx);
    binding(MCXCBContext, void, changeAttribute, uint32_t mask, const uint32_t *valuelist);

    return claz;
}
