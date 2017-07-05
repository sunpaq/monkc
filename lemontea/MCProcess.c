#include "MCProcess.h"

oninit(MCProcess)
{
    if (init(MCObject)) {
        obj->pid=getpid();
        obj->ppid=getppid();
        obj->uid=getuid();
        obj->euid=geteuid();
        obj->gid=getgid();
        obj->egid=getegid();
        return obj;
    }else{
        return null;
    }
}

method(MCProcess, void, printIDs, voida)
{
	printf("pid[%d]ppid[%d]uid[%d]euid[%d]gid[%d]egid[%d]\n", 
		obj->pid, obj->ppid, obj->uid, obj->euid, obj->gid, obj->egid);
}

method(MCProcess, int, fork, voida)
{
	//pid_t fork(void);
	//copy-on-write (COW)
	//typically a "page" in a virtual memory system
	return fork();
}

method(MCProcess, int, registerAtExitCallback, void (*func)(void))
{
	if(atexit(func)==0)
		return 0;//success
	else
		return -1;//error
}

method(MCProcess, void, exitWithStatus, int status)
{
	//this is a system call
	_exit(status);
}

method(MCProcess, pid_t, waitAnyChildExit, int* statusAddr)
{
	return wait(statusAddr);
}

method(MCProcess, pid_t, waitPIDChildExit, pid_t pid, int* statusAddr, int options)
{
	return waitpid(pid, statusAddr, options);
}

method(MCProcess, int, isChildExitNormal, int status)
{
	if(WIFEXITED(status))
		return 1;
	else
		return 0;
}

method(MCProcess, int, getChildExitLowOrder8Bit, int status)
{
	return WEXITSTATUS(status);
}

method(MCProcess, int, isChildExitBySignal, int status)
{
	if (WIFSIGNALED(status))
		return 1;
	else
		return 0;
}

method(MCProcess, int, getChildTerminateSignal, int status)
{
	return WTERMSIG(status);
}

method(MCProcess, int, isCoreDumpFileGenerated, int status)
{
	return WCOREDUMP(status);
}

method(MCProcess, int, isChildStopped, int status)
{
	if (WIFSTOPPED(status))
		return 1;
	else
		return 0;
}

method(MCProcess, int, getChildStopSignal, int status)
{
	return WSTOPSIG(status);
}

//method(MCProcess, int, isChildContinued, int status)
//{
//	if(WIFCONTINUED(status))
//		return 1;
//	else
//		return 0;
//}

//method(MCProcess, pid_t, waitAnyChildExitGetResourceUseage, int* statusAddr, int options, MCProcessRUseage* useage)
//{
//	return wait3(statusAddr, options, useage->rusage_p);
//}

method(MCProcess, pid_t, waitPIDChildExitGetResourceUseage, pid_t pid, int* statusAddr, int options, MCProcessRUseage* useage)
{
	return wait4(pid, statusAddr, options, useage->rusage_p);
}

onload(MCProcess)
{
    if (load(MCObject)) {
        binding(MCProcess, void, printIDs);
        binding(MCProcess, int, fork);
        
        binding(MCProcess, int, registerAtExitCallback, void (*func)(void));
        binding(MCProcess, void, exitWithStatus, int status);
        binding(MCProcess, pid_t, waitAnyChildExit, int* statusAddr);
        
        binding(MCProcess, pid_t, waitPIDChildExit, pid_t pid, int* statusAddr, int options);
        binding(MCProcess, int, isChildExitNormal, int status);
        binding(MCProcess, int, getChildExitLowOrder8Bit, int status);
        binding(MCProcess, int, isChildExitBySignal, int status);
        binding(MCProcess, int, getChildTerminateSignal, int status);
        binding(MCProcess, int, isCoreDumpFileGenerated, int status);
        binding(MCProcess, int, isChildStopped, int status);
        binding(MCProcess, int, getChildStopSignal, int status);
        //binding(MCProcess, int, isChildContinued, int status);
        //binding(MCProcess, pid_t, waitAnyChildExitGetResourceUseage, int* statusAddr, int options, MCProcessRUseage* useage);
        binding(MCProcess, pid_t, waitPIDChildExitGetResourceUseage, pid_t pid, int* statusAddr, int options, MCProcessRUseage* useage);
        return cla;
    }else{
        return null;
    }
}
