#include <sys/socket.h>

#ifndef _MCSocket 
#define _MCSocket _MCObject;\
	unsigned tid;\

class(MCSocket);
method(MCSocket, new, xxx);
constructor(MCSocket, xxx);

#endif