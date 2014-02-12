#include "monkc.h"
#include <string.h>

void mc_copy_key(char* const dest, const char* src)
{
	size_t srclen = strnlen(src, MAX_KEY_CHARS-1);
	strncpy(dest, src, srclen);
	dest[srclen+1]='\0';
}

int mc_compare_key(char* const dest, const char* src)
{
	size_t srclen = strnlen(src, MAX_KEY_CHARS-1);
	return strncmp(dest, src, srclen);
}