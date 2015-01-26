#ifndef _MC3DBase
#define _MC3DBase

#include <GL/gl.h>

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
inline MCVertex MCVertexFromSpherical(double R, double tht, double fai) {
    double x = R * sin(tht) * cos(fai);
    double y = R * sin(tht) * sin(fai);
    double z = R * cos(tht);
    return (MCVertex){x,y,z};
}

//for OpenGL bridge
inline void MCGLFrustumView(double left, double right,
			    double top, double bottom,
			    double near, double far) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(left, right, top, bottom, near, far);
}

inline void MCGLLookat(double eyeX,    double eyeY,    double eyeZ,
		       double centerX, double centerY, double centerZ,
		       double upX,     double upY,     double upZ) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
}

inline void MCGLLookatSpherical(double centerX, double centerY, double centerZ,
				double R, double tht, double fai) {
    MCVertex position = MCVertexFromSpherical(R, tht, fai);
    MCVertex up       = MCVertexFromSpherical(R, tht+90, fai);
    MCGLLookat(position.x, position.y, position.z,
	       centerX,    centerY,    centerZ,
	       up.x,       up.y,       up.z);
}

#endif
