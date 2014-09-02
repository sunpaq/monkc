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

  MCNode* root = new(MCNode);
  MCNode* node1 = new(MCNode);
  ff(root, initWithFrame, mc_rect(30,30,120,120));
  ff(node1, initWithFrame, mc_rect(0,0,10,10));
  ff(root, addChild, node1);

  int done = 0;
  xcb_generic_event_t       *event;
  xcb_motion_notify_event_t *mevent;

  while (!done && (event = xcb_wait_for_event(ctx->connection))) {
    switch (event->response_type & ~0x80) {
    case XCB_EXPOSE:
      ff(root, draw, nil);
      break;
    case XCB_MOTION_NOTIFY:
      mevent = event;
      MCPoint point = {};
      break;
    case XCB_KEY_PRESS:
      done = 1;
      break;
    }
    free(event);
  }

  MCXCBContext_releaseInstance();
  return 0;
}
