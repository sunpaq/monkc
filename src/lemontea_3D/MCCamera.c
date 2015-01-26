#include "MCCamera.h"

initer(MCCamera)
{
    var(super) = nil;
    call(obj, MCCamera, reset, nil);
    return obj;
}

method(MCCamera, void, reset, xxx)
{
    var(ratio) = MCRatioCameraFilm3x2;
    var(focal_length) = MCLensStandard50mm;
    var(max_distance) = 100;//100 metres
    var(lookat) = MCVertexMake(0,0,0);
    //spherical coor
    var(R) = 10;
    var(tht) = 0.5;
    var(fai) = 0.5;
    call(obj, MCCamera, update, nil);
}

method(MCCamera, MCVertex, position, xxx)
{
    return MCVertexFromSpherical(obj->R, obj->tht, obj->fai);
}

method(MCCamera, MCVertex, up, xxx)
{
    return MCVertexFromSpherical(obj->R, obj->tht+90, obj->fai);
}

method(MCCamera, void, updateRatioFocalDistance, xxx)
{
    //left right bottom top near far (135film 36mm x 24mm)
    MCGLFrustumView(-0.012*var(ratio),
	             0.012*var(ratio),
	            -0.012,
	             0.012,
	             var(focal_length),
	             var(max_distance));
}

method(MCCamera, void, updateLookat, xxx)
{
    MCGLLookatSpherical(var(lookat).x, var(lookat).y, var(lookat).z,
		        var(R),        var(tht),      var(fai));
}

method(MCCamera, void, update, xxx)
{
    call(obj, MCCamera, updateRatioFocalDistance, nil);
    call(obj, MCCamera, updateLookat, nil);
}

loader(MCCamera)
{
    binding(MCCamera, void, reset, xxx);
    binding(MCCamera, MCVertex, position, xxx);
    binding(MCCamera, MCVertex, up, xxx);
    binding(MCCamera, void, updateRatioFocalDistance, xxx);
    binding(MCCamera, void, updateLookat, xxx);
    binding(MCCamera, void, update, xxx);
    return claz;
}

