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
    LittleBird* abird = hew(LittleBird, 506760431);
    LittleBird* bbird = hew(LittleBird, 506760431);
    release(bbird);

    //static call methods
    LittleBird_fly(abird, 0, nil);
    LittleBird_eat(abird, 0, nil);
    LittleBird_swim(abird,0, nil);
    
    //dynamic call methods
    fh(abird,fly, 101491, nil);
    fh(abird,swim, 3543688, nil);
    fh(abird,eat, 100184, nil);
    
    //call abs method
    fh(abird,hello_abs, 1197016965, nil);
    fh(abird,land_abs, 2677951518, nil);
    
    //dynamic call super class methods
    int fatherage = (int)fh(abird,getAge, 3045599689, nil);
    printf("my father age is : %d\n", fatherage);
    
    recycle(abird);
}

#include "MCString.h"
#include "MCClock.h"
#include "MCIO.h"

void testLemontea()
{
    
    MCString* mcstr = ff(hew(MCString, 2872462663), initWithCString, "a MCString");
    ff(mcstr, add, " the second");
    ff(mcstr, add, " the third");
    ff(mcstr, add, " the forth\n");
    
    // int i;
    // for (i=0; i<100; i++) {
    //     int old = LOG_LEVEL;
    //     LOG_LEVEL = MC_ERROR_ONLY;
    //     ff(mcstr, add, " a piece of string");
    //     LOG_LEVEL = old;
    // }
    fh(mcstr,print, 106934957, nil);
    release(mcstr);
    
    MCClock* mcclock = ff(hew(MCClock, 1601663000), setTimeToNow, nil);
    fh(mcclock,printTime, 2497993498, nil);
    fh(mcclock,printCurrentGMTTime, 1939388559, nil);
    recycle(mcclock);

    MCFile* afile = MCFile_newReadWrite("mcfile.txt", 1);
    char buff[1024] = "this is a file";
    int res = call(afile, MCFile, writeToBegin, 8, buff, 64);
    printf("writeToBegin result: %d errno: %d\n", res, errno);
    call(afile, MCFile, printAttribute, nil);
    release(afile);

    MCCharBuffer* charbuff = CopyToCharBuffer(NewMCCharBuffer(64*sizeof(char)), 
    	"this is a stream make it longer to find out why it is cutted\n");
    MCString* mcstring = ff(hew(MCString, 2872462663), initWithCString, 
    	"this is a stream make it longer to find out why it is cutted\n");
    MCStream* stream = ff(hew(MCStream, 2872458422), newWithPath, readwrite_fullbuffered, "mcstream.txt");
    fh(stream,putCString, 569138245, charbuff);
    fh(stream,putMCString, 2748809558, mcstring);

    release(stream);
    ReleaseMCBuffer(charbuff);
    release(mcstring);

}

void test(MCContext* context)
{
	printf("%s\n", "----------");
	printf("%s\n", "ctl+c to exit");
	printf("%s\n", "----------");

	char selection = call(context,
		MCContext,
		showMenuAndGetSelectionChar, 
		5,
		"menu_drive_test", 
		"MCSocket(Server) --- use one termial process run this", 
		"MCSocket(Client) --- use another termial process run this",
        "test monkc",
        "test lemontea"
                         
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
	        case '2':{
		    char serverip[32];
		    printf("input your ip:");
		    fh(context,getUserInputString, 1145369978, serverip);
                    mocha_serversocket_test(serverip);
		    break;
		}
	        case '3':{
		    char serverip[32];
		    printf("input the server side ip you want connect:");
		    fh(context,getUserInputString, 1145369978, serverip);
		    mocha_clientsocket_test(context, serverip);
	            break;
		}
	        case '4':testMonkC();break;
                case '5':testLemontea();break;
        
		//case '6':mocha_exception_test();break;
		//case '7':test_MCThread();break;
		//case '8':test_MCProcess();break;
		//case '9':test_ffi();break;
	}
}


int main(int argc, char const *argv[])
{
		//LOG_LEVEL = MC_VERBOSE;
		//LOG_LEVEL = MC_DEBUG;
	
		monkc_runtime_check();
//		test_method_jumpping();
		test_object_life_cycle();

		MCContext* context = hew(MCContext, 1685319481);
		context->argc = argc;
		context->argv = cast(char**, argv);
		for(;;)
			test(context);

		release(context);

	return 0;
}
