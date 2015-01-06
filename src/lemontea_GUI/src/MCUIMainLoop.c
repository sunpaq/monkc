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


//--------------------
#include "monkc.h"
#include "MCUIBase.h"
#include "MCNode.h"
#include "MCXCBContext.h"

//--------------------
int main(void)
{
  MCXCBContext* ctx = MCXCBContext_instance();

  MCNode* root  = new(MCNode);
  MCNode* node1 = new(MCNode);
  MCNode* node2 = new(MCNode);
  MCNode* node3 = new(MCNode);

  root->color  = mc_color_blue;
  node1->color = mc_color_green;
  node2->color = mc_color_red;
  node3->color = mc_color_mix(mc_color_red, mc_color_green);

  ff(root,  initWithFrame, mc_rect(30,30,160,120));
  ff(node1, initWithFrame, mc_rect(0,0,80,60));
  ff(node2, initWithFrame, mc_rect(0,0,40,30));
  ff(node3, initWithFrame, mc_rect(0,0,20,15));

  node1->anchor = mc_point(0.5, 0.5);
  node2->anchor = mc_point(0.5, 0.5);
  node3->anchor = mc_point(0.5, 0.5);
  node1->position = mc_point(80, 60);
  node2->position = mc_point(40, 30);
  node3->position = mc_point(20, 15);

  ff(root,  addChild, node1);
  ff(node1, addChild, node2);
  ff(node2, addChild, node3);

  ff(ctx, registerTouchObserver, root);

  int done = 0;
  xcb_generic_event_t       *event;
  xcb_motion_notify_event_t *motion;

  MCPoint mouse;

  while (!done && (event = xcb_wait_for_event(ctx->connection))) {
    switch (event->response_type & ~0x80) {
    case XCB_EXPOSE:
      MCXCBContext_clear();
      break;
    case XCB_MOTION_NOTIFY:
      MCXCBContext_clearRect(&root->frame);
      motion = event;
      mouse = mc_point(motion->event_x, motion->event_y);
      mc_point_copy(&root->frame.origin, mouse);
      break;
    case XCB_BUTTON_PRESS:
      ff(ctx, notifyTouchObservers, mouse);
      //if(mc_rect_contains(&root->frame, mouse))
      //    root->color = mc_color_mix(root->color, mc_color(0,0,128));
      break;
    case XCB_KEY_PRESS:
      //done = 1;
      root->color = mc_color_mix(root->color, mc_color(0,0,25.5));
      break;
    }

    ff(root, draw, nil);
    MCXCBContext_flush();
    free(event);
  }

  ff(ctx, unregisterTouchObserver, root);
  MCXCBContext_releaseInstance();
  return 0;
}
