%{
#include "mcpp_parser.h"
%}
digit 				[0-9]
number				("-"|"+")?{digit}+
letter				[a-zA-Z]
identifier			(_|{letter})(_|{letter}|{number})*
identifier_w		(_|{letter}|" ")(_|{letter}|{number}|" ")*
space				(" "+)
comment 			(\/\/|\/\*.*\*\/)
default_rule		.
%%
"("             	{return PL;}
")"            		{return PR;}
","             	{return COMMA;}
"*"					{return STAR;}

"xxx"         		{return XXX;}
"method("			{return METHOD;}
"binding("          {return BINDING;}
"ff("               {return FF;}
"new("              {return NEW;}
"class("            {return CLASS;}
"implements("		{return IMPL;}
"extends(" 			{return EXTS;}

{identifier}		{yylval.string=strdup(yytext);return ID;}
{number}		    {return NUMBER;}
%%

int yywrap(void)
{
	return 1;
}

