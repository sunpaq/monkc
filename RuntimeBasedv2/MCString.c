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

method(MCString, print, xxx)
{
	printf("%s\n", this->str);
}

method(MCString, getOneChar, xxx)
{
	get_one_char();
}

method(MCString, getCharsUntilEnter, char const resultString[])
{
	get_chars_until_enter(resultString);
}

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
}