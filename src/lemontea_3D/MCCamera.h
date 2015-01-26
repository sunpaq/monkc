#include "monkc.h"

#ifndef _MCCamera
#define _MCCamera

#include "MC3DBase.h"

monkc(MCCamera);
    double ratio;
    double focal_length;
    double max_distance;
    MCVertex lookat;
    //spherical coordinate
    double R;
    double tht;
    double fai;
end(MCCamera);

method(MCCamera, void, reset, xxx);
method(MCCamera, MCVertex, position, xxx);
method(MCCamera, MCVertex, up, xxx);
method(MCCamera, void, updateRatioFocalDistance, xxx);
method(MCCamera, void, updateLookat, xxx);
method(MCCamera, void, update, xxx);

#define MCLensStandard50mm (0.050)
#define MCLensWide24mm     (0.024)
#define MCLensLong100mm    (0.100)
#define MCLensLong200mm    (0.200)

#define MCRatioCameraFilm3x2    (3.0/2.0)
#define MCRatioOldTV4x3         (4.0/3.0)
#define MCRatioHDTV16x9         (16.0/9.0)
#define MCRatioCinema239x100    (2.39/1.0)
#define MCRatioMake(w, h)       ((double)w / (double)h)

#endif
