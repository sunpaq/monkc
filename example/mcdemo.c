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

	//call extensions
	ff(m, extensionMethod, 0);
	ff(m, extensionFunction, 0);

	//call an wrong method name
	ff(m, typo, 0);

	printf("%s\n", "finish");
}

int main(int argc, char const *argv[])
{
	extend(Monkey, Ext);

	MCContext* ctx = MCContext_newWithArgs(argc, (char**)argv);
	char c = MCContext_showMenuAndGetSelectionChar(4, 
		"test OOP", 
		"Male", 
		"Female", 
		"Unknown");

	switch(c) {
		case '1':
			testOOP();
			break;
		case '2':
			printf("%s\n", "Hi, boy!");
			break;
		case '3':
			printf("%s\n", "welcome, girl!");
			break;
		case '4':
			printf("%s\n", "Hey, welcome!");
			break;
		default:
			break;
	}

	return 0;
}