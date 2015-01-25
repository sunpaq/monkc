#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//all the X11 stuff is installed in /opt/X11 on Mac OS
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

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

#define MCLensStandard50mm (0.050)
#define MCLensWide24mm     (0.024)
#define MCLensLong100mm    (0.100)
#define MCLensLong200mm    (0.200)

#define MCRatioCameraFilm3x2    (3.0/2.0)
#define MCRatioOldTV4x3         (4.0/3.0)
#define MCRatioHDTV16x9         (16.0/9.0)
#define MCRatioCinema239x100    (2.39/1.0)
#define MCRatioMake(w, h)       ((double)w / (double)h)

typedef struct {
    double x;
    double y;
    double z;  
} MCVertex;

inline MCVertex MCVertexMake(double x, double y, double z) {
    return (MCVertex){x, y, z};
}

inline void putMCVertexes(MCVertex verp[], int size) {
    int i;
    for(i=0; i<size; i++) {
        glVertex3f(verp[i].x, verp[i].y, verp[i].z);
    }
}

//for upvertex use (tht + 90)
MCVertex MCVertexFromSpherical(double R, double tht, double fai) {
    double x = R * sin(tht) * cos(fai);
    double y = R * sin(tht) * sin(fai);
    double z = R * cos(tht);
    return (MCVertex){x,y,z};
}

//the unit is metre
void setupCamera(double ratio, double focal_length, double max_distance, MCVertex position, MCVertex lookat, MCVertex up) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //left right bottom top near far (135film 36mm x 24mm)
    glFrustum(-0.012*ratio, 0.012*ratio, -0.012, 0.012, focal_length, max_distance);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //eyeX eyeY eyeZ centerX centerY centerZ upX upY upZ
    gluLookAt(position.x, position.y, position.z,
	      lookat.x,   lookat.y,   lookat.z,
	      up.x,       up.y,       up.z);
}

void setupCameraSpherical(double ratio, double focal_length, double max_distance, double R, double tht, double fai, MCVertex lookat) {
    MCVertex position = MCVertexFromSpherical(R, tht, fai);
    MCVertex up       = MCVertexFromSpherical(R, tht+90, fai);
    setupCamera(ratio, focal_length, max_distance, position, lookat, up);
}

void ClearScreen() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DrawGround() {
    double R = 100.0;
    double D = 10.0;
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(R,  -D,  R);
    glVertex3f(-R, -D,  R);
    glVertex3f(-R, -D, -R);
    glVertex3f(R,  -D, -R);
    glEnd();
}

void DrawACube() {
    double R = 0.50;
    MCVertex v1 = {R,  R,  R};
    MCVertex v2 = {-R, R,  R};
    MCVertex v3 = {-R, -R, R};
    MCVertex v4 = {R,  -R, R};

    MCVertex v5 = {R,  R,  -R};
    MCVertex v6 = {-R, R,  -R};
    MCVertex v7 = {-R, -R, -R};
    MCVertex v8 = {R,  -R, -R};

    MCVertex faceFront[4] = {v1, v2, v3, v4};
    MCVertex faceBack[4]  = {v5, v6, v7, v8};
    MCVertex faceLeft[4]  = {v5, v1, v4, v8};
    MCVertex faceRight[4] = {v2, v6, v7, v3};
    MCVertex faceTop[4]   = {v5, v6, v2, v1};
    MCVertex faceBottom[4]= {v8, v7, v3, v4};

    //front
    glBegin(GL_QUADS);
    glColor3f(0., 1., 0.);
    putMCVertexes(faceFront, 4);
    glEnd();

    //back
    glBegin(GL_QUADS);
    glColor3f(1., 1., 0.);
    putMCVertexes(faceBack, 4);
    glEnd();

    //left
    glBegin(GL_QUADS);
    glColor3f(0., 1., 1.);
    putMCVertexes(faceLeft, 4);
    glEnd();

    //right
    glBegin(GL_QUADS);
    glColor3f(1., 0.5, 1.);
    putMCVertexes(faceRight, 4);
    glEnd();

    //top
    glBegin(GL_QUADS);
    glColor3f(1., 0., 1.);
    putMCVertexes(faceTop, 4);
    glEnd();

    //bottom
    glBegin(GL_QUADS);
    glColor3f(1., 0., 0.);
    putMCVertexes(faceBottom, 4);
    glEnd();   
}

static double degree = 0;
static double tht = 0;
static double fai = 0;

int main(int argc, char *argv[]) {

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

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask;

    win = XCreateWindow(dpy, root, 0, 0, 900, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(dpy, win);
    XStoreName(dpy, win, "Lemontea 3D");
 
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);
 
    glEnable(GL_DEPTH_TEST); 

    while(1) {
        XNextEvent(dpy, &xev);
        
        if(xev.type == Expose) {
            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
	    setupCamera(MCRatioMake(gwa.width, gwa.height),
			MCLensStandard50mm, 100,
			MCVertexMake(10.0,10.0,10.0), MCVertexMake(0,0,0), MCVertexMake(0,1.0,0));
            ClearScreen();
	    //DrawGround();
	    DrawACube();
            glXSwapBuffers(dpy, win);
        }else if(xev.type == KeyPress) {
            setupCameraSpherical(MCRatioMake(gwa.width, gwa.height),
				 MCLensStandard50mm, 100,
				 17.32, tht, fai, MCVertexMake(0,0,0));
	    tht = tht + 0.2;
	    fai = fai + 2.0;

	    ClearScreen();
	    //DrawGround();
	    DrawACube();
            glXSwapBuffers(dpy, win);
	  
	  /*
	    glXMakeCurrent(dpy, None, NULL);
            glXDestroyContext(dpy, glc);
            XDestroyWindow(dpy, win);
            XCloseDisplay(dpy);
            exit(0);
          */
	  
	  //degree = degree + 5;
	  //glRotatef(degree, 0.0, 1.0, 0.0);
          //glXSwapBuffers(dpy, win);

	  //printf("a frame");
        }
    }
}

