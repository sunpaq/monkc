#include "monkc.h"

#include "ClientServerExample.h"
#include "MenuDrivenExample.h"
#include "MethodJumpping.h"
#include "ObjectLifeCycle.h"

void monkc_runtime_check()
{
	const char* met1 = "method1";
	const char* met2 = "method2";
	const char* met3 = "method3";

	printf("method1 address: %ld\n", (unsigned long)met1);
	printf("method2 address: %ld\n", (unsigned long)met2);
	printf("method3 address: %ld\n", (unsigned long)met3);
}

void test(MCContext* context)
{
	printf("%s\n", "----------");
	printf("%s\n", "ctl+c to exit");
	printf("%s\n", "----------");

	int selection = call(context,
		MCContext,
		showMenuAndGetSelectionChar, 
		3, 
		"menu_drive_test", 
		"MCSocket(Server)", 
		"MCSocket(Client)"
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
		//case '6':mocha_exception_test();break;
		//case '7':test_MCThread();break;
		//case '8':test_MCProcess();break;
		//case '9':test_ffi();break;
	}
}

int main(int argc, char const *argv[])
{
	mc_init();
		LOG_LEVEL = MC_DEBUG;
		monkc_runtime_check();
//		test_method_jumpping();
		test_object_life_cycle();

		MCContext* context = new(MCContext);
		context->argc = argc;
		context->argv = argv;
		
		for(;;)
			test(context);

		release(context);

	mc_end();
	return 0;
}
