#include "MCContext.h"

method_imp(MCContext, bye, xxx)
{
	runtime_log("%s\n", "MCContext goodbye");
}

method_imp(MCContext, dump, xxx)
{
	This(MCContext);
	int i;
	for (i = 0; i < this->argc; ++i)
	{
		runtime_log("%s\n", this->argv[i]);
	}
}

method_imp(MCContext, getPara, int index)
{
	This(MCContext);
	return this->argv[index];
}

method_imp(MCContext, paraEqual, int index, char* para)
{
	This(MCContext);
	char* para1 = this->argv[index];
	if (para1==nil)return NO;
	if (strcmp(para1, para)==0)return YES;
	else return NO;
}

method_imp(MCContext, havePara, char* para)
{
	This(MCContext);if(this==nil)return NO;
	int i, res;
	for (i = 0; i < this->argc; ++i)
	{
		char* tmp = this->argv[i];
		if(tmp!=nil&&para!=nil)res = strcmp(tmp, para);
		else return NO;

		if(res==0)return YES;
	}
	return NO;
}

method_imp(MCContext, showMenuAndGetSelectionChar, int count, ...)
{
	This(MCContext);
	va_list ap;
	va_start(ap, count);
	int i;
	for (i = 0; i < count; ++i)
	{
		char* arg = va_arg(ap, const char*);
		printf("%d.%s\n", i+1, arg);
	}
	printf("%s\n", "your selection is?");
	va_end(ap);
	this->selectionChar = get_one_char();
	return this->selectionChar;
}

method_imp(MCContext, showConfirmAndGetBOOL, const char* confirm)
{
	This(MCContext);
	printf("%s (y/n)?\n", confirm);
	char cf = get_one_char();
	if (cf=='y'){
		return YES;
	}
	return NO;
}

method_imp(MCContext, getUserInputString, char resultString[])
{
	This(MCContext);
	get_chars_until_enter(resultString);
}

constructor_imp(MCContext, int argc, char** argv)
{
	Chis(MCContext, MCObject, nil);
	if(set_class(this, "MCContext", "MCObject")){

		bind(this, MK(dump), MV(MCContext, dump));
		bind(this, MK(getPara), MV(MCContext, getPara));
		bind(this, MK(paraEqual), MV(MCContext, paraEqual));
		bind(this, MK(havePara), MV(MCContext, havePara));
		bind(this, MK(showMenuAndGetSelectionChar), MV(MCContext, showMenuAndGetSelectionChar));
		bind(this, MK(showConfirmAndGetBOOL), MV(MCContext, showConfirmAndGetBOOL));
		bind(this, MK(getUserInputString), MV(MCContext, getUserInputString));

		bind(this, MK(bye), MV(MCContext, bye));
	}

	this->argc=argc;
	this->argv=argv;
	this->selectionChar=0;
}