#include "MCContext.h"
#include <sys/types.h>
#include <unistd.h>

#ifndef _MCProcess
#define _MCProcess _MCObject;\
	pid_t pid;\
	pid_t ppid;

class(MCProcess);

method(MCProcess, printPID, xxx);
method(MCProcess, printPPID, xxx);
constructor(MCProcess, xxx);

pid_t getpid(void);
pid_t getppid(void);

#endif