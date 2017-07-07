//
//  MCFileParser.h
//  monkcGame
//
//  Created by Sun YuLi on 16/3/26.
//  Copyright © 2016年 oreisoft. All rights reserved.
//

#ifndef MCFileParser_h
#define MCFileParser_h

//parser
typedef enum {
    MCTokenIdentifier,
    MCTokenFilename,
    MCTokenFloat,
    MCTokenInteger,
    MCTokenDate,
    MCTokenComment,
    MCTokenUnknown
} MCTokenType;

typedef union {
    long   Integer;
    long   Date[3];
    double Double;
    char   Word[128];
} MCTokenValue;

typedef struct {
    MCTokenType type;
    MCTokenValue value;
} MCToken;

static const char  MCTab = '\t';
static const char  MCWhiteSpace = ' ';
static const char  MCNewLineN = '\n';
static const char  MCNewLineR = '\r';

#define MCCond_Digit(w)     (*w >= '0' && *w <= '9')
#define MCCond_Alphabet(w)  (*w >= 'a' && *w <= 'z') || (*w >= 'A' && *w <= 'Z')
#define MCCond_PathDiv(w)   (*w == '/' || *w =='\\')

MCInline size_t MCLexerFill(char* const dest, const char* src)
{
    size_t len = strlen(src);
    strncpy(dest, src, len);
    dest[len] = NUL;
    return len;
}

//return remain string
MCInline const char* trimWhiteSpace(const char** target_p)
{
    const char* iter = *target_p;
    while (*iter == MCWhiteSpace || *iter == MCTab)
        iter++;
    *target_p = iter;//update remain
    return iter;
}

MCInline const char* trimWhiteSpaceNewline(const char** target_p)
{
    const char* iter = *target_p;
    while (*iter == MCWhiteSpace || *iter == MCTab || *iter == MCNewLineN || *iter == MCNewLineR)
        iter++;
    *target_p = iter;//update remain
    return iter;
}

//Old Mac9 end of line sequence: \r
//Unix OSX end of line sequence: \n
//Windows  end of line sequence: \r\n
MCInline MCBool isNewLine(const char *s)
{
    if (s) {
        if (*s == MCNewLineN) {
            return true;
        } else if (*s == MCNewLineR) { //Windows NewLine
            return true;
        }
    }
    return false;
}

MCInline MCBool isDigit(const char* w)
{
    while (*w != NUL) {
        if (MCCond_Digit(w)) {
            w++; continue;
        } else {
            return false;
        }
    }
    return true;
}

MCInline MCBool isAlphabet(const char* w)
{
    while (*w != NUL) {
        if (MCCond_Alphabet(w)) {
            w++; continue;
        } else {
            return false;
        }
    }
    return true;
}

MCInline MCBool isIdentifier(const char* w)
{
    //must start with alphabet or underbar
    if (MCCond_Alphabet(w) || *w == '_') {
        w++;
    }else{
        return false;
    }
    //can be end with alphabet or underbar or number
    while (*w != NUL) {
        if (MCCond_Alphabet(w) || MCCond_Digit(w) || *w == '_') {
            w++; continue;
        } else {
            return false;
        }
    }
    return true;
}

MCInline MCBool isFilename(const char* w)
{
    //can start with any char except '\0'
    if (w != NUL) {
        return true;
    }
    return false;
}

MCInline MCBool isInteger(const char* n)
{
    while (*n != NUL) {
        if (MCCond_Digit(n) || *n == '-') {
            n++; continue;
        } else {
            return false;
        }
    }
    return true;
}

MCInline MCBool isFloat(const char* n)
{
    MCBool havedot = false;
    while (*n != NUL) {
        if (MCCond_Digit(n) || *n == '-' || *n == '.' || *n == 'e' || *n == 'E') {
            if (*n == '.')
                havedot = true;
            n++; continue;
        } else {
            return false;
        }
    }
    return havedot;
}

MCInline MCBool isDate(const char* s)
{
    while (!isNewLine(s) && *s != NUL) {
        if (MCCond_Digit(s) || *s == '/') {
            s++; continue;
        } else {
            return false;
        }
    }
    return true;
}

//return int count
MCInline int getDate(const char* s, long* buff)
{
    const char* remain = s;
    char digit[512];
    int b = 0, i = 0;
    while (isNewLine(s) == false && *remain != NUL && *remain != MCWhiteSpace) {
        //a int
        if (MCCond_Digit(remain)) {
            digit[i++] = *remain;
        }
        else if (*remain == '/') {
            if (i == 0) {
                //no digit
                buff[b++] = 0;
            }else{
                //have digit
                digit[i] = NUL;
                buff[b++] = atoi(digit);
                i = 0;
            }
        }
        
        remain++;//next char
    }
    //last digit
    if (i == 0) {
        //no digit
        buff[b++] = 0;
    }else{
        //have digit
        digit[i] = NUL;
        buff[b++] = atoi(digit);
    }
    
    return b;
}

//MCTokenWord,
//MCTokenFloat,
//MCTokenInteger,
//MCTokenIdentifier,
//MCTokenDate,
//MCTokenComment,
//MCTokenUnknown
MCInline MCToken tokenize(const char* word)
{
    MCToken token = (MCToken){MCTokenUnknown, 0};
    //don't change the order!
    if (isFloat(word) == true) {
        token.type = MCTokenFloat;
        double dval = atof(word);
        if (dval != dval) {
            //NaN
            token.value.Double = 0.0f;
        } else {
            token.value.Double = atof(word);
        }
    }
    else if (isInteger(word) == true) {
        token.type = MCTokenInteger;
        token.value.Integer = atoi(word);
    }
    else if (isDate(word) == true) {
        token.type = MCTokenDate;
        getDate(word, token.value.Date);
    }
    else if (isFilename(word) == true) {
        if (isIdentifier(word) == true) {
            token.type = MCTokenIdentifier;
            MCLexerFill(token.value.Word, word);
        }
        else {
            token.type = MCTokenFilename;
            MCLexerFill(token.value.Word, word);
        }
    }
    else if (strncmp("#", word, 1) == 0) {
        token.type = MCTokenComment;
    }
    return token;
}

MCInline const char* readNext(const char** target_p, char buff[], MCBool isUpdate)
{
    const char* str = trimWhiteSpace(target_p);//skip whitespace
    int i = 0;
    while ( (*str != MCWhiteSpace) && !isNewLine(str) && (*str != NUL) ) {
        buff[i++] = *str++;
    }
    buff[i] = NUL;
    if (isUpdate) {
        *target_p = str;//update remain
    }
    return buff;
}

MCInline const char* readNextInThisLine(const char** target_p, char buff[], MCBool isUpdate)
{
    const char* str = trimWhiteSpace(target_p);//skip whitespace
    int i = 0;
    while ( !isNewLine(str) && (*str != NUL) ) {
        buff[i++] = *str++;
    }
    buff[i] = NUL;
    if (isUpdate) {
        *target_p = str;//update remain
    }
    return buff;
}

//return word
MCInline const char* nextWord(const char** target_p, char buff[])
{
    return readNext(target_p, buff, true);
}

MCInline const char* nextWordsInThisLine(const char** target_p, char buff[])
{
    return readNextInThisLine(target_p, buff, true);
}

MCInline const char* peekNext(const char** target_p, char buff[])
{
    return readNext(target_p, buff, false);
}

MCInline const char* skipNext(const char** target_p)
{
    const char* str = trimWhiteSpaceNewline(target_p);//skip whitespace
    const char* iter = str;
    while (*iter != MCWhiteSpace)
        iter++;
    *target_p = iter;//update remain
    return str;
}

MCInline size_t nextFloats(const char** target_p, double buff[])
{
    const char* str = trimWhiteSpaceNewline(target_p);//skip whitespace
    char linebuff[LINE_MAX];
    MCToken token;
    size_t i = 0;
    while (isNewLine(str) == false && (*str != NUL)) {
        token = tokenize(nextWord(&str, linebuff));
        if (token.type == MCTokenFloat) {
            buff[i++] = token.value.Double;
        }
        else{
            return i;
        }
    }
    //nextWord will update remain
    return i;
}

MCInline size_t nextIntegers(const char** target_p, long buff[])
{
    const char* str = trimWhiteSpaceNewline(target_p);//skip whitespace
    char linebuff[LINE_MAX];
    MCToken token;
    size_t i = 0;
    while (isNewLine(str) == false && (*str != NUL)) {
        token = tokenize(nextWord(&str, linebuff));
        if (token.type == MCTokenInteger) {
            buff[i++] = token.value.Integer;
        }else{
            return i;
        }
    }
    //nextWord will update remain
    return i;
}

MCInline size_t nextNumbersAsFloat(const char** target_p, double buff[])
{
    const char* str = trimWhiteSpaceNewline(target_p);//skip whitespace
    char linebuff[LINE_MAX];
    MCToken token;
    size_t i = 0;
    while (isNewLine(str) == false && (*str != NUL)) {
        token = tokenize(nextWord(&str, linebuff));
        if (token.type == MCTokenInteger) {
            buff[i++] = (double)token.value.Integer;
        }
        else if (token.type == MCTokenFloat) {
            buff[i++] = (double)token.value.Double;
        }
        else{
            return i;
        }
    }
    //nextWord will update remain
    return i;
}

MCInline size_t nextDates(const char** target_p, long buff[])
{
    const char* str = trimWhiteSpaceNewline(target_p);//skip whitespace
    char linebuff[LINE_MAX];
    MCToken token;
    size_t i = 0;
    while (isNewLine(str) == false && (*str != NUL)) {
        token = tokenize(nextWord(&str, linebuff));
        if (token.type == MCTokenDate) {
            buff[i++] = token.value.Date[0];
            buff[i++] = token.value.Date[1];
            buff[i++] = token.value.Date[2];
        }
    }
    //nextWord will update remain
    return i;
}

#endif /* MCFileParser_h */
