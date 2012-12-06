#include "MCContext.h"

#include "VTable.h"
#include "VTableSuper.h"
#include "Bird.h"
/* main */
int MCContext_runloop(MCContext* const context){

	LOG_LEVEL=VERBOSE;

	ff(context, MT(dump), nil);
	BOOL res;
	if(res = ff(context, MT(havePara), "-c"))
		debug_log("%d %s\n", res,ff(context, MT(getPara), 1));

	if(ff(context, MT(havePara), "-w"))
		debug_log("%s\n", "context have -w para");

	New(VTable, ret, nil);
		New(VTable, ret2, nil);

	ff(ret,"draw",nil);
	ff(ret,MT(erase),nil);
	ff(ret,MT(redraw),nil);

	New(VTableSuper ,ret_father, nil);
	ff(ret_father, MT(draw), nil);
	ff(ret_father, MT(erase), nil);
	ff(ret_father, MT(redraw), nil);

	ff(ret, MT(bmethod), 
		ff(ret,MT(amethod),nil), 
		3.1415, "this is amethod");

	if(ff(context, MT(havePara), "--release")){
		release(ret);
		release(ret_father);
	}

	New(Bird, duck, DUCK_TYPE);
	ff(duck, MT(fly), nil);

	New(Bird, chicken, CHICKEN_TYPE);
	ff(chicken, MT(fly), nil);

	New(Bird, bird, NONE);
	ff(bird, MT(fly), nil);

	release(duck);
		//release(duck);

	release(chicken);
	release(bird);

}