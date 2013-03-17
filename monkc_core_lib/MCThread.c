#include "MCThread.h"


/* MCRunnable */


constructor(MCRunnable, _FunctionPointer(init_routine))
{	
	link_class(MCRunnable, MCObject, nil)
	{
		binding(MCRunnable, run, xxx);
	}

	this->init_routine = init_routine;
	return this;
}

method(MCRunnable, run, xxx)
{
	//do nothing
}

constructor(MCThread, MCRunnable* runnable)
{
	if (runnable==nil)
	{
		error_log("%s\n","runnable can not be nil, do nothing");
		return;
	}

	link_class(MCThread, MCObject, nil)
	{
		binding(MCThread, start, void* result) 							returns(int);
		binding(MCThread, equal, MCThread* thread) 						returns(BOOL);
		binding(MCThread, bye, xxx);
	}
	//init the vars
	pthread_once_t ponce = PTHREAD_ONCE_INIT;
	this->once_control = ponce;
	this->isRunOnce = NO;//default is NO
	retain(runnable);
	this->runnable = runnable;
	pthread_attr_init(&this->attribute);
	//if you need, you can set the attribute use the raw pthread APIs
	//example: pthread_attr_getstacksize(m_thread->attribute);
	return this;
}

/* MCThread */

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

method(MCThread, start, void* result)
{
	int res;
	if (this->isRunOnce==YES)
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

method(MCThread, equal, MCThread* thread)
{
	return pthread_equal(this->self, thread->self);
}

method(MCThread, bye, xxx)
{
	pthread_attr_destroy(&this->attribute);
	relnil(this->runnable);
}

