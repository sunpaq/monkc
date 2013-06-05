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

char convbuff[100];
char* uint2str(unsigned i)
{
	sprintf(convbuff, "%u", i);
	return convbuff;
}

char cutbuff[100];
char* cut_method_name(char* in)
{
	int i=0;
	while(in[i++]!=',');//skip obj
	while(in[i++]!=' ');//skip space
	int j=0;
	for(;in[i+j]!=',' && in[i+j]!=' ';j++){
		cutbuff[j]=in[i+j];
	}
	return cutbuff;
}

#define MYECHO printf("%s:%u\n", cut_method_name(yytext), hash(cutbuff))
#define MYWRITE fprintf(outfile, "%s:%u\n", cut_method_name(yytext), hash(cutbuff))
%}

%%
ff(.*) MYECHO;
%%

int yywrap(void)
{
	return 1;
}
int main(int argc, char *argv[])
{
	yyin = fopen(argv[1], "r");
	//outfile = fopen(argv[2], "rw");
	yylex();
	fclose(yyin);
	//fclose(outfile);
	return 0;
}