#include <stdio.h>
#include <stdlib.h>
//all the X11 stuff is installed in /opt/X11 on Mac OS
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include "MC3DBase.h"
#include "MCCamera.h"
#include "MC3DShapeBase.h"

Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;
XFontStruct*            fnt;

void ClearScreen() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void setupX() {
    dpy = XOpenDisplay(NULL);
 
    if(dpy == NULL) {
        printf("cannot connect to X server\n");
        exit(0);
    }

    root = DefaultRootWindow(dpy);
    vi = glXChooseVisual(dpy, 0, att);

    if(vi == NULL) {
        printf("no appropriate visual found\n");
        exit(0);
    } else {
        printf("visual %p selected\n", (void *)vi->visualid); 
        /* %p creates hexadecimal output like in glxinfo */
    }

    //set font
    const char * fontname = "-*-helvetica-*-r-*-*-14-*-*-*-*-*-*-*";
    fnt = XLoadQueryFont (dpy, fontname);
    /* If the font could not be loaded, revert to the "fixed" font. */
    if (! fnt) {
        //fprintf (stderr, "unable to load font %s: using fixed\n", fontname);
        fnt = XLoadQueryFont (dpy, "fixed");
    }
    if (fnt) {
      //XSetFont(dpy, glc, fnt->fid);
    }
    
    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 900, 600, 0,
			vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask, &swa);
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Lemontea 3D");
 
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
 
    glEnable(GL_DEPTH_TEST);
}

void DrawText(int x, int y, const char* text, int size) {
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;
    XTextExtents (fnt, text, size,
		  & direction, & ascent, & descent, & overall);
    XDrawString(dpy, root, glc, x, y, text, size);
}

int main(int argc, char *argv[]) {

    setupX();
    MCCamera* camera = new(MCCamera);

    while(1) {
        XNextEvent(dpy, &xev);
        
        if(xev.type == Expose) {
            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
	    //setting camera
	    camera->ratio = MCRatioMake(gwa.width, gwa.height);
            camera->R = 17.32;
	    call(camera, MCCamera, update, nil);
	    
            ClearScreen();
	    //DrawGround();
	    //DrawText(0,0, "this is a 3D demo", 18);
	    DrawACube();
            glXSwapBuffers(dpy, win);
        }else if(xev.type == KeyPress) {
	  KeySym ks = XLookupKeysym(&xev.xkey, 0);
            switch(ks) {
	      case XK_Left:
		camera->fai = camera->fai + 0.1;
		break;
	      case XK_Right:
		camera->fai = camera->fai - 0.1;
		break;
	      case XK_Up:
		camera->tht = camera->tht + 0.1;
		break;
	      case XK_Down:
		camera->tht = camera->tht - 0.1;
                break;
	      default:
	        break;
	    }
	    
	    call(camera, MCCamera, updateLookat, nil);
	    ClearScreen();
	    //DrawGround();
	    DrawACube();
            glXSwapBuffers(dpy, win);
        }
    }
}

