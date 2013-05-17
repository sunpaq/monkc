#include "MCString.h"

constructor(MCString, char* str)
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

	super_init(newthis, MCObject, nil);
	if (set_class(newthis, "MCString", "MCObject"))
	{
		binding(MCString, add, char* str);
		binding(MCString, print, xxx);
		binding(MCString, toCString, char const resultString[]);
		binding(MCString, equalTo, MCString* stringToComp) 							returns(BOOL);
		binding(MCString, getOneChar, xxx);
		binding(MCString, getCharsUntilEnter, char const resultString[]);
		binding(MCString, bye, xxx);
	}
	
	newthis->length = strlen(str);
	newthis->size = strlen(str) + 1;
	newthis->next = nil;
	return newthis;
}

MCString* MCString_newWithCString(char* cstr)
{
	return new(MCString, cstr);
}

MCString* MCString_newWithMCString(MCString* mcstr)
{
	return new(MCString, mcstr->buff);
}

MCString* MCString_newForHttp(char* cstr, BOOL isHttps)
{
	MCString* res;
	if (isHttps)
		res = new(MCString, "https://");
	else
		res = new(MCString, "http://");

	ff(res, MK(add), cstr);
	return res;
}

MCString* MCString_newWithCStringAnony(char* cstr)
{
	return new_anony(MCString, cstr);
}

MCString* MCString_newWithMCStringAnony(MCString* mcstr)
{
	return new_anony(MCString, mcstr->buff);
}

MCString* MCString_newForHttpAnony(char* cstr, BOOL isHttps)
{
	MCString* res;
	if (isHttps)
		res = new(MCString, "https://");
	else
		res = new(MCString, "http://");

	ff(res, MK(add), cstr);
	res->ref_count = 0;
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

method(MCString, add, char* str)
{
	MCString* iterator = this;
	while(iterator->next!=nil)
		iterator = iterator->next;
	(iterator->next) = new(MCString, str);
	this->length += strlen(str);
	this->size += strlen(str) + 1;
}

method(MCString, print, xxx)
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

method(MCString, toCString, char const resultString[])
{
	MCString* iterator = this;
	strcpy(resultString, this->buff);
	while(iterator->next!=nil)
	{
		iterator = iterator->next;
		strcat(resultString, iterator->buff);
	}
}

method(MCString, equalTo, MCString* stringToComp)
{
	int res;
	res = strcmp(this->buff, stringToComp->buff);
	if (res==0)
		return YES;
	else
		return NO;
}

method(MCString, bye, xxx)
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

method(MCString, getOneChar, xxx)
{
	get_one_char();
}

method(MCString, getCharsUntilEnter, char const resultString[])
{
	get_chars_until_enter(resultString);
}

