#include "MCString.h"

static int block_size = 1024;
initer(MCString)
{
	//nothing to init
    obj->buff = malloc(block_size*sizeof(char));
	return obj;
}

method(MCString, void, bye, xxx)
{
    debug_log("MCString bye");    
    free(obj->buff);
}

method(MCString, MCString*, initWithCString, char* str)
{
	obj->length = strlen(str);
	obj->size = strlen(str) + 1;
    strcpy(obj->buff, str);
	return obj;
}

MCString* MCString_newWithCString(char* cstr)
{
	return ff(new(MCString), initWithCString, cstr);
}

MCString* MCString_newWithMCString(MCString* mcstr)
{
	return ff(new(MCString), initWithCString, mcstr->buff);
}

MCString* MCString_newForHttp(char* cstr, int isHttps)
{
	MCString* res;
	if (isHttps)
		res = ff(new(MCString), initWithCString, "https://");
	else
		res = ff(new(MCString), initWithCString, "http://");

	ff(res, add, cstr);
	return res;
}

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

method(MCString, void, add, char* str)
{
    if (block_size-obj->size < strlen(str)+1) {
        char* newbuff = malloc(sizeof(char) * (obj->size + block_size));
        strncpy(newbuff, obj->buff, obj->size-1);
        newbuff[obj->size-1]='\0';
        free(obj->buff);
        obj->buff = newbuff;
        obj->size = obj->size + block_size;
    }
    strncat(obj->buff, str, strlen(str));
}

method(MCString, void, print, xxx)
{
	printf("%s", obj->buff);
}

method(MCString, const char*, toCString, char const buff[])
{
	strcpy(cast(char*, buff), obj->buff);
	return buff;
}

method(MCString, int, equalTo, MCString* stringToComp)
{
	int res;
	res = strcmp(obj->buff, stringToComp->buff);
	if (res==0)
		return 1;
	else
		return 0;
}

method(MCString, char, getOneChar, xxx)
{
	return get_one_char();
}

method(MCString, void, getCharsUntilEnter, char resultString[])
{
	get_chars_until_enter(resultString);
}

loader(MCString)
{
binding(MCString, MCString*, initWithCString, char* str);
binding(MCString, void, add, char* str);
binding(MCString, void, print, xxx);
binding(MCString, char*, toCString, char const buff[]);
binding(MCString, int, equalTo, MCString* stringToComp);
binding(MCString, char, getOneChar, xxx);
binding(MCString, void, getCharsUntilEnter, char const resultString[]);
binding(MCString, void, bye, xxx);
return claz;
}
