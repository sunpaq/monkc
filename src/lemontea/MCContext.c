#include "MCContext.h"

initer(MCContext)
{
	obj->selectionChar=0;
	return obj;
}

loader(MCContext)
{
binding(MCContext, MCContext*, newWithArgs, int argc, char** argv);
binding(MCContext, void, bye, xxx);
binding(MCContext, void, dumpParas, xxx);
binding(MCContext, char*, getPara, int index);
binding(MCContext, int, isIndexedParaEqualTo, int index, char* para);
binding(MCContext, int, isHavePara, char* para);
binding(MCContext, char, showMenuAndGetSelectionChar, int count, ...);
binding(MCContext, int, showConfirmAndGetBOOL, const char* confirm);
binding(MCContext, void, getUserInputString, char resultString[]);
binding(MCContext, char*, getEnvironmentVar, const char* key);
binding(MCContext, int, setEnvironmentVar, const char* key, const char* value, int isOverwrite);
binding(MCContext, int, clearEnvironmentVar, const char* key);
return claz;
}

method(MCContext, 
MCContext*, newWithArgs, int argc, char** argv)
{
	MCContext* res = new(MCContext);
	res->argc = argc;
	res->argv = argv;
	return res;
}

struct privateData
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
		putchar(tc);
	}
	resultString[i]='\0';
	putchar(tc);
}

method(MCContext, void, bye, xxx)
{	
	runtime_log("%s\n", "MCContext goodbye");
}

method(MCContext, void, dumpParas, xxx)
{
	int i;
	for (i = 0; i < obj->argc; ++i)
	{
		runtime_log("%s\n", obj->argv[i]);
	}
}

method(MCContext, char*, getPara, int index)
{
	return obj->argv[index];
}

method(MCContext, int, isIndexedParaEqualTo, int index, char* para)
{
	char* para1 = obj->argv[index];
	if (para1==nil)return 0;
	if (strcmp(para1, para)==0)return 1;
	else return 0;
}

method(MCContext, int, isHavePara, char* para)
{
	if(obj==nil)return 0;
	int i, res;
	for (i = 0; i < obj->argc; ++i)
	{
		char* tmp = obj->argv[i];
		if(tmp!=nil&&para!=nil)res = strcmp(tmp, para);
		else return 0;

		if(res==0)return 1;
	}
	return 1;
}

method(MCContext, char, showMenuAndGetSelectionChar, int count, ...)
{
	va_list ap;
	va_start(ap, count);
	int i;
	for (i = 0; i < count; ++i)
	{
		char* arg = va_arg(ap, char*);
		printf("%d.%s\n", i+1, arg);
	}
	printf("%s\n", "your selection is?");
	va_end(ap);
	obj->selectionChar = get_one_char();
	return obj->selectionChar;
}

method(MCContext, int, showConfirmAndGetBOOL, const char* confirm)
{
	printf("%s (y/n)?\n", confirm);
	char cf = get_one_char();
	if (cf=='y'){
		return 1;
	}
	return 0;
}

method(MCContext, void, getUserInputString, char resultString[])
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

method(MCContext, char*, getEnvironmentVar, const char* key)
{
	//char *getenv(const char *name);
	return getenv(key);
}

method(MCContext, 
int, setEnvironmentVar, const char* key, const char* value, int isOverwrite)
{
	//int setenv(const char *name, const char *value, int rewrite);
	if (setenv(key, value, isOverwrite)==0)
		return 0;
	else
		return -1;
}

method(MCContext, 
int, clearEnvironmentVar, const char* key)
{
	//int unsetenv(const char *name);
	if (unsetenv(key)==0)
		return 0;
	else
		return -1;
}
