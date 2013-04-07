#include "MCProcess.h"

constructor(MCProcess, xxx)
{
	link_class(MCProcess, MCObject, nil)
	{
		binding(MSNA, MCProcess, printIDs, xxx);
		binding(MS(2,I,P), MCProcess, fork, xxx) returns(0 in child/child-pid in parent/-1 on error);
		binding(MS(2,I,P), MCProcess, vfork, xxx) returns(0 in child/child-pid in parent/-1 on error);

		binding(MS(2,P,P), MCProcess, registerAtExitCallback, _FunctionPointer(func));
		binding(MS(2,P,I), MCProcess, exitWithStatus, int status);
		binding(MS(2,I,P), MCProcess, waitAnyChildExit, int* statusAddr) returns(pid_t);
		binding(MS(4,I,I,P,I), MCProcess, waitPIDChildExit, pid_t pid, int* statusAddr, MCProcessOptions options) returns(pid_t);

		binding(MS(2,I,I), MCProcess, isChildExitNormal, int status) returns(BOOL);
		binding(MS(2,I,I), MCProcess, getChildExitLowOrder8Bit, int status) returns(int);

		binding(MS(2,I,I), MCProcess, isChildExitBySignal, int status) returns(BOOL);
		binding(MS(2,I,I), MCProcess, getChildTerminateSignal, int status) returns(int signalNum);
		binding(MS(2,I,I), MCProcess, isCoreDumpFileGenerated, int status) returns(BOOL);

		binding(MS(2,I,I), MCProcess, isChildStopped, int status) returns(BOOL);
		binding(MS(2,I,I), MCProcess, getChildStopSignal, int status) returns(int signalNum);
		binding(MS(2,I,I), MCProcess, isChildContinued, int status) returns(BOOL);

		binding(MS(4,I,P,I,P), MCProcess, waitAnyChildExitGetResourceUseage, 
			int* statusAddr, int options, MCProcessRUseage* useage) returns(pid_t);

		binding(MS(4,I,I,P,I,P), MCProcess, waitPIDChildExitGetResourceUseage, pid_t pid,
			int* statusAddr, int options, MCProcessRUseage* useage) returns(pid_t);
	}

	this->pid=getpid();
	this->ppid=getppid();
	this->uid=getuid();
	this->euid=geteuid();
	this->gid=getgid();
	this->egid=getegid();

	return this;
}

method(MCProcess, printIDs, xxx)
{
	printf("pid[%d]ppid[%d]uid[%d]euid[%d]gid[%d]egid[%d]\n", 
		this->pid, this->ppid, this->uid, this->euid, this->gid, this->egid);
}

method(MCProcess, fork, xxx) returns(0 in child/child-pid in parent/-1 on error)
{
	//pid_t fork(void);
	//copy-on-write (COW)
	//typically a "page" in a virtual memory system
	return fork();
}

method(MCProcess, vfork, xxx) returns(0 in child/child-pid in parent/-1 on error)
{
	//pid_t vfork(void);
	//no copy, so the vfork will be faster than fork
	return vfork();
}

method(MCProcess, registerAtExitCallback, _FunctionPointer(func)) returns(RES)
{
	if(atexit(func)==0)
		return SUCCESS;
	else
		return ERROR;
}

method(MCProcess, exitWithStatus, int status)
{
	//this is a system call
	_exit(status);
}

method(MCProcess, waitAnyChildExit, int* statusAddr) returns(pid_t)
{
	return wait(statusAddr);
}

method(MCProcess, waitPIDChildExit, pid_t pid, int* statusAddr, int options) returns(pid_t)
{
	return waitpid(pid, statusAddr, options);
}

method(MCProcess, isChildExitNormal, int status) returns(BOOL)
{
	if(WIFEXITED(status))
		return YES;
	else
		return NO;
}

method(MCProcess, getChildExitLowOrder8Bit, int status) returns(int)
{
	return WEXITSTATUS(status);
}

method(MCProcess, isChildExitBySignal, int status) returns(BOOL)
{
	if (WIFSIGNALED(status))
		return YES;
	else
		return NO;
}

method(MCProcess, getChildTerminateSignal, int status) returns(int signalNum)
{
	return WTERMSIG(status);
}

method(MCProcess, isCoreDumpFileGenerated, int status) returns(BOOL)
{
	return WCOREDUMP(status);
}

method(MCProcess, isChildStopped, int status) returns(BOOL)
{
	if (WIFSTOPPED(status))
		return YES;
	else
		return NO;
}

method(MCProcess, getChildStopSignal, int status) returns(int signalNum)
{
	return WSTOPSIG(status);
}

method(MCProcess, isChildContinued, int status) returns(BOOL)
{
	if(WIFCONTINUED(status))
		return YES;
	else
		return NO;
}

method(MCProcess, waitAnyChildExitGetResourceUseage, 
	int* statusAddr, int options, MCProcessRUseage* useage) returns(pid_t)
{
	return wait3(statusAddr, options, useage);
}

method(MCProcess, waitPIDChildExitGetResourceUseage, pid_t pid,
	int* statusAddr, int options, MCProcessRUseage* useage) returns(pid_t)
{
	return wait4(pid, statusAddr, options, useage);
}