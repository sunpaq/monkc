#include "MCThread.h"

method(MCRunnable, run, xxx)
{
	//do nothing
}

constructor(MCRunnable, _FunctionPointer(init_routine))
{	
	super_init(this, MCObject, nil);
	if(set_class(this, "MCRunnable", "MCObject"))
	{
		bind(this, MK(run), MV(MCRunnable, run));
		//bind(this, MK(bye), MV(MCRunnable, bye));
	}
	this->init_routine = init_routine;

	return this;
}

/* MCThread */
//this is a bridge between static pthread callback
//and dynamic Mocha inherit tree method calling
static void *fireRun(MCThread* this)
{
	ff(this->runnable, MK(run), nil);//no result
}

method(MCThread, start, void* result)
{
	if (this->runnable->init_routine!=nil)
	{
		this->isRunOnce = YES;
		once_control = PTHREAD_ONCE_INIT;
		pthread_once(&once_control, 
			         this->runnable->init_routine);
	}

	pthread_create(&this->self, 
				   &this->attribute, 
				   fireRun, 
			       this);//no argument
}

method(MCThread, stop, void* result)
{
	pthread_exit(result);
}

method(MCThread, join, MCThread* threadToWait, void** result)
{
	pthread_join(threadToWait->self, result);
}

method(MCThread, detach, MCThread* thread)
{
	pthread_detach(thread->self);
}

method(MCThread, equal, MCThread* thread)
{
	return pthread_equal(this->self, thread->self);
}

method(MCThread, bye, xxx)
{
	pthread_attr_destroy(&this->attribute);
	release(this->runnable);
	//call(this, MCThread, stop, nil);
}

void MCThread_cancel(MCThread* thread)
{
	pthread_cancel(thread->self);
}

constructor(MCThread, MCRunnable* runnable)
{
	if (runnable==nil)
	{
		error_log("%s\n","runnable can not be nil, do nothing");
		return;
	}

	super_init(this, MCObject, nil);
	if(set_class(this, "MCThread", "MCObject")){
		bind(this, MK(start), MV(MCThread, start));
		bind(this, MK(stop), MV(MCThread, stop));
		bind(this, MK(join), MV(MCThread, join));
		bind(this, MK(detach), MV(MCThread, detach));
		bind(this, MK(equal), MV(MCThread, equal));
		bind(this, MK(bye), MV(MCThread, bye));
	}
	//init the vars
	this->isRunOnce = NO;//default is NO
	this->runnable = runnable;
	pthread_attr_init(&this->attribute);

	//size_t stacksize
	//void*  stackaddr
	return this;
}
