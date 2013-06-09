%{
FILE* outfile;
unsigned hash(const char *s)
{
	//runtime_log("hash(%s) --- ", s);
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	//runtime_log("hashval is: %d\n", hashval);
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
	//int i = 0;
	while(*in!=',')//copy head
		buff[i++]=*(in++);
	for(buff[i++]=','; *in!=' '; in++)//skip space
		buff[i++]=' ';
	in++;//next non-space
	buff[1]='h';//ff->fh
	unsigned hashval;
	for(hashval=0; (*in!=',' && *in!=' '); in++){
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
	//int i = 0;
	while(*in!=',')//copy head
		buff[i++]=*(in++);
	for(buff[i++]=','; *in!=' '; in++)//skip space
		buff[i++]=' ';
	in++;//next non-space
	buff[0]='h';//binding->hinding
	unsigned hashval;
	for(hashval=0; (*in!=',' && *in!=' '); in++){
		hashval = (*in) + 31*hashval;
		buff[i++]=*in;
	}
	buff[i++]=',';
	buff[i++]=' ';
	char* hashstr = uint2str(hashval);
	strncpy(&buff[i], hashstr, strlen(hashstr));//copy middle
	i=i+strlen(hashstr);
	//tail
	strcpy(&buff[i], in);//copy tail
	return buff;
}

#define MYP printf("%s - %s", yytext, hash_method_name(yytext))
#define MYECHO do{char* writeback = hash_ff_method_name(yytext, 0);\
				fprintf(yyout, "%s", writeback);}while(0);
#define MYECHO2 do{char* writeback = hash_binding_method_name(yytext, 0);\
				fprintf(yyout, "%s", writeback);}while(0);

%}

%%
binding(.*) MYECHO2;
ff(.*) MYECHO;
. ECHO;
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
	//char* outfile = argv[2];
	//outfile = strcat(outfile, argv[1]);
	yyout=fopen(argv[2], "wt+");
	yylex();
	fclose(yyin);
	fclose(yyout);
	return 0;
}