#include "MCContext.h"

#include "MCBuffer.h"
#include "MCClock.h"
#include "MCException.h"
#include "MCIO.h"
#include "MCMath.h"
#include "MCProcess.h"
#include "MCSocket.h"
#include "MCString.h"
#include "MCThread.h"

#include "VTable.h"
#include "VTableSuper.h"
#include "Bird.h"

#include "MCUnitTest.h"

void mocha_syntex_test(MCContext* context);
void menu_drive_test(MCContext* context);
void mocha_lib_test();
void mocha_serversocket_test();
void mocha_clientsocket_test(MCContext* context);
void mocha_exception_test();
void test_MCThread();
void test_MCProcess();
void test_ffi();

void test(MCContext* context);

extern void function();

/* 
main: Mocha hide the C main entry in MCRuntime.c
for some prepare works to do before any customer code.
and expose this MCContext_runloop to developers
argc and argv are wrapped into context
you can check the origin main code at MCRuntime.c line:27
*/

int main(int argc, char const *argv[])
{
	mc_init();
	LOG_LEVEL = DEBUG;
	MCContext* context = new(MCContext, argc, argv);

	for(;;)
		test(context);
	
	relnil(context);

	mc_end();
	return 0;
}

void test(MCContext* context)
{
	//pre load some classes
	printf("%s\n", "----------");
	// debug_log("%s\n", "preload some classes:");

	preload(Bird, DUCK_TYPE);
	preload(MCClock, nil);
	preload(MCMath, nil);
	preload(MCProcess, nil);
	preload(MCString, "a");

	int selection = call(context,
		MCContext,
		showMenuAndGetSelectionChar, 
		9, 
		"syntex_test", "menu_drive_test", "lib_test", "MCSocket(Server)", 
		"MCSocket(Client)", "MCException", "MCThread", "MCProcess", "ffi");

	switch(selection){
		case '1':mocha_syntex_test(context);break;
		case '2':menu_drive_test(context);break;
		case '3':mocha_lib_test();break;
		case '4':mocha_serversocket_test();break;
		case '5':mocha_clientsocket_test(context);break;
		case '6':mocha_exception_test();break;
		case '7':test_MCThread();break;
		case '8':test_MCProcess();break;
		case '9':test_ffi();break;

	}

}

// use thread pool to management them ?

MCMutexLockNew(lock) = MCMutexLockStaticInitializer;
void init_routine()
{
	MCMutexLock(lock);
	printf("%s\n", "init the thread only once!");
	MCMutexUnlock(lock);
}

MCMutexLockNew(withCond) = MCMutexLockStaticInitializer;
MCCondLockNew(cond) = MCCondLockStaticInitializer;
//MCSpinLockNew(spin); int test_spin_count=0;
void wait_routine()
{
	//MCSpinLockInit(spin ,YES);
		
	printf("%s\n", "wait for signal, block here");
	MCCondWait(cond, withCond);

	printf("%s\n", "received signal!!!");

	//MCSpinLock(spin);
	//printf("test_spin_count is:%d\n", test_spin_count);
	//MCSpinUnlock(spin);
}

void signal_routine()
{
	int i;
	for (i = 0; i < 10; ++i)
	{
		printf("%d seconds to signal\n", 10-i);
		sleep(1);
	}
	
	printf("%s\n", "signal!!!");
	MCCondSignal(cond);

	//MCSpinLock(spin);
	//test_spin_count++;
	//MCSpinUnlock(spin);

}



void test_MCClock()
{
	printf("---- test_MCClock START ----\n");
	//test MCClock
	MCClock* myclock = new(MCClock, nil);
	char* gmtnow = ff(myclock, getCurrentGMTTimeString, nil);
	char* now = ff(myclock, getCurrentTimeString, nil);

	debug_log("\nGMT time is:%s", gmtnow);
	debug_log("\njapan time is:%s", now);

	debug_log("%s\n", "time works fine");
	ff(myclock, printCurrentGMTTime, nil);
	ff(myclock, printCurrentTime, nil);
	
	clock_t clocks_per_second, clocks_since_start;
	ff(myclock, getCPUClocksPerSecond, &clocks_per_second);
	ff(myclock, getCPUClocksSinceStart, &clocks_since_start);
	debug_log("%ld\n", clocks_per_second);
	debug_log("%ld\n", clocks_since_start);

	//blank time
	ff(myclock, printTime, nil);
	//set time
	ff(myclock, setRawtimeFields, 59, 10, 21, 19, DEC, 2012, 3, 0, 0);
	ff(myclock, printTime, nil);
	//adjust time
	ff(myclock, setTimeToNow, nil);
	ff(myclock, printTime, nil);
	ff(myclock, adjustTime, 0, 0, 2, 0, 0, 0, 0);
	ff(myclock, printTime, nil);
	relnil(myclock);
	printf("---- test_MCClock END ----\n");
}

int mcprocess_flag = 0;
void mcprocess_atexit()
{
	//printf("%s\n", "this is child, mcprocess_atexit called");
	mcprocess_flag = 1;
}

void test_MCProcess()
{
	printf("---- test_MCProcess START ----\n");

	//test MCProcess
	MCProcess* p = new(MCProcess, nil);
		ff(p, printIDs, nil);
	relnil(p);

	MCProcess pp;//this will alloc a instance on stack?
	call(&pp, MCProcess, init, nil);
	ff(&pp, printIDs, nil);

	pid_t pid;
	if((pid=ff(&pp, fork, nil))==0){
		//child
		atexit(mcprocess_atexit);
		if(ff(&pp, registerAtExitCallback, mcprocess_atexit)==ERROR)
			printf("%s\n", "register atexit error");
		printf("%s\n", "this is child");
		sleep(2);
		exit(5);

	}else if(pid > 0){
		//parent
		int sta;
		if(ff(&pp, registerAtExitCallback, mcprocess_atexit)==ERROR)
			printf("%s\n", "register atexit error");

		while(ff(&pp, waitPIDChildExit, pid, &sta, WNOHANG)!=pid){
			usleep(500*1000);
			printf("%s\n", "this is parent...");
		}

		if(mcprocess_flag==1)printf("%s\n", "this is child, mcprocess_atexit called");
		printf("this is parent, child exit status is:[%d]\n", 
			ff(&pp, getChildExitLowOrder8Bit, sta));

	}else if(pid == -1){
		//error
		printf("%s\n", "fork error");
	}

	printf("---- test_MCProcess END ----\n");
}

void test_MCString()
{
	printf("---- test_MCString START ----\n");
	MCString* newstr = new(MCString, "a new string a");

	unsigned add_key = MK(add);//speed up looping
	int ix;
	for (ix = 0; ix < 20; ++ix)
	{
		_ff(newstr, add_key, " + with append info");
	}
	ff(newstr, print, nil);
	printf("length:%d size:%d\n", newstr->length, newstr->size);

	char csbuff[newstr->size];
	ff(newstr, toCString, csbuff);
	printf("the CString is:\n%s\n", csbuff);

	MCString* newstr2 = new(MCString, "a new string b");
	ff(newstr2, add, " + with append info");
	ff(newstr2, print, nil);

	MCString* astr = new(MCString, "string");
	if (ff(new_anony(MCString, "string"), equalTo, astr))
	{
		printf("two string is equal!!!\n");
	}

	ff(MCString_newForHttpAnony("www.google.com",NO), print, nil);

	printf("size is: %d\n", strlen("size of string"));
	printf("---- test_MCString END ----\n");

	relnil(newstr);
	relnil(newstr2);
	relnil(astr);

}

	#ifndef _MyRunnable
	#define _MyRunnable _MCRunnable
	class(MyRunnable);
	method(MyRunnable, run, xxx)
	{
		int i;
		for (i = 0; i < 10; ++i)
		{
			printf("%s\n", "i am a MCThread!");
			sleep(1);
		}
	}
	constructor(MyRunnable, _FunctionPointer(my_init_routine))
	{
		link_class(MyRunnable, MCRunnable, my_init_routine)
		{
			override(MyRunnable, run, xxx);
		}

		return this;
	}
	#endif

void test_MCThread()
{
	//gcc can define a function in function
	//so this class define also can be.

	/* inner runnable class */
	// #ifndef _MyRunnable
	// #define _MyRunnable _MCRunnable
	// class(MyRunnable);
	// method(MyRunnable, run, xxx)
	// {
	// 	int i;
	// 	for (i = 0; i < 10; ++i)
	// 	{
	// 		printf("%s\n", "i am a MCThread!");
	// 		sleep(1);
	// 	}
	// }
	// constructor(MyRunnable, _FunctionPointer(my_init_routine))
	// {
	// 	link_class(MyRunnable, MCRunnable, my_init_routine)
	// 	{
	// 		override(MCRunnable, run, xxx);
	// 	}

	// 	return this;
	// }
	// #endif

	printf("---- test_MCThread START ----\n");

	//test MCThread
	MCThread* m_thread = new(MCThread, new_anony(MyRunnable, init_routine));
	m_thread->isRunOnce = YES;
	//start once
	ff(m_thread, start, nil);
	ff(m_thread, start, nil);
	ff(m_thread, start, nil);
	ff(m_thread, start, nil);
	debug_log("tid is:%lu\n", m_thread->self);
	//release(m_thread);
	//MCThread_join(m_thread, nil);

	//equal
	if (ff(m_thread, equal, m_thread))
	{
		debug_log("m_thread is equal to m_thread!\n");
	}

	//the Mocha is not thread safe now!
	MCThread* m_thread2 = new(MCThread, new_anony(MyRunnable, nil));
	ff(m_thread2, start, nil);

	int i;
	for (i = 0; i < 12; ++i)
	{
		debug_log("this is Main thread!\n");
		sleep(1);
	}

	//join the m_thread, thread2 to main thread
	MCThread_join(m_thread2, nil);

	//test condition lock and spin lock
	MCThread* m_wait = new(MCThread, new_anony(MyRunnable, wait_routine));
	MCThread* m_signal = new(MCThread, new_anony(MyRunnable, signal_routine));
	ff(m_wait, start, nil);
	ff(m_signal, start, nil);

	MCThread_join(m_wait, nil);
	MCThread_join(m_signal, nil);

	printf("---- test_MCThread END ----\n");
}

void test_MCFile()
{
	char* str = "i_am_sun_and_i_create_this_file.";
	//char buff[4096];
	MCCharBuffer* buff = NewMCCharBuffer(4096);
	printf("current working directory: %s\n", MCProcess_getCurrentWorkingDir(buff));

	MCFile_chmod("temp.txt" ,S_IRWXU|S_IRWXG|S_IRWXO);
	MCFile* tmpfile = MCFile_newReadWrite("temp.txt", YES);
	MCFile_createSymbolLink("temp.txt", "temp.link");
	if(tmpfile!=nil){
		ff(tmpfile, writeToBegin, 0, str, strlen(str)+1);
		ff(tmpfile, readFromBegin, 0, sizeof(tmpfile->buffer));
		printf("content in file is: %s strlen is:%d\n", tmpfile->buffer, strlen(str)+1);
		ff(tmpfile, printAttribute, nil);
		release(tmpfile);
	}

	free(buff);
}

void test_MCStream()
{
	MCStream* stream = new(MCStream, readwrite_fullbuffered, "stream.txt");
	MCCharBuffer* buff = NewMCCharBuffer(1024);
	strcpy(buff->data, "this is a test line. haha\n");

	if(stream!=nil){
		ff(stream, putCString, buff);
		ff(stream, getCString, buff);
	}

	printf("%s\n", buff->data);

	free(buff);
	relnil(stream);
}

void mocha_lib_test()
{
	test_MCClock();

	test_MCString();
	test_MCStream();

	test_MCFile();
}

static int readline(int fd, char* const recvbuff)
{
	char onechar;
	char* ptr = recvbuff;
	int RETURN_VAL_END_OF_FILE = 0;
	while(read(fd, &onechar, 1)!=RETURN_VAL_END_OF_FILE){
		(*ptr++)=onechar;
		if (onechar=='\n')return 0;
	}
	return -1;
}

void mocha_serversocket_test()
{
	MCSocket* server = new(MCSocket, MCSocket_Server_TCP, "127.0.0.1", "4000");
	ff(server, listeningStart, nil);
	printf("%s\n", "MC server start to listenning");

	char *sendbuff[1024];
	char *recvbuff[1024];

	//use select()
	MCSelect* fdcontroler = new(MCSelect, 0, 0);
	ff(fdcontroler, addFd, MCSelect_Readfd, server->sfd);

	int client_array[100];
	memset(client_array, 0, sizeof(client_array));
	int client_count = 0;

	for(;;){

		printf("%s\n", "wait for message...");
		if(ff(fdcontroler, waitForFdsetChange, nil)<=0)//no time out
		{
			//[<0] error [=0] time out
			error_log("select error, or time out!\n");
			release(fdcontroler);
			release(server);
			exit(-1);
		}

		if (ff(fdcontroler, isFdReady, MCSelect_Readfd, server->sfd))
		{
			MCSocketClientInfo* request = ff(server, acceptARequest, nil);
			//get a empty client slot
			int i;
			for (i = 0; i < 100; ++i){
				if(client_array[i]==0)
				{
					client_array[i] = request->returnSfd;
					break;
				}
			}
			
			printf("accept a client: %d Total[%d]\n", i, ++client_count);
			ff(fdcontroler, addFd, MCSelect_Readfd, client_array[i]);
			release(request);
			continue;
		}

		int i;
		for(i=0; i<100; i++){

			if(client_array[i]==0)continue;

			if(ff(fdcontroler, isFdReady, MCSelect_Readfd, client_array[i])){
				memset(sendbuff, 0, 1024);
				memset(recvbuff, 0, 1024);

				if(readline(client_array[i], recvbuff)==-1){
					printf("a client quite: %d Total[%d]\n", i, --client_count);
					ff(fdcontroler, removeFd, MCSelect_Readfd, client_array[i]);
					close(client_array[i]);
					client_array[i]=0;
					break;
				}
				
				printf("get a message from: %d Total[%d] ---- %s", i, client_count, recvbuff);
			}
		}
	}
	release(server);
}

void mocha_clientsocket_test(MCContext* context)
{
	MCSocket* client = new(MCSocket, MCSocket_Client_TCP, "127.0.0.1", "4000");

	char sendbuff[1024];
	char recvbuff[1024];
	
	for(;;){
		memset(sendbuff, 0, 1024);
		printf("%s\n", "to Server: (your message please)");
		ff(context, getUserInputString, sendbuff);
		char* str = strcat(sendbuff, "\n");

		write(client->sfd, str, strlen(str));
	}

	release(client);
}

void menu_drive_test(MCContext* context)
{
	int selection = call(context, MCContext, showMenuAndGetSelectionChar, 3, "male", "female", "double");
	//printf("selection is: %c\n", putchar(selection));
	//printf("context->selectionChar is: %c\n", context->selectionChar);

	while(ff(context, showConfirmAndGetBOOL, "are you sure")!=YES){
		call(context, MCContext, showMenuAndGetSelectionChar, 3, "male", "female", "double");
	}
	//printf("%d\n", bb);
	printf("%s\n", "your name please:");
	char name[100];
	ff(context, getUserInputString, name);
	
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



void mocha_syntex_test(MCContext* context)
{
	//output all cmdline parameters
	ff(context, dumpParas, nil);

	debug_log("PATH: [%s]\n", ff(context, getEnvironmentVar, "PATH"));

	ff(new_anony(MCObject, nil), whatIsYourClassName, nil);

	//check whether have cmdline parameter "-c"
	BOOL res;
	if(res = ff(context, isHavePara, "-c"))
		debug_log("%d %s\n", res,ff(context, getPara, 1));

	//check whether have cmdline parameter "-w"
	if(ff(context, isHavePara, "-w"))
		debug_log("%s\n", "context have -w para");

	new_onstack(VTableSuper, nil);

	//twice new test
	new_onstack(VTable, nil);
	new_onstack(VTable, nil);

	//get singleton instance test
	VTable* ret2= VTable_getInstance();
	VTable* ret = VTable_getInstance();

	//call by string
	ff(VTable_getInstance(), draw, nil);

	//protocol method call
	ff(ret, erase, nil);
	ff(ret, redraw, nil);

	VTableSuper* ret_father = new(VTableSuper, nil);
	ff(ret_father, draw, nil);
	ff(ret_father, erase, nil);
	ff(ret_father, redraw, nil);

	//nested method call
	ff(ret, bmethod, 
		ff(ret, amethod, nil),
		pushv(3.1415), "this is amethod");

	//inherit test
	ff(ret, show, YES, "this is a super method called by child:VTable");
	ret2->info="Changed Info By VTable";
	ff(ret2, show, YES, "this is a super method called by child:VTable ret2");

	//ff-release
	ff(new_anony(VTableSuper, nil), draw, nil);

	//polymorphism test
	Bird* birdArray[3]={new_anony(Bird, DUCK_TYPE), new_anony(Bird, CHICKEN_TYPE), new_anony(Bird, NONE)};
	int i;
	for (i = 0; i < 3; ++i)
	{
		ff(birdArray[i], fly, nil);
	}

	ff(new_anony(Bird, DUCK_TYPE),    fly, nil);
	ff(new_anony(Bird, CHICKEN_TYPE), fly, nil);
	ff(new_anony(Bird, NONE),         fly, nil);

	//side effect: class method list change dynamically
	Bird* b1 = new(Bird, DUCK_TYPE);
	Bird* b2 = new(Bird, CHICKEN_TYPE);
	Bird* b3 = new(Bird, NONE);

	ff(b1, fly, nil);
	ff(b2, fly, nil);
	ff(b3, fly, nil);

	//clean up controlled by cmdline parameter
	//if(ff(context, isHavePara, "--release")){
		release(nil);
		relnil(ret);
		relnil(ret2);
		relnil(ret_father);
	//}

	//response
	Bird* abird = new(Bird, DUCK_TYPE);
	if (response(abird, whatIsYourClassName))
		ff(abird, whatIsYourClassName, nil);

	ff(abird, youCanNotResponseThis, nil);
	relnil(abird);
}

void test_ffi()
{
	VTable* tobeinvoke = new(VTable, nil);
	char* socool = "so cool";

	ff(tobeinvoke, bmethod, 10, pushv(9.99), "so cool");
	ff(tobeinvoke, cmethod, 10, pushv(9.88), socool);

	relnil(tobeinvoke);
}

void doSomething() throws(MCIOException);
void doSomething2() throws(MCIOException);
void doSomething3() throws(MCIOException);
void mocha_exception_test()
{
	//exception support
	try{
		doSomething();
		doSomething();//this will never be reach

		//doSomething2();
	}catch(MCRuntimeException){
		printf("%s\n", "MCRuntimeException raised");

	}catch(MCIOException){
		MCString* str = (MCString*)get_exception_data("MCIOException");
		if (str!=nil)
		{
			ff(str, add, "@this is append info");
			ff(str, print, nil);
			printf("%s\n", "MCIOException raised");
			//it will be auto released
			//relnil(str);
		}else{
			debug_log("get_exception_data return nil\n");
		}


	}catch(MyException){
		printf("%s\n", "MyException raised");

	}finally{
		printf("%s\n", "finally default handling");
	}
}

void doSomething() throws(MCIOException) {
	doSomething2();
	printf("%s\n", "doSomething this should never show");
}

void doSomething2() throws(MCIOException) {
	doSomething3();
	printf("%s\n", "doSomething2 this should never show");
}

void doSomething3() throws(MCIOException) {
	set_exception_data("MCIOException", new(MCString, "this is a MCIOException reason"));
	throw(MCIOException);
	printf("%s\n", "doSomething3 this should never show");
}