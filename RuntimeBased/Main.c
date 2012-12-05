#include "VTable.h"
#include "VTableSuper.h"
/* main */

int MCRuntime_runloop(MCContext* context){

	ff(context, MT(dump), nil);
	BOOL res;
	if(res = ff(context, MT(havePara), "-c"))
		printf("%d %s\n", res,ff(context, MT(getPara), 1));

	if(ff(context, MT(havePara), "-w"))
		printf("%s\n", "context have -w para");

	New(VTable, ret, nil);

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
		release(context);
	}
}