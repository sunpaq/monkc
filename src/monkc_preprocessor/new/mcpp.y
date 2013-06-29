%{
#include <stdio.h>
#include <ctype.h>
void class_define_action(const char* class);
void object_new_action(const char* class);
void ff_called_action(const char* methodname);
void found_arg_action(const char* type);
void found_method_name_action(const char* s);

%}

%union
{
	int number;
	char* string;
}

%token METHOD
%token BINDING
%token FF
%token NEW
%token CLASS
%token IMPL
%token EXTS

%token <string> ID
%token NUMBER
%token XXX
%token PL
%token PR
%token COMMA
%token STAR

%%
expr				:	macro content end;
macro				:	METHOD 	{printf("method\n");}
					| 	BINDING {printf("binding\n");}
					| 	FF 		{printf("ff\n");}
					| 	NEW 	{printf("new\n");}
					| 	CLASS 	{printf("class\n");}
					| 	IMPL 	{printf("implements\n");}
					| 	EXTS	{printf("extends\n");}
					;
content				:	single | list;
single				:	classname;
classname			:	ID {printf("classname is: %s\n", $1);};
list				:	class_ret_met_arg | class_method_para;
class_ret_met_arg	:	ID COMMA ID COMMA ID COMMA argslist {printf("methodname is:%s ret-type:%s\n", $5, $3);};
argslist			:	argslist COMMA arg | arg | XXX {printf("type is xxx\n");};
arg 				:	type ID {printf("arg is %s\n", $2);};
type				:	ID STAR {printf("type is %s*\n", $1);} | ID {printf("type is %s\n", $1);};
class_method_para	:	ID COMMA ID COMMA paralist {printf("methodname is: %s\n", $3);};
paralist			:	paralist COMMA para | para;
para 				:	ID {printf("para is %s\n", $1);}| NUMBER;
end 				:	PR;

%%
unsigned hash(const char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval;
}

char* uint2str(unsigned i)
{
	static char convbuff[100];
	sprintf(convbuff, "%u", i);
	return convbuff;
}

/*Actions*/

void class_define_action(const char* class)
{
	printf("class %s defined\n", class);
}

void object_new_action(const char* class)
{
	printf("object of %s created\n", class);
}

void ff_called_action(const char* methodname)
{
	printf("method %s called\n", methodname);
}

void found_method_name_action(const char* s)
{
	printf("a method name:%s - hash:%s\n", s, uint2str(hash(s)));
}

void found_arg_action(const char* type)
{
	if(strncmp(type, "char", 4)==0){
		printf("char should change to int\n");
	}
	else if(strncmp(type, "short", 5)==0){
		printf("short should change to int\n");
	}
	else if(strncmp(type, "short int", 9)==0){
		printf("short int should change to int\n");
	}
	else if(strncmp(type, "float", 5)==0){
		printf("float should change to double\n");
	}
	else
		printf("type is %s\n", type);
}

yyerror(char *s)
{
	printf("%s\n", s);
}

int main()
{
  yyparse();
}

