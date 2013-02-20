#include "MCProcess.h"

constructor(MCProcess, xxx)
{
	link_class(MCProcess, MCObject, nil)
	{
		have_method(MCProcess, printIDs, xxx);
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
