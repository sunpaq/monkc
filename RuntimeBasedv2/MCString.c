#include "MCString.h"

char get_one_char()
{
	char cf = getchar();
	while(getchar()!='\n');//clear the buff
	return cf;
}

void get_chars_until_enter(char resultString[])
{
	char tc;
	int i=0;
	while((tc=getchar())!='\n'){
		resultString[i]=tc;
		i++;
	}
	resultString[i]='\0';
}

<<<<<<< HEAD
method(MCString, print, xxx)
{
	printf("%s\n", this->str);
=======
method(MCString, add, CString str)
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

method(MCString, toCString, char resultString[])
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
	//only release the added sub strings.
	//debug_log("MCString - bye\n");
	MCString* iterator = this;
	while(iterator->next!=nil){
		iterator = iterator->next;
		//debug_log("MCString - free a sub string\n");
		free(iterator);//avoid recursive release call!!
	}
>>>>>>> version 0108
}

method(MCString, getOneChar, xxx)
{
	get_one_char();
}

method(MCString, getCharsUntilEnter, char const resultString[])
{
	get_chars_until_enter(resultString);
}

<<<<<<< HEAD
constructor(MCString, String str)
{
	super_init(this, MCObject, nil);

	if (set_class(this, "MCString", "MCObject"))
	{
		bind(this, "print", MCString_print);
		bind(this, "getOneChar", MCString_getOneChar);
		bind(this, "getCharsUntilEnter", MCString_getCharsUntilEnter);
	}

	this->str=str;

	return this;
=======
constructor(MCString, CString str)
{
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
		bind(newthis, "add", MCString_add);
		bind(newthis, "print", MCString_print);
		bind(newthis, "toCString", MCString_toCString);
		bind(newthis, "equalTo", MCString_equalTo);
		bind(newthis, "getOneChar", MCString_getOneChar);
		bind(newthis, "getCharsUntilEnter", MCString_getCharsUntilEnter);
		bind(newthis, "bye", MCString_bye);
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
>>>>>>> version 0108
}