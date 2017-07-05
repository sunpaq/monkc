#include "MCString.h"

utility(MCString, size_t, replace, const char* str, const char* withstr, const char* instr, char (*buff)[])
{
    size_t count = strlen(str);
    size_t wcount = strlen(withstr);
    
    int i=0, b=0, o=0;
    while (instr[i] != '\0') {
        while (instr[i+o] != '\0' && instr[i+o] == str[0+o]) {
            o++;
        }
        if (o == (int)count) {
            for (int k=0; k<wcount; k++) {
                (*buff)[b++] = withstr[k];
            }
            i += o;
        }
        o = 0;
        (*buff)[b++] = instr[i++];
    }
    (*buff)[b++] = '\0';
    
    return b;
}

utility(MCString, size_t, reverse, const char* str, char (*buff)[])
{
    size_t count = strlen(str);
    char* c = (char*)&str[count-1];
    for (int i=0; i<count; i++) {
        (*buff)[i] = *c;
        c--;
    }
    (*buff)[count] = '\0';
    
    return count;
}

utility(MCString, const char*, baseFromPath, const char* path, char (*buff)[])
{
    char reversebuff[PATH_MAX];
    size_t count = MCString_reverse(path, &reversebuff);
    
    char* head = &reversebuff[count-1];
    char* tail = &reversebuff[0];
    while (*tail != '/') {
        tail++;
    }
    
    int i=0;
    while (head != tail) {
        (*buff)[i++] = *head;
        head--;
    }
    (*buff)[i] = '\0';
    
    return &(*buff)[0];
}

utility(MCString, const char*, filenameFromPath, const char* path, char (*buff)[])
{
    char reversebuff[PATH_MAX];
    MCString_reverse(path, &reversebuff);
    
    char* head = &reversebuff[0];
    char* tail = &reversebuff[0];
    while (*head != '/') {
        head++;
    }
    head--;
    
    int i=0;
    while (head != tail) {
        (*buff)[i++] = *head;
        head--;
    }
    (*buff)[i] = *tail;
    
    return &(*buff)[0];
}

utility(MCString, const char*, filenameTrimExtension, const char* name, char (*buff)[])
{
    int i=0;
    while (*name != '.' && *name != '\0') {
        (*buff)[i++] = *name;
        name++;
    }
    (*buff)[i] = '\0';

    if (*name == '\0') {
        return name;
    }else{
        return &(*buff)[0];
    }
}

utility(MCString, const char*, extensionFromFilename, const char* name, char (*buff)[])
{
    while (*name != '.' && *name != '\0') name++;
    if (*name == '\0') {
        return mull;
    }else{
        name++;//skip dot
        int i=0;
        while (*name != '\0') {
            (*buff)[i++] = *name;
            name++;
        }
        (*buff)[i] = '\0';
        
        return &(*buff)[0];
    }
}

utility(MCString, const char*, concate, const char** strings, size_t count, char (*buff)[])
{
    strcpy(*buff, strings[0]);
    for (int i=1; i<count; i++) {
        strcat(*buff, strings[i]);
    }
    return *buff;
}

utility(MCString, const char*, concateWith, const char* sp, const char* path1, const char* path2, char (*buff)[])
{
    return MCString_concate((const char* []){
        path1, sp, path2
    }, 3, buff);
}

utility(MCString, const char*, concatePath, const char* path1, const char* path2, char (*buff)[])
{
    return MCString_concateWith("/", path1, path2, buff);
}

static size_t block_size = 1024;
oninit(MCString)
{
    if (init(MCObject)) {
        //nothing to init
        obj->buff = malloc(block_size*sizeof(char));
        return obj;
    }else{
        return mull;
    }
}

method(MCString, void, bye, voida)
{
    debug_log("MCString bye");    
    free(obj->buff);
}

method(MCString, MCString*, initWithCString, const char* str)
{
    size_t len = strlen(str);
    if (len >= block_size) {
        free(obj->buff);
        obj->buff = malloc(len*sizeof(char));
    }
    
    obj->length = strlen(str);
	obj->size = strlen(str) + 1;
    strcpy(obj->buff, str);
	return obj;
}

MCString* MCString_newWithCString(const char* cstr)
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

	ff(res, add, cstr);
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

method(MCString, void, add, char* str)
{
    if (block_size-obj->size < strlen(str)+1) {
        char* newbuff = malloc(sizeof(char) * (obj->size + block_size));
        strncpy(newbuff, obj->buff, obj->size-1);
        newbuff[obj->size-1]='\0';
        free(obj->buff);
        obj->buff = newbuff;
        obj->size = obj->size + block_size;
    }
    strncat(obj->buff, str, strlen(str));
}

method(MCString, void, print, voida)
{
	printf("%s", obj->buff);
}

method(MCString, const char*, toCString, char const buff[])
{
	strcpy(cast(char*, buff), obj->buff);
	return buff;
}

method(MCString, int, equalTo, MCString* stringToComp)
{
	int res;
	res = strcmp(obj->buff, stringToComp->buff);
	if (res==0)
		return 1;
	else
		return 0;
}

method(MCString, char, getOneChar, voida)
{
	return get_one_char();
}

method(MCString, void, getCharsUntilEnter, char resultString[])
{
	get_chars_until_enter(resultString);
}

method(MCString, MCBool, startWith, const char* str)
{
    size_t len = strlen(str);
    if (len > obj->length) {
        return MCFalse;
    }else{
        if (strncmp(obj->buff, str, len) == 0) {
            return MCTrue;
        }else{
            return MCFalse;
        }
    }
}

method(MCString, double, getFloat, char** endptr)
{
    return strtod(obj->buff, endptr);
}

onload(MCString)
{
    if (load(MCObject)) {
        binding(MCString, MCString*, initWithCString, char* str);
        binding(MCString, void, add, char* str);
        binding(MCString, void, print);
        binding(MCString, char*, toCString, char const buff[]);
        binding(MCString, int, equalTo, MCString* stringToComp);
        binding(MCString, char, getOneChar);
        binding(MCString, void, getCharsUntilEnter, char const resultString[]);
        binding(MCString, void, bye);
        binding(MCString, MCBool, startWith, const char* str);
        binding(MCString, double, getFloat, char** endptr);
        return cla;
    }else{
        return mull;
    }
}
