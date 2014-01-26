#include "MenuDrivenExample.h"

void menu_drive_test(MCContext* context)
{
	int selection = call(context, MCContext, showMenuAndGetSelectionChar, 3, "male", "female", "double");
	//printf("selection is: %c\n", putchar(selection));
	//printf("context->selectionChar is: %c\n", context->selectionChar);

	while(ff(context, showConfirmAndGetBOOL, "are you sure")!=1){
		call(context, MCContext, showMenuAndGetSelectionChar, 3, "male", "female", "double");
	}
	//printf("%d\n", bb);
	printf("%s\n", "your name please:");
	char name[100];
	fh(context,getUserInputString, 1145369978, name);
	
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

	printf("%s\n", "--------------------");
	printf("%s %s welcome to Mars\n", sex, name);
	printf("%s\n", "--------------------");
}