#ifndef _MC3DShapeBase
#define _MC3DShapeBase

#include "MC3DBase.h"

extern inline void DrawGround() {
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

extern inline void DrawACube() {
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

#endif

