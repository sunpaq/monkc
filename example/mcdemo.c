#include "Monkey.h"
#include "MonkeyExt.h"
#include "MCContext.h"
#include "SimpleServer.h"

void testOOP()
{
	Monkey* m = new(Monkey);
	//static call
	Monkey_info(m, 0);

	//dynamic call
	ff(m, showage, 0);
	ff(m, showname, 0);

	//call protocal Flyable
	ff(m, fly, 0);
	ff(m, takeoff, "yeah!");
	ff(m, landing, "OK");

	//call super class methods
	ff(m, eat, 0);
	ff(m, walk, 0);
	ff(m, sleep, 0);
	ff(m, breath, 0);
	ff(m, breed, 0);

	//call extensions
	ff(m, extensionMethod, 0);
	ff(m, extensionFunction, 0);

	//call an wrong method name
	ff(m, typo, 0);

	printf("%s\n", "finish");
}

void startServer()
{
	SimpleServer* server = new(SimpleServer);
	ff(server, start, 0);
}

int main(int argc, char const *argv[])
{
	extend(Monkey, Ext);

	MCContext* ctx = MCContext_newWithArgs(argc, (char**)argv);
	char c = MCContext_showMenuAndGetSelectionChar(5, 
	    "test OOP",
		"start Server", 
		"Male", 
		"Female", 
		"Unknown");

	switch(c) {
		case '1':
			testOOP();
			break;
		case '2':
			startServer();
			break;
		case '3':
			printf("%s\n", "Hi, boy!");
			break;
		case '4':
			printf("%s\n", "welcome, girl!");
			break;
		case '5':
			printf("%s\n", "Hey, welcome!");
			break;
		default:
			break;
	}

	return 0;
}