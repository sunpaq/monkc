%{
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

char* hash_ff_method_name(char* in, int i)
{
	static char buff[100];
	int step = i;
	while(*in!=',' && *in!='\0')//copy head
		buff[i++]=*(in++);
	buff[i++]=',';
	while(*(++in)==' ' && *in!='\0');//skip space
	buff[step+1]='h';//ff->fh
	unsigned hashval;
	for(hashval=0; (*in!=',' && *in!=' ' && *in!='\0'); in++){
		hashval = (*in) + 31*hashval;
		buff[i++]=*in;
	}
	buff[i++]=',';
	buff[i++]=' ';
	char* hashstr = uint2str(hashval);
	strncpy(&buff[i], hashstr, strlen(hashstr));//copy middle
	i=i+strlen(hashstr);
	char* substr;
	if((substr=strstr(in, "ff("))==NULL)
		strcpy(&buff[i], in);//copy tail
	else{
		buff[i++]=',';
		buff[i++]=' ';
		hash_ff_method_name(substr, i);//+1 skip the '\0' in convbuff
	}
	return buff;
}

char* hash_binding_method_name(char* in, int i)
{
	static char buff[100];
	int step = i;
	while(*in!=',' && *in!='\0')//copy class
		buff[i++]=*(in++);
	buff[i++]=*(in++);//add ','
	while(*in!=',' && *in!='\0')//copy returnType
		buff[i++]=*(in++);
	buff[i++]=*(in++);//add ','
	while(*(++in)==' ' && *in!='\0');//skip space
	buff[i++]=' ';//add one space
	buff[step+0]='h';//ff->fh
	unsigned hashval;
	for(hashval=0; (*in!=',' && *in!=' ' && *in!='\0'); in++){
		hashval = (*in) + 31*hashval;
		buff[i++]=*in;
	}
	buff[i++]=',';
	buff[i++]=' ';
	char* hashstr = uint2str(hashval);
	strncpy(&buff[i], hashstr, strlen(hashstr));//copy middle
	i=i+strlen(hashstr);
	char* substr;
	strcpy(&buff[i], in);//copy tail
	return buff;
}

char* hash_new_class_name(char* in, int i)
{
	static char buff[100];
	int step = i;
	while(*in!='(' && *in!='\0')//copy head
		buff[i++]=*(in++);
	buff[i++]='(';
	while(*(++in)==' ' && *in!='\0');//skip space
	buff[step+0]='h';//new->hew
	unsigned hashval;
	for(hashval=0; (*in!=')' && *in!=' ' && *in!='\0'); in++){
		hashval = (*in) + 31*hashval;
		buff[i++]=*in;
	}
	buff[i++]=',';
	buff[i++]=' ';
	char* hashstr = uint2str(hashval);
	strncpy(&buff[i], hashstr, strlen(hashstr));//copy middle
	i=i+strlen(hashstr);
	char* substr;
	strcpy(&buff[i], in);//copy tail
	return buff;
}

char* hash_new_category_class_name(char* in, int i)
{
	static char buff[100];
	int step = i;
	while(*in!='(' && *in!='\0')//copy head
		buff[i++]=*(in++);
	buff[i++]='(';
	while(*(++in)==' ' && *in!='\0');//skip space
	buff[step+0]='h';//new->hew
	unsigned hashval;
	for(hashval=0; (*in!=',' && *in!=' ' && *in!='\0'); in++){
		hashval = (*in) + 31*hashval;
		buff[i++]=*in;
	}
	buff[i++]=',';
	buff[i++]=' ';
	char* hashstr = uint2str(hashval);
	strncpy(&buff[i], hashstr, strlen(hashstr));//copy middle
	i=i+strlen(hashstr);
	char* substr;
	strcpy(&buff[i], in);//copy tail
	return buff;
}

#define MYP 	printf("%s - %s", yytext, hash_method_name(yytext))
#define MYECHO 	do{char* writeback = hash_ff_method_name(yytext, 0);\
				fprintf(yyout, "%s", writeback);}while(0);
#define MYECHO2 do{char* writeback = hash_binding_method_name(yytext, 0);\
				fprintf(yyout, "%s", writeback);}while(0);
#define MYECHO3 do{char* writeback = hash_new_class_name(yytext, 0);\
				fprintf(yyout, "%s", writeback);}while(0);
#define MYECHO4 do{char* writeback = hash_new_category_class_name(yytext, 0);\
				fprintf(yyout, "%s", writeback);}while(0);

%}

digit 			[0-9]
number			("-"|"+")?{digit}+
letter			[a-zA-Z]
identifier		(_|{letter})(_|{letter}|{number})*
identifier_w	(_|{letter}|" ")(_|{letter}|{number}|" ")*
comment 		(\/\/|\/\*.*\*\/)
default_rule	.

new_category    new_category\({identifier_w}\)   
new                      new\({identifier_w}\)
info                    info\({identifier_w}\)
clear                  clear\({identifier_w}\)

binding 		binding\({identifier_w},.*,{identifier_w}+\)
override	   	override\({identifier_w},.*,{identifier_w}+\)
response_to					response_to\({identifier_w},{identifier_w}\)
_self_response_to 	  _self_response_to\({identifier_w},{identifier_w}\)
ff    								 ff\({identifier_w},{identifier_w},{identifier_w}+\)

%%
{new_category}												MYECHO4;

{new}														MYECHO3;
{info} 														MYECHO3;
{clear}					 									MYECHO3;

{binding} 													MYECHO2;
{override} 													MYECHO2;
{response_to}												MYECHO2;
{_self_response_to}											MYECHO2;

{ff}														MYECHO;
{comment}													ECHO;
{default_rule}												ECHO;
%%

int yywrap(void)
{
	return 1;
}

int main(int argc, char *argv[])
{
	if(argc!=3){
		printf("mcpp <inputfile> <outputfile>\n");
		return -1;
	}
	yyin=fopen(argv[1], "rt");
	yyout=fopen(argv[2], "wt+");
	yylex();
	fclose(yyin);
	fclose(yyout);
	return 0;
}