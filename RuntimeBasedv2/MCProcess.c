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
	super_init(this, MCObject, nil);

	if (set_class(this, MK(MCProcess), MK(MCObject)))
	{
		bind_method(this, MK(printPID), MV(MCProcess, printPID));
		bind_method(this, MK(printPPID), MV(MCProcess, printPPID));
	}

	this->pid=getpid();
	this->ppid=getppid();

	return this;
}