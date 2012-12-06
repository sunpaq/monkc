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

method_imp(MCContext, init, int argc, char** argv)
{
	This(MCContext);
	setting_start(this, "MCContext");
		this->argc=argc;
		this->argv=argv;

		bind(this, MT(dump), MA(MCContext, dump));
		bind(this, MT(getPara), MA(MCContext, getPara));
		bind(this, MT(paraEqual), MA(MCContext, paraEqual));
		bind(this, MT(havePara), MA(MCContext, havePara));

	setting_end(this, MA(MCContext, bye));
}