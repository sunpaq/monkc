#include "Monkey.h"
#include "MCContext.h"
#include "SimpleServer.h"

void testOOP()
{
	Monkey* m = new(Monkey);
	ff(m, info, 0);
	ff(m, showage, 0);
	ff(m, showname, 0);

	printf("%s\n", "finish");
}

int main(int argc, char const *argv[])
{
	MCContext* ctx = MCContext_newWithArgs(argc, (char**)argv);
	char c = MCContext_showMenuAndGetSelectionChar(0, ctx, 4, 
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