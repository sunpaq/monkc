#include "MCContext.h"

#include "VTable.h"
#include "VTableSuper.h"
#include "Bird.h"

void mocha_syntex_test(MCContext* const context);
void menu_drive_test(MCContext* const context);

/* main */
int MCContext_runloop(MCContext* const context){
	mocha_syntex_test(context);
	//menu_drive_test(context);

}

void menu_drive_test(MCContext* const context)
{
	int selection = ff(context, MK(showMenuAndGetSelectionChar), 3, "male", "female", "double");
	//printf("selection is: %c\n", putchar(selection));
	//printf("context->selectionChar is: %c\n", context->selectionChar);

	while(ff(context, MK(showConfirmAndGetBOOL), "are you sure")!=YES){
		ff(context, MK(showMenuAndGetSelectionChar), 3, "male", "female", "double");
	}
	//printf("%d\n", bb);
	printf("%s\n", "your name please:");
	char name[100];
	ff(context, MK(getUserInputString), name);
	
	char* sex;
	switch(selection){
		case '1':
			sex="Mr";
		break;
		case '2':
			sex="Miss";
		break;
		case '3':
			sex="Hi";
		break;
	}

	printf("%s %s %s\n", sex, name, "welcome to Mars");
}

void mocha_syntex_test(MCContext* const context)
{
	LOG_LEVEL=VERBOSE;

	//output all cmdline parameters
	ff(context, MK(dump), nil);

	//check whether have cmdline parameter "-c"
	BOOL res;
	if(res = ff(context, MK(havePara), "-c"))
		debug_log("%d %s\n", res,ff(context, MK(getPara), 1));

	//check whether have cmdline parameter "-w"
	if(ff(context, MK(havePara), "-w"))
		debug_log("%s\n", "context have -w para");

	//twice new test
	New(VTable, ret, nil);
	New(VTable, ret2, nil);

	//call by string
	ff(ret2,"draw",nil);

	//protocol method call
	ff(ret,MK(erase),nil);
	ff(ret,MK(redraw),nil);
	New(VTableSuper ,ret_father, nil);
	ff(ret_father, MK(draw), nil);
	ff(ret_father, MK(erase), nil);
	ff(ret_father, MK(redraw), nil);

	//nested method call
	ff(ret, MK(bmethod), 
		ff(ret,MK(amethod),nil), 
		3.1415, "this is amethod");

	//inherit test
	ff(ret, MK(show), YES, "this is a super method called by child:VTable");
	ret2->info="Changed Info By VTable";
	ff(ret2, MK(show), YES, "this is a super method called by child:VTable ret2");

	//polymorphism test
	New(Bird, b1, DUCK_TYPE);
	ff(b1, MK(fly), nil);

	New(Bird, b2, CHICKEN_TYPE);
	ff(b2, MK(fly), nil);

	New(Bird, b3, NONE);
	ff(b3, MK(fly), nil);

	//clean up controlled by cmdline parameter
	if(ff(context, MK(havePara), "--release")){
		release(ret);
		release(ret2);
		release(ret_father);
		release(b1);
		release(b2);
		release(b3);
	}

	LOG_LEVEL=DEBUG;
}
