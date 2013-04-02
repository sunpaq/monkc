#include "MCContext.h"

constructor(MCContext, int argc, char** argv)
{
	link_class(MCContext, MCObject, nil)
	{
		binding(MCContext, bye, xxx);
		binding(MCContext, dumpParas, xxx);
		binding(MCContext, getPara, int index) 									returns(char*);
		binding(MCContext, isIndexedParaEqualTo, int index, char* para) 			returns(BOOL);
		binding(MCContext, isHavePara, char* para) returns(BOOL);
		binding(MCContext, showMenuAndGetSelectionChar, int count, ...) 			returns(char);
		binding(MCContext, showConfirmAndGetBOOL, const char* confirm) 			returns(BOOL);
		binding(MCContext, getUserInputString, char resultString[]);

		binding(MCContext, getEnvironmentVar, const char* key) returns(char*);
		binding(MCContext, setEnvironmentVar, const char* key, const char* value, BOOL isOverwrite) returns(RES);
		binding(MCContext, clearEnvironmentVar, const char* key) returns(RES);
	}

	this->argc=argc;
	this->argv=argv;
	this->selectionChar=0;

	return this;
}

static struct privateData
{
	/* data */
};

static char get_one_char()
{
	char cf = getchar();
	while(getchar()!='\n');//clear the buff
	return cf;
}

static void get_chars_until_enter(char resultString[])
{
	char tc;
	int i=0;
	while((tc=getchar())!='\n'){
		resultString[i]=tc;
		i++;
	}
	resultString[i]='\0';
}

method(MCContext, bye, xxx)
{
	runtime_log("%s\n", "MCContext goodbye");
}

method(MCContext, dumpParas, xxx)
{
	int i;
	for (i = 0; i < this->argc; ++i)
	{
		runtime_log("%s\n", this->argv[i]);
	}
}

method(MCContext, getPara, int index)
{
	return this->argv[index];
}

method(MCContext, isIndexedParaEqualTo, int index, char* para)
{
	char* para1 = this->argv[index];
	if (para1==nil)return NO;
	if (strcmp(para1, para)==0)return YES;
	else return NO;
}

method(MCContext, isHavePara, char* para)
{
	if(this==nil)return NO;
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

method(MCContext, showMenuAndGetSelectionChar, int count, ...)
{
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

method(MCContext, showConfirmAndGetBOOL, const char* confirm)
{
	printf("%s (y/n)?\n", confirm);
	char cf = get_one_char();
	if (cf=='y'){
		return YES;
	}
	return NO;
}

method(MCContext, getUserInputString, char resultString[])
{
	get_chars_until_enter(resultString);
}

/*
#include <stdlib.h>
char *getenv(const char *name);
int putenv(char *str); //need "key=value"
int setenv(const char *name, const char *value, int rewrite);
int unsetenv(const char *name);
*/

method(MCContext, getEnvironmentVar, const char* key) returns(char*)
{
	//char *getenv(const char *name);
	return getenv(key);
}

method(MCContext, setEnvironmentVar, const char* key, const char* value, BOOL isOverwrite) returns(RES)
{
	//int setenv(const char *name, const char *value, int rewrite);
	if (setenv(key, value, isOverwrite)==0)
		return SUCCESS;
	else
		return ERROR;
}

method(MCContext, clearEnvironmentVar, const char* key) returns(RES)
{
	//int unsetenv(const char *name);
	if (unsetenv(key)==0)
		return SUCCESS;
	else
		return ERROR;
}