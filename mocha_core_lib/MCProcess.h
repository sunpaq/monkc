#include "MCContext.h"
#include <sys/types.h>
#include <unistd.h>

#ifndef _MCProcess
#define _MCProcess _MCObject;\
	pid_t pid;\
	pid_t ppid;\
	uid_t uid;\
	uid_t euid;\
	gid_t gid;\
	gid_t egid;\

class(MCProcess);
constructor(MCProcess, xxx);

method(MCProcess, printIDs, xxx);
method(MCProcess, fork, xxx) returns(0 in child/child-pid in parent/-1 on error);

/*
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

pid_t fork(void);
*/
#endif