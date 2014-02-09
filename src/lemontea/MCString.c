#include "MCString.h"

initer(MCString)
{
	//nothing to init
	return obj;
}

method(MCString, MCString*, initWithCString, char* str)
{
	/*
    if(str==nil)return nil;
	size_t len = strlen(str);
	MCString* newthis = nil;
	//realloc will return a new mem if can now expand the old one!
	if(len > 0){
		newthis = (MCString*)realloc(obj, sizeof(MCString) + len + 1);
	}else{
		newthis = (MCString*)realloc(obj, sizeof(MCString) + 1);
		error_log("MCString input string length <= 0\n");
	}

	if(newthis!=nil){
		strncpy(newthis->buff, str, strlen(str) + 1);
	}else{
		error_log("mem realloc failed, nothing is in buff\n");
		exit(-1);
	}
    */
	
	obj->length = strlen(str);
	obj->size = strlen(str) + 1;
	//obj->next = nil;
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

	ff(res, MK(add), cstr);
	return res;
}

// MCString* MCString_newWithCStringAnony(char* cstr)
// {
// 	return new_anony(MCString, cstr);
// }

// MCString* MCString_newWithMCStringAnony(MCString* mcstr)
// {
// 	return new_anony(MCString, mcstr->buff);
// }

// MCString* MCString_newForHttpAnony(char* cstr, BOOL isHttps)
// {
// 	MCString* res;
// 	if (isHttps)
// 		res = new(MCString, "https://");
// 	else
// 		res = new(MCString, "http://");

// 	ff(res, MK(add), cstr);
// 	res->ref_count = 0;
// 	return res;
// }

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
	/*
    MCString* iterator = obj;
	while(iterator->next!=nil)
		iterator = (MCString*)iterator->next;
	(iterator->next) = ff(new(MCString), initWithCString, str);
	obj->length += strlen(str);
	obj->size += strlen(str) + 1;
    */
    
    strcat(obj->buff, str);
}

method(MCString, void, print, xxx)
{
	printf("%s", obj->buff);
    /*
	MCString* iterator = obj;
	while(iterator->next!=nil)
	{
		iterator = (MCString*)iterator->next;
		printf("%s", iterator->buff);
	}
	printf("\n");
    */
}

method(MCString, const char*, toCString, char const buff[])
{
	//MCString* iterator = obj;
	strcpy(cast(char*, buff), obj->buff);
    /*
	while(iterator->next!=nil)
	{
		iterator = cast(MCString*, iterator->next);
		strcat(cast(char*, buff), iterator->buff);
	}
    */ 
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

method(MCString, void, bye, xxx)
{
	/*
    //only release the added sub strings.
	debug_log("MCString - bye\n");
	MCString *iterator, *save;
	for(iterator=obj->next; (save=iterator)!=nil; free(save)){
		iterator = iterator->next;
		debug_log("MCString - free a sub string\n");
	}
    */
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