#include "MCString.h"
#include "MCMath.h"

utility(MCString, MCBool, contains, const char* str, const char* instr)
{
    if (strstr(instr, str)) {
        return true;
    }
    return false;
}

utility(MCString, size_t, replace, const char* str, const char* withstr, const char* instr, char (*buff)[])
{
    size_t count = strlen(str);
    size_t wcount = strlen(withstr);
    
    int i=0, b=0, o=0;
    while (instr[i] != NUL) {
        while (instr[i+o] != NUL && instr[i+o] == str[0+o]) {
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
    (*buff)[b++] = NUL;
    
    return b;
}

utility(MCString, size_t, reverse, const char* str, char *buff)
{
    size_t count = strlen(str);
    char* c = (char*)&str[count-1];
    for (int i=0; i<count; i++) {
        buff[i] = *c;
        c--;
    }
    buff[count] = NUL;
    return count;
}

utility(MCString, const char*, percentEncode, const char* str, char *buff)
{
    if (!str || !buff) {
        return null;
    }
    char* iter = (char*)str; int b = 0;
    while (*iter != NUL) {
        //2
             if (*iter == ' ') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '0'; }
        else if (*iter == '!') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '1'; }
        else if (*iter == '"') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '2'; }
        else if (*iter == '#') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '3'; }
        else if (*iter == '$') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '4'; }
        else if (*iter == '%') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '5'; }
        else if (*iter == '&') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '6'; }
        else if (*iter =='\'') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '7'; }
        else if (*iter == '(') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '8'; }
        else if (*iter == ')') { buff[b++] = '%';buff[b++] = '2';buff[b++] = '9'; }
        else if (*iter == '*') { buff[b++] = '%';buff[b++] = '2';buff[b++] = 'A'; }
        else if (*iter == '+') { buff[b++] = '%';buff[b++] = '2';buff[b++] = 'B'; }
        else if (*iter == ',') { buff[b++] = '%';buff[b++] = '2';buff[b++] = 'C'; }
        else if (*iter == '-') { buff[b++] = '%';buff[b++] = '2';buff[b++] = 'D'; }
        else if (*iter == '.') { buff[b++] = '%';buff[b++] = '2';buff[b++] = 'E'; }
        else if (*iter == '/') { buff[b++] = '%';buff[b++] = '2';buff[b++] = 'F'; }
        //3
        else if (*iter == ':') { buff[b++] = '%';buff[b++] = '3';buff[b++] = 'A'; }
        else if (*iter == ';') { buff[b++] = '%';buff[b++] = '3';buff[b++] = 'B'; }
        else if (*iter == '<') { buff[b++] = '%';buff[b++] = '3';buff[b++] = 'C'; }
        else if (*iter == '=') { buff[b++] = '%';buff[b++] = '3';buff[b++] = 'D'; }
        else if (*iter == '>') { buff[b++] = '%';buff[b++] = '3';buff[b++] = 'E'; }
        else if (*iter == '?') { buff[b++] = '%';buff[b++] = '3';buff[b++] = 'F'; }
        //4
        else if (*iter == '@') { buff[b++] = '%';buff[b++] = '4';buff[b++] = '0'; }
        //5
        else if (*iter == '[') { buff[b++] = '%';buff[b++] = '5';buff[b++] = 'B'; }
        else if (*iter =='\\') { buff[b++] = '%';buff[b++] = '5';buff[b++] = 'C'; }
        else if (*iter == ']') { buff[b++] = '%';buff[b++] = '5';buff[b++] = 'D'; }
        else if (*iter == '^') { buff[b++] = '%';buff[b++] = '5';buff[b++] = 'E'; }
        else if (*iter == '_') { buff[b++] = '%';buff[b++] = '5';buff[b++] = 'F'; }
        //6
        else if (*iter == '`') { buff[b++] = '%';buff[b++] = '6';buff[b++] = '0'; }
        //7
        else if (*iter == '{') { buff[b++] = '%';buff[b++] = '7';buff[b++] = 'B'; }
        else if (*iter == '|') { buff[b++] = '%';buff[b++] = '7';buff[b++] = 'C'; }
        else if (*iter == '}') { buff[b++] = '%';buff[b++] = '7';buff[b++] = 'D'; }
        else if (*iter == '~') { buff[b++] = '%';buff[b++] = '7';buff[b++] = 'E'; }
        
        else {
            buff[b++] = *iter;
        }
        iter++;
    }

    return buff;
}

utility(MCString, const char*, percentDecode, const char* str, char *buff)
{
    if (!str || !buff) {
        return null;
    }
    char* iter = (char*)str; int b = 0;
    while (*iter != NUL) {
        //debug_log("MCString_percentDecode: %s\n", iter);
        if (*iter == '%') {
            iter++;
            if (*iter == '2') {
                iter++;
                     if (*iter == '0') { buff[b++] = ' '; iter++;}
                else if (*iter == '1') { buff[b++] = '!'; iter++;}
                else if (*iter == '2') { buff[b++] = '"'; iter++;}
                else if (*iter == '3') { buff[b++] = '#'; iter++;}
                else if (*iter == '4') { buff[b++] = '$'; iter++;}
                else if (*iter == '5') { buff[b++] = '%'; iter++;}
                else if (*iter == '6') { buff[b++] = '&'; iter++;}
                else if (*iter == '7') { buff[b++] ='\''; iter++;}
                else if (*iter == '8') { buff[b++] = '('; iter++;}
                else if (*iter == '9') { buff[b++] = ')'; iter++;}
                else if (*iter == 'A') { buff[b++] = '*'; iter++;}
                else if (*iter == 'B') { buff[b++] = '+'; iter++;}
                else if (*iter == 'C') { buff[b++] = ','; iter++;}
                else if (*iter == 'D') { buff[b++] = '-'; iter++;}
                else if (*iter == 'E') { buff[b++] = '.'; iter++;}
            }
            else if (*iter == '3') {
                iter++;
                     if (*iter == 'A') { buff[b++] = ':'; iter++;}
                else if (*iter == 'B') { buff[b++] = ';'; iter++;}
                else if (*iter == 'C') { buff[b++] = '<'; iter++;}
                else if (*iter == 'D') { buff[b++] = '='; iter++;}
                else if (*iter == 'E') { buff[b++] = '>'; iter++;}
                else if (*iter == 'F') { buff[b++] = '?'; iter++;}
            }
            else if (*iter == '4') {
                iter++;
                if (*iter == '0') { buff[b++] = '@'; iter++; }
            }
            else if (*iter == '5') {
                iter++;
                if (*iter == 'B') { buff[b++] = '['; iter++; }
                if (*iter == 'C') { buff[b++] ='\\'; iter++; }
                if (*iter == 'D') { buff[b++] = ']'; iter++; }
                if (*iter == 'E') { buff[b++] = '^'; iter++; }
                if (*iter == 'F') { buff[b++] = '_'; iter++; }
            }
            else if (*iter == '6') {
                iter++;
                if (*iter == '0') { buff[b++] = '`'; iter++; }
            }
            else if (*iter == '7') {
                iter++;
                if (*iter == 'B') { buff[b++] = '{'; iter++; }
                if (*iter == 'C') { buff[b++] = '|'; iter++; }
                if (*iter == 'D') { buff[b++] = '}'; iter++; }
                if (*iter == 'E') { buff[b++] = '~'; iter++; }
            }
        }
        else {
            buff[b++] = *iter;
            iter++;
        }
    }
    
    return buff;
}

utility(MCString, const char*, baseFromPath, const char* path, char (*buff)[])
{
    char reversebuff[PATH_MAX] = {0};
    size_t count = MCString_reverse(path, reversebuff);
    
    char* head = &reversebuff[count-1];
    char* tail = &reversebuff[0];
    while (!MCCond_PathDiv(tail) && *head != NUL) {
        tail++;
    }
    
    int i=0;
    while (head != tail) {
        (*buff)[i++] = *head;
        head--;
    }
    (*buff)[i] = NUL;
    
    return &(*buff)[0];
}

utility(MCString, const char*, filenameFromPath, const char* path, char (*buff)[])
{
    trimWhiteSpace(&path);

    char reversebuff[PATH_MAX] = {0};
    MCString_reverse(path, reversebuff);
    
    char* head = &reversebuff[0];
    char* tail = &reversebuff[0];
    while (!MCCond_PathDiv(head) && *head != NUL) {
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

utility(MCString, size_t, filenameTrimExtension, const char* name, char* buff)
{
    trimWhiteSpace(&name);
    char reversebuff[PATH_MAX] = {0};
    MCString_reverse(name, reversebuff);
    
    char* head = &reversebuff[0];
    char* tail = &reversebuff[0];
    
    while (1) {
        if (*tail != '.' && *tail != NUL) {
            tail++;
        }
        if (*head != NUL) {
            head++;
        } else {
            head--;//skip NUL
            break;
        }
    }
    //have extension
    if (*tail == '.') {
        tail++;
        int i=0;
        while (head != tail) {
            buff[i++] = *head;
            head--;
        }
        buff[i] = *head;//last char
        buff[i+1] = NUL;
        return i+1;
    }
    //no extension
    else {
        size_t szn = sizeof(name);
        strncpy(buff, name, szn);
        return szn;
    }
}

utility(MCString, size_t, extensionFromFilename, const char* name, char* basebuff, char* extbuff)
{
    trimWhiteSpace(&name);
    int i=0, j=0;
    while (name[i] != NUL && name[i] != NUL) {
        if (name[i] == '.') {
            j = i;
        }
        i++;
    }
    //no extension
    if (j==0) {
        strcpy(basebuff, name);
        extbuff[0] = NUL;
        return 0;
    }
    //have extension
    else {
        size_t b, e, x=0;
        for (b=0; b<j; b++) {
            basebuff[b] = name[b];
        }
        for (e=j+1; e<i; e++) {
            extbuff[x++] = name[e];
        }
        basebuff[b] = NUL;
        extbuff[x]  = NUL;
        return e;
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

utility(MCString, const char*, compressToCharCount, const char* source, char* buff)
{
    //assume buff is large enough
    if (source && buff) {
        //first char
        int cur = 0;
        buff[cur++] = *source;
        char last   = *source;
        
        char digits[LINE_MAX];
        size_t count = 1;
        
        for (int i=1; i<strlen(source); i++) {
            if(source[i] != last) {
                if (count > 1) {
                    sprintf(digits, "%ld", count);
                    for (int d=0; d<strlen(digits); d++)
                        buff[cur++] = digits[d];
                    count = 0;
                }
                buff[cur++] = source[i];
                last = source[i];
            } else {
                if (count > LINE_MAX)
                    count = LINE_MAX;
                else
                    count++;
            }
        }
        //end char
        buff[cur] = NUL;
    }
    return buff;
}

utility(MCString, const char*, extractFromCharCount, const char* source, char* buff)
{
    if (source && buff) {
        int cur = 0; int count=0; char last = NUL;
        char digits[LINE_MAX];

        for (int i=0; i<strlen(source); i++) {
            char c = source[i];
            if (c >= '0' && c <= '9') {
                digits[count++] = c;
                continue;
            } else {
                if (count > LINE_MAX)
                    count = LINE_MAX;
                digits[count] = NUL;
                if (count > 0) {
                    int number = atoi(digits);
                    for(int d=0; d<number; d++)
                        buff[cur++] = last;
                    count=0;
                }
                buff[cur++] = c;
                last = c;
            }
        }
        //end char
        buff[cur] = NUL;
    }
    return buff;
}

static void swap(char* a, char* b)
{
    if (a != b) {
        char temp = *a;
        *a = *b;
        *b = temp;
    }
}

static void permutationOf(char str[], int index)
{
    if (index == strlen(str)) {
        printf("%s\n", str);
        return;
    }
    for (int i=index; i<strlen(str); i++) {
        swap(&str[index], &str[i]);
        permutationOf(str, index+1);
        swap(&str[index], &str[i]);
    }
}

utility(MCString, void, printPermutationOf, char str[])
{
    char buff[LINE_MAX];
    strcpy(buff, str);
    buff[strlen(str)] = NUL;
    permutationOf(buff, 0);
}

#define MCStringBlock LINE_MAX

oninit(MCString)
{
    if (init(MCObject)) {
        //nothing to init
        obj->buff = malloc(MCStringBlock * sizeof(char));
        return obj;
    }else{
        return null;
    }
}

method(MCString, void, bye, voida)
{
    //debug_log("MCString bye");
    free(obj->buff);
}

method(MCString, MCString*, initWithCString, const char* str)
{
    size_t len = strlen(str);
    if (len >= MCStringBlock) {
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
    return MCString_initWithCString(new(MCString), cstr);
}

MCString* MCString_newWithMCString(MCString* mcstr)
{
    return MCString_initWithCString(new(MCString), mcstr->buff);
}

MCString* MCString_newForHttp(char* cstr, int isHttps)
{
	MCString* res;
	if (isHttps)
        res = MCString_newWithCString("https://");
	else
		res = MCString_newWithCString("http://");
    MCString_add(res, cstr);
	return res;
}

static char get_one_char()
{
    char cf = NUL;
    while(!isNewLine(&cf)) {
        cf = getchar();
    }//clear the buff
	return cf;
}

static void get_chars_until_enter(char resultString[])
{
	char tc = NUL;
	int i=0;
	while(!isNewLine(&tc)){
		resultString[i]=tc;
		i++;
	}
	resultString[i]=NUL;
}

method(MCString, void, add, char* str)
{
    if (MCStringBlock-obj->size < strlen(str)+1) {
        char* newbuff = malloc(sizeof(char) * (obj->size + MCStringBlock));
        strncpy(newbuff, obj->buff, obj->size-1);
        newbuff[obj->size-1]=NUL;
        free(obj->buff);
        obj->buff = newbuff;
        obj->size = obj->size + MCStringBlock;
    }
    strncat(obj->buff, str, strlen(str));
}

method(MCString, void, print, MCBool withNewline)
{
    if (withNewline)
        debug_log("%s\n", obj->buff);
    else
        debug_log("%s", obj->buff);
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
        return false;
    }else{
        if (strncmp(obj->buff, str, len) == 0) {
            return true;
        }else{
            return false;
        }
    }
}

method(MCString, double, toDoubleValue, char** endptr)
{
    return strtod(obj->buff, endptr);
}

method(MCString, MCString*, copyCompressedString, voida)
{
    MCString* string = new(MCString);
    MCString_compressToCharCount(obj->buff, string->buff);
    return string;
}

method(MCString, MCString*, copyExtractedString, voida)
{
    MCString* string = new(MCString);
    MCString_extractFromCharCount(obj->buff, string->buff);
    return string;
}

onload(MCString)
{
    if (load(MCObject)) {
        binding(MCString, MCString*, initWithCString, char* str);
        binding(MCString, void, add, char* str);
        binding(MCString, void, print, MCBool withNewline);
        binding(MCString, char*, toCString, char const buff[]);
        binding(MCString, int, equalTo, MCString* stringToComp);
        binding(MCString, char, getOneChar);
        binding(MCString, void, getCharsUntilEnter, char const resultString[]);
        binding(MCString, void, bye);
        binding(MCString, MCBool, startWith, const char* str);
        binding(MCString, double, toDoubleValue, char** endptr);
        binding(MCString, MCString*, copyCompressedString, voida);
        binding(MCString, MCString*, copyExtractedString, voida);
        return cla;
    }else{
        return null;
    }
}
