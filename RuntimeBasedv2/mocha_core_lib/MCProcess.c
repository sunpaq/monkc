#include "MCProcess.h"

method(MCProcess, printPID, xxx)
{
	printf("%d\n", this->pid);
}

method(MCProcess, printPPID, xxx)
{
	printf("%d\n", this->ppid);
}

constructor(MCProcess, xxx)
{
	link_class(MCProcess, MCObject, nil)
	{
		have_method(MCProcess, printPID);
		have_method(MCProcess, printPPID);
	}

	this->pid=getpid();
	this->ppid=getppid();

	return this;
}