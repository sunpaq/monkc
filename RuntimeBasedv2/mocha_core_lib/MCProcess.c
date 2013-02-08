#include "MCProcess.h"

constructor(MCProcess, xxx)
{
	link_class(MCProcess, MCObject, nil)
	{
		have_method(MCProcess, printPID, xxx);
		have_method(MCProcess, printPPID, xxx);
	}

	this->pid=getpid();
	this->ppid=getppid();

	return this;
}

method(MCProcess, printPID, xxx)
{
	printf("%d\n", this->pid);
}

method(MCProcess, printPPID, xxx)
{
	printf("%d\n", this->ppid);
}

