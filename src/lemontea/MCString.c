#include "MCString.h"

initer(MCString)
{
	//nothing to init
}

method(MCString, MCString*, initWithCString, char* str)
{
	if(str==nil)return nil;
	size_t len = strlen(str);
	MCString* newthis = nil;
	//realloc will return a new mem if can now expand the old one!
	if(len > 0){
		newthis = (MCString*)mc_realloc(this, sizeof(MCString) + len + 1);
	}else{
		newthis = (MCString*)mc_realloc(this, sizeof(MCString) + 1);
		error_log("MCString input string length <= 0\n");
	}

	if(newthis!=nil){
		strncpy(newthis->buff, str, strlen(str) + 1);
	}else{
		error_log("mem realloc failed, nothing is in buff\n");
		exit(-1);
	}
	
	newthis->length = strlen(str);
	newthis->size = strlen(str) + 1;
	newthis->next = nil;
	return newthis;
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
	MCString* iterator = this;
	while(iterator->next!=nil)
		iterator = iterator->next;
	(iterator->next) = ff(new(MCString), initWithCString, str);
	this->length += strlen(str);
	this->size += strlen(str) + 1;
}

method(MCString, void, print, xxx)
{
	printf("%s", this->buff);
	MCString* iterator = this;
	while(iterator->next!=nil)
	{
		iterator = iterator->next;
		printf("%s", iterator->buff);
	}
	printf("\n");
}

method(MCString, char*, toCString, char const buff[])
{
	MCString* iterator = this;
	strcpy(buff, this->buff);
	while(iterator->next!=nil)
	{
		iterator = iterator->next;
		strcat(buff, iterator->buff);
	}
	return buff;
}

method(MCString, int, equalTo, MCString* stringToComp)
{
	int res;
	res = strcmp(this->buff, stringToComp->buff);
	if (res==0)
		return 1;
	else
		return 0;
}

method(MCString, void, bye, xxx)
{
	call(this, MCObject, bye, nil);
	//only release the added sub strings.
	debug_log("MCString - bye\n");
	MCString *iterator, *save;
	for(iterator=this->next; (save=iterator)!=nil; mc_free(save)){
		iterator = iterator->next;
		debug_log("MCString - free a sub string\n");
	}
}

method(MCString, char, getOneChar, xxx)
{
	return get_one_char();
}

method(MCString, void, getCharsUntilEnter, char const resultString[])
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
}