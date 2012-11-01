#define CLASS String
#include "String.h"

MCImplement(String)
#include "RC.default"
method_imp(void, show, xxx)body(
	pull(char*,charseq);
	printf("%s\n", charseq);
);

//form <string.h>
//char* strcat (char *s1, const char *s2);
method_imp(void, append, String *str)body(
	pull(char*,charseq);
	charseq = strcat(charseq, str->charseq);
	push(charseq);
);

//from <string.h>
//int strcmp (const char *s1, const char *s2);
//if equal return 0
method_imp(bool, equal, String *str)body(
	pull(char*,charseq);
	int res = strcmp(charseq, str->charseq);
	if(res == 0)return true;
	return false;
);

method_imp(void,bye,xxx)body(
	//C style char sequence does not
	//alloc in heap so can not free them
	//they will be take care automatically
	printf("string bye\n");
 	free(this);
);

MCImplementEnd(String, char* charseq_in)Body(
	//RC support
	Set(ref_count,1);
	Bind(retain);
	Bind(release);
	Bind(bye);
	//Assemble
	Set(charseq,charseq_in);
	Bind(show);
	Bind(append);
	Bind(equal);
);

#undef CLASS