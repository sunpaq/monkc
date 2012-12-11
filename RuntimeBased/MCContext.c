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

method_imp(MCContext, init, int argc, char** argv)
{
	This(MCContext);
	if(set_class(this, "MCContext", "root")){

		bind(this, MT(dump), MA(MCContext, dump));
		bind(this, MT(getPara), MA(MCContext, getPara));
		bind(this, MT(paraEqual), MA(MCContext, paraEqual));
		bind(this, MT(havePara), MA(MCContext, havePara));
		bind(this, MT(showMenuAndGetSelectionChar), MA(MCContext, showMenuAndGetSelectionChar));
		bind(this, MT(showConfirmAndGetBOOL), MA(MCContext, showConfirmAndGetBOOL));
		bind(this, MT(getUserInputString), MA(MCContext, getUserInputString));

		bind(this, MA(MCContext, bye), MA(MCContext, bye));
	}

	this->argc=argc;
	this->argv=argv;
	this->selectionChar=0;
}