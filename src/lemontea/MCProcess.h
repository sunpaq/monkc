#include "MCContext.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

/*
pid 0 is a swapper(scheduler)
pid 1 is a init
*/

#ifndef MCProcess_
#define MCProcess_ 

monkc(MCProcess);
	pid_t pid;
	pid_t ppid;
	uid_t uid;
	uid_t euid;
	gid_t gid;
	gid_t egid;
end(MCProcess);

method(MCProcess, void, printIDs, xxx);
//returns(0 in child/child-pid in parent/-1 on error)
method(MCProcess, int, fork, xxx);

//may be not supported by OS
method(MCProcess, int, registerAtExitCallback, void (*func)(void));
method(MCProcess, void, exitWithStatus, int status);
method(MCProcess, pid_t, waitAnyChildExit, int* statusAddr);

typedef enum {
	wait_no_option=0,
	wait_continued=WCONTINUED,
	wait_no_hang=WNOHANG,
//The waitpid function will not block if a child specified by pid is not immediately available. In
//this case, the return value is 0.
	wait_untraced=WUNTRACED
//If the implementation supports job control, the status of any child specified by pid that has
//stopped, and whose status has not been reported since it has stopped, is returned.
}MCProcessOptions;
//wait_continued | wait_no_hang

method(MCProcess, pid_t, waitPIDChildExit, pid_t pid, int* statusAddr, int options);

method(MCProcess, int, isChildExitNormal, int status);
method(MCProcess, int, getChildExitLowOrder8Bit, int status);

method(MCProcess, int, isChildExitBySignal, int status);
method(MCProcess, int, getChildTerminateSignal, int status);
method(MCProcess, int, isCoreDumpFileGenerated, int status);

method(MCProcess, int, isChildStopped, int status);
method(MCProcess, int, getChildStopSignal, int status);
method(MCProcess, int, isChildContinued, int status);

typedef struct MCProcessRUseage_struct {
    struct rusage* rusage_p;
    char* description;
} MCProcessRUseage;
//wait3
method(MCProcess, 
	pid_t, waitAnyChildExitGetResourceUseage, 
	int* statusAddr, int options, MCProcessRUseage* useage);
//wait4
method(MCProcess, 
	pid_t, waitPIDChildExitGetResourceUseage, 
	pid_t pid, int* statusAddr, int options, MCProcessRUseage* useage);

#endif
/*
The origin APIs:
(i strongly recommand to use the origin API than these wrappers
however these wrappers only as a document for esay )

pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

pid_t fork(void);
pid_t vfork(void);

SIGCHLD
#include <sys/wait.h>
pid_t wait(int *statloc);
pid_t waitpid(pid_t pid, int *statloc, int options);

WIFEXITED(status) //True if status was returned for a child that terminated normally.
WEXITSTATUS (status) //to fetch the low-order 8 bits of the argument that the child passed.

WIFSIGNALED(status)
WTERMSIG(status)

WCOREDUMP(status)

WIFSTOPPED(status)
WSTOPSIG(status)

WIFCONTINUED(status) //for waitpid only
int atexit(void (*func)(void));

zombie is cause by unresponsed living father

1. responsed father will clean the child death.
2. father dead init will clean the child death.

fork twice and exit first one.
will force child death be management by init.
to avoid unresponsed father.

by calling fork twice, [grandfather, father, child] and father exit
can avoid child became zombie process(parent did not handle his death)
[grandfather, x, child] child became orphan, will management by init(pid=1) process

*/
