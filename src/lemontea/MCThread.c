#include "MCThread.h"


/* MCRunnable */


loader(MCRunnable)
{	
	binding(MCRunnable, void, run, xxx);
	binding(MCRunnable, MCRunnable*, initWithFunctionPointer, void (*init_routine)(void));
}

initer(MCRunnable)
{
	this->init_routine = 0;
}

method(MCRunnable, MCRunnable*, initWithFunctionPointer, void (*init_routine)(void))
{
	this->init_routine = init_routine;
	return this;
}

method(MCRunnable, void, run, xxx)
{
	//do nothing
}

/* MCThread */

loader(MCThread)
{
	binding(MCThread, MCThread*, initWithRunnable, MCRunnable* runnable);
	binding(MCThread, int, start, void* result);
	binding(MCThread, int, equal, MCThread* thread);
	binding(MCThread, void, bye, xxx);
}

initer(MCThread)
{
	//init the vars
	pthread_once_t ponce = PTHREAD_ONCE_INIT;
	this->once_control = ponce;
	this->isRunOnce = 0;//default is NO
	//if you need, you can set the attribute use the raw pthread APIs
	//example: pthread_attr_getstacksize(m_thread->attribute);
	pthread_attr_init(&this->attribute);
}

method(MCThread, MCThread*, initWithRunnable, MCRunnable* runnable)
{
	if (runnable==nil)
	{
		error_log("%s\n","runnable can not be nil, do nothing");
		return;
	}
	this->runnable = retain(runnable);
	return this;
}

int MCThread_join(MCThread* thread, void** result)
{
	return pthread_join(thread->self, result);
}

int MCThread_detach(MCThread* thread)
{
	return pthread_detach(thread->self);
}

int MCThread_cancel(MCThread* thread)
{
	return pthread_cancel(thread->self);
}

//must call this inside the runnable run_routine
void MCThread_stop(void* result)
{
	pthread_exit(result);
}

pthread_t MCThread_self()
{
	return pthread_self();
}

//this is a bridge between static pthread callback
//and dynamic Mocha inherit tree method calling
static void *fireRun(MCThread* this)
{
	ff(this->runnable, run, nil);//no result
}

method(MCThread, int, start, void* result)
{
	int res;
	if (this->isRunOnce==1)
	{
		if (this->runnable->init_routine!=nil)
			res = pthread_once(&(this->once_control), this->runnable->init_routine);
		else
			res = pthread_once(&(this->once_control), fireRun);

	}else{
		if (this->runnable->init_routine!=nil)
			res = pthread_create(&this->self,//tid, pthread_t type
				   &this->attribute, 
				   this->runnable->init_routine, 
			       this);//no argument
		else
			res = pthread_create(&this->self,//tid, pthread_t type
				   &this->attribute, 
				   fireRun, 
			       this);//no argument
	}
	return res;
}

method(MCThread, int, equal, MCThread* thread)
{
	return pthread_equal(this->self, thread->self);
}

method(MCThread, void, bye, xxx)
{
	pthread_attr_destroy(&this->attribute);
	release(&(this->runnable));
}

