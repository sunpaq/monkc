#include "MCContext.h"

#include "VTable.h"
#include "VTableSuper.h"
#include "Bird.h"

void mocha_syntex_test(MCContext* const context);
void menu_drive_test(MCContext* const context);

/* main */
int MCContext_runloop(MCContext* const context){
	mocha_syntex_test(context);
	menu_drive_test(context);

}

void menu_drive_test(MCContext* const context)
{
	int selection = ff(context, MT(showMenuAndGetSelectionChar), 3, "male", "female", "double");
	//printf("selection is: %c\n", putchar(selection));
	//printf("context->selectionChar is: %c\n", context->selectionChar);

	while(ff(context, MT(showConfirmAndGetBOOL), "are you sure")!=YES){
		ff(context, MT(showMenuAndGetSelectionChar), 3, "male", "female", "double");
	}
	//printf("%d\n", bb);
	printf("%s\n", "your name please:");
	char name[100];
	ff(context, MT(getUserInputString), name);
	
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
	ff(context, MT(dump), nil);

	//check whether have cmdline parameter "-c"
	BOOL res;
	if(res = ff(context, MT(havePara), "-c"))
		debug_log("%d %s\n", res,ff(context, MT(getPara), 1));

	//check whether have cmdline parameter "-w"
	if(ff(context, MT(havePara), "-w"))
		debug_log("%s\n", "context have -w para");

	//twice new test
	New(VTable, ret, nil);
	New(VTable, ret2, nil);

	//call by string
	ff(ret2,"draw",nil);

	//protocol method call
	ff(ret,MT(erase),nil);
	ff(ret,MT(redraw),nil);
	New(VTableSuper ,ret_father, nil);
	ff(ret_father, MT(draw), nil);
	ff(ret_father, MT(erase), nil);
	ff(ret_father, MT(redraw), nil);

	//nested method call
	ff(ret, MT(bmethod), 
		ff(ret,MT(amethod),nil), 
		3.1415, "this is amethod");

	//inherit test
	ff(ret, MT(show), YES, "this is a super method called by child:VTable");
	ff(ret2, MT(show), YES, "this is a super method called by child:VTable ret2");


	//polymorphism test
	New(Bird, duck, DUCK_TYPE);
	ff(duck, MT(fly), nil);

	New(Bird, chicken, CHICKEN_TYPE);
	ff(chicken, MT(fly), nil);

	New(Bird, bird, NONE);
	ff(bird, MT(fly), nil);

	//clean up controlled by cmdline parameter
	if(ff(context, MT(havePara), "--release")){
		release(ret);
		release(ret2);
		release(ret_father);
		release(duck);
		release(chicken);
		release(bird);
	}

	LOG_LEVEL=DEBUG;
}
