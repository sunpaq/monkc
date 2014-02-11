#include "monkc.h"

#include "ClientServerExample.h"
#include "MenuDrivenExample.h"
#include "MethodJumpping.h"
#include "ObjectLifeCycle.h"

#include "LittleBird.h"

void monkc_runtime_check()
{
	const char* met1 = "method1";
	const char* met2 = "method2";
	const char* met3 = "method3";

	printf("method1 address: %ld\n", (unsigned long)met1);
	printf("method2 address: %ld\n", (unsigned long)met2);
	printf("method3 address: %ld\n", (unsigned long)met3);
}

void testMonkC()
{
    //new a instance
    LittleBird* abird = new(LittleBird);
    
    //static call methods
    //LittleBird_fly(abird, abird, nil, nil);
    //LittleBird_eat(abird, abird, nil, nil);
    //LittleBird_swim(abird, abird, nil, nil);
    
    //dynamic call methods
    ff(abird, fly, nil);
    ff(abird, swim, nil);
    ff(abird, eat, nil);
    
    //call abs method
    ff(abird, hello_abs, nil);
    ff(abird, land_abs, nil);
    
    //dynamic call super class methods
    int fatherage = (int)ff(abird, getAge, nil);
    printf("my father age is : %d\n", fatherage);
    
    release(abird);
}

#include "MCString.h"
#include "MCClock.h"
#include "ObjCClass.h"

void testLemontea()
{
    MCString* mcstr = ff(new(MCString), initWithCString, "a MCString");
    ff(mcstr, add, " the second");
    ff(mcstr, add, " the third");
    ff(mcstr, add, " the forth\n");
    ff(mcstr, print, nil);
    release(mcstr);
    
    MCClock* mcclock = ff(new(MCClock), setTimeToNow, nil);
    ff(mcclock, printTime, nil);
    ff(mcclock, printCurrentGMTTime, nil);
    release(mcclock);
}

void callFromObjC()
{
    printf("\n<call from objc class>\n\n");
    ObjCClass* aobj = [ObjCClass new];
    [aobj callMonkCMethod];
}

void test(MCContext* context)
{
	printf("%s\n", "----------");
	printf("%s\n", "ctl+c to exit");
	printf("%s\n", "----------");

	int selection = call(context,
		MCContext,
		showMenuAndGetSelectionChar, 
		6,
		"menu_drive_test", 
		"MCSocket(Server) --- use one termial process run this", 
		"MCSocket(Client) --- use another termial process run this",
        "test monkc",
        "test lemontea",
        "test call from objc"
                         
		//"[x]syntex_test", 
		//"[x]lib_test", 
		//"[x]MCException", 
		//"[x]MCThread", 
		//"[x]MCProcess", 
		//"[x]ffi"
		);

	switch(selection){
		//case '1':mocha_syntex_test(context);break;
		case '1':menu_drive_test(context);break;
		//case '3':mocha_lib_test();break;
		case '2':mocha_serversocket_test();break;
		case '3':mocha_clientsocket_test(context);break;
        case '4':testMonkC();break;
        case '5':testLemontea();break;
        case '6':callFromObjC();break;
        
		//case '6':mocha_exception_test();break;
		//case '7':test_MCThread();break;
		//case '8':test_MCProcess();break;
		//case '9':test_ffi();break;
	}
}


int main(int argc, char const *argv[])
{
	mc_init();
		LOG_LEVEL = MC_ERROR_ONLY;
		monkc_runtime_check();
//		test_method_jumpping();
		test_object_life_cycle();

		MCContext* context = new(MCContext);
		context->argc = argc;
		context->argv = cast(char**, argv);
		for(;;)
			test(context);

		release(context);

	mc_end();
	return 0;
}
