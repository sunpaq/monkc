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

static const char MCWhiteSpace = ' ';
static const char MCBackSlash0 = '\0';

#define MCCond_Digit(w)     (*w >= '0' && *w <= '9')
#define MCCond_Alphabet(w)  (*w >= 'a' && *w <= 'z') || (*w >= 'A' && *w <= 'Z')

MCInline size_t MCCopyString(char* const dest, const char* src)
{
    size_t len = strlen(src);
    strncpy(dest, src, len);
    dest[len] = MCBackSlash0;
    return len;
}

//Old Mac9 end of line sequence: \r
//Unix OSX end of line sequence: \n
//Windows  end of line sequence: \r\n
MCInline MCBool isNewLine(const char* s)
{
    if (*s == '\n') {
        return MCTrue;
    } else if (*s == '\r') { //Windows NewLine
        return MCTrue;
    }
    return MCFalse;
}

MCInline MCBool isDigit(const char* w)
{
    while (*w != MCBackSlash0) {
        if (MCCond_Digit(w)) {
            w++; continue;
        } else {
            return MCFalse;
        }
    }
    return MCTrue;
}

MCInline MCBool isAlphabet(const char* w)
{
    while (*w != MCBackSlash0) {
        if (MCCond_Alphabet(w)) {
            w++; continue;
        } else {
            return MCFalse;
        }
    }
    return MCTrue;
}

MCInline MCBool isIdentifier(const char* w)
{
    //must start with alphabet or underbar
    if (MCCond_Alphabet(w) || *w == '_') {
        w++;
    }else{
        return MCFalse;
    }
    //can be end with alphabet or underbar or number
    while (*w != MCBackSlash0) {
        if (MCCond_Alphabet(w) || MCCond_Digit(w) || *w == '_') {
            w++; continue;
        } else {
            return MCFalse;
        }
    }
    return MCTrue;
}

MCInline MCBool isInteger(const char* n)
{
    while (*n != MCBackSlash0) {
        if (MCCond_Digit(n) || *n == '-') {
            n++; continue;
        } else {
            return MCFalse;
        }
    }
    return MCTrue;
}

MCInline MCBool isFloat(const char* n)
{
    while (*n != MCBackSlash0) {
        if (MCCond_Digit(n) || *n == '-' || *n == '.' || *n == 'e' || *n == 'E') {
            n++; continue;
        } else {
            return MCFalse;
        }
    }
    return MCTrue;
}

MCInline MCBool isDate(const char* s)
{
    while (isNewLine(s) == MCFalse && *s != MCBackSlash0) {
        if (MCCond_Digit(s) || *s == '/') {
            s++; continue;
        } else {
            return MCFalse;
        }
    }
    return MCTrue;
}

//return int count
MCInline int getDate(const char* s, long* buff)
{
    const char* remain = s;
    char digit[512];
    int b = 0, i = 0;
    while (isNewLine(s) == MCFalse && *remain != MCBackSlash0) {
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
                digit[i] = MCBackSlash0;
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
        digit[i] = MCBackSlash0;
        buff[b++] = atoi(digit);
        i = 0;
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
    
    if (isIdentifier(word) == MCTrue) {
        token.type = MCTokenIdentifier;
        MCCopyString(token.value.Word, word);
    }
    else if (isFloat(word) == MCTrue) {
        token.type = MCTokenFloat;
        token.value.Double = atof(word);
    }
    else if (isInteger(word) == MCTrue) {
        token.type = MCTokenInteger;
        token.value.Integer = atoi(word);
    }
    else if (isDate(word) == MCTrue) {
        token.type = MCTokenDate;
        getDate(word, token.value.Date);
    }
    else if (strncmp("#", word, 1) == 0) {
        token.type = MCTokenComment;
    }
    return token;
}

//return remain string
MCInline const char* trimWhiteSpace(const char** target_p)
{
    const char* iter = *target_p;
    while (*iter == ' ')
        iter++;
    *target_p = iter;//update remain
    return iter;
}

//return word
MCInline const char* nextWord(const char** target_p, char buff[])
{
    const char* str = trimWhiteSpace(target_p);//skip whitespace
    int i = 0;
    while ( (*str != ' ') && isNewLine(str) == MCFalse && (*str != '\0') ) {
        buff[i++] = *str++;
    }
    buff[i] = '\0';
    *target_p = str;//update remain
    return buff;
}

#endif /* MCFileParser_h */
