/* Simple XCB application drawing a box in a window */
/* to compile it use :
 gcc -Wall x.c -lxcb
*/

/*
https://blogs.gnome.org/clutter/about/

decide to use <clutter> build my lemontea.
because they are basically the GNOME team
and base on OpenGL/OpenGL|ES for mobile

they are [LGPL2.1] maybe that will be the problem
*/
#include <xcb/xcb.h>
#include <stdio.h>
#include <stdlib.h>

//global draw context
xcb_connection_t    *c;
xcb_screen_t        *s;
xcb_window_t         w;
xcb_gcontext_t       g;
xcb_generic_event_t *e;

//--------------------
#include "monkc.h"
#include "MCArray.h"

monkc(MCPoint);
    double x;
    double y;
end(MCPoint);

monkc(MCSize);
    double width;
    double height;
end(MCSize);

monkc(MCRect);
    MCPoint origin;
    MCSize size;
end(MCRect);

inline MCRect mcrect(double x, double y, double width, double height)
{
    MCRect frame;
    frame.origin.x = x;
    frame.origin.y = y;
    frame.size.width = width;
    frame.size.height = height;
    return frame;
}

monkc(MCNode);
    MCRect frame;
    struct MCNode_struct *parent;
    MCArray *children;
end(MCNode);

method(MCNode, MCNode*, initWithFrame, MCRect frame);
method(MCNode, MCNode*, addChild, MCNode* child);
method(MCNode, void, draw, xxx);

initer(MCNode)
{
    obj->super = nil;
    obj->children = new(MCArray);
    return obj;
}

method(MCNode, void, bye, xxx)
{
    //clean up
    release(obj->children);
}

method(MCNode, MCNode*, initWithFrame, MCRect frame)
{
    obj->frame = frame;
    return obj;
}

method(MCNode, MCNode*, addChild, MCNode* child)
{
    retain(child);
    call(obj->children, MCArray, addItem, child);
    return child;
}

static draw_use_xcb(xcb_rectangle_t *xcb_rect)
{
    xcb_poly_fill_rectangle(c, w, g, 1, xcb_rect);
}

method(MCNode, void, draw, xxx)
{
    //draw self
    xcb_rectangle_t rect = {obj->frame.origin.x,
                            obj->frame.origin.y,
                            obj->frame.size.width,
                            obj->frame.size.height};
    draw_use_xcb(&rect);
    //draw children
    int i;
    for(i=0; i<obj->children->count; i++)
    {
        MCNode* child = call(obj->children, MCArray, getItemByIndex, i);
        if(child)
          call(child, MCNode, draw, nil);
    }
    return;
}

loader(MCNode)
{
    binding(MCNode, MCNode*, initWithFrame, MCRect frame);
    binding(MCNode, MCNode*, addChild, MCNode* child);
    binding(MCNode, void, draw, xxx);
    return claz;
}

//--------------------
void drawAll()
{
    MCNode* root = new(MCNode);
    ff(root, initWithFrame, mcrect(30,30,120,120));

    MCNode* node1 = new(MCNode);
    ff(node1, initWithFrame, mcrect(0,0,10,10));
    ff(root, addChild, node1);

    ff(root, draw, nil);
}

int main(void)
{
  //xcb_connection_t    *c;
  //xcb_screen_t        *s;
  //xcb_window_t         w;
  //xcb_gcontext_t       g;
  //xcb_generic_event_t *e;
  uint32_t             mask;
  uint32_t             values[2];
  int                  done = 0;
  xcb_rectangle_t      r = { 20, 20, 60, 60 };

                        /* open connection with the server */
  c = xcb_connect(NULL,NULL);
  if (xcb_connection_has_error(c)) {
    printf("Cannot open display\n");
    exit(1);
  }
                        /* get the first screen */
  s = xcb_setup_roots_iterator( xcb_get_setup(c) ).data;

                       /* create black graphics context */
  g = xcb_generate_id(c);
  w = s->root;
  mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
  values[0] = s->black_pixel;
  values[1] = 0;
  xcb_create_gc(c, g, w, mask, values);

                       /* create window */
  w = xcb_generate_id(c);
  mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  values[0] = s->white_pixel;
  values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
  xcb_create_window(c, s->root_depth, w, s->root,
                    10, 10, 400, 300, 1,
                    XCB_WINDOW_CLASS_INPUT_OUTPUT, s->root_visual,
                    mask, values);

                        /* map (show) the window */
  xcb_map_window(c, w);

  xcb_flush(c);

                        /* event loop */
  while (!done && (e = xcb_wait_for_event(c))) {
    switch (e->response_type & ~0x80) {
    case XCB_EXPOSE:    /* draw or redraw the window */
      //xcb_poly_fill_rectangle(c, w, g,  1, &r);

      drawAll();

      xcb_flush(c);
      break;
    case XCB_KEY_PRESS:  /* exit on key press */
      done = 1;
      break;
    }
    free(e);
  }
                        /* close connection to server */
  xcb_disconnect(c);

  return 0;
}
