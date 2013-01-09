#include "MCThread.h"

<<<<<<< HEAD
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
=======

/* MCRunnable */


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
	}
	this->init_routine = init_routine;
	return this;
}


/* MCThread */


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
>>>>>>> version 0108
	ff(this->runnable, MK(run), nil);//no result
}

method(MCThread, start, void* result)
{
<<<<<<< HEAD
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
=======
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
>>>>>>> version 0108
}

method(MCThread, join, MCThread* threadToWait, void** result)
{
<<<<<<< HEAD
	pthread_join(threadToWait->self, result);
}

method(MCThread, detach, MCThread* thread)
{
	pthread_detach(thread->self);
}

=======
	return pthread_join(threadToWait->self, result);
}

method(MCThread, detach, MCThread* thread)
{
	return pthread_detach(thread->self);
}

>>>>>>> version 0108
method(MCThread, equal, MCThread* thread)
{
	return pthread_equal(this->self, thread->self);
}

method(MCThread, bye, xxx)
{
	pthread_attr_destroy(&this->attribute);
	release(this->runnable);
<<<<<<< HEAD
	//call(this, MCThread, stop, nil);
}

void MCThread_cancel(MCThread* thread)
{
	pthread_cancel(thread->self);
=======
>>>>>>> version 0108
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
<<<<<<< HEAD
	this->isRunOnce = NO;//default is NO
	this->runnable = runnable;
	pthread_attr_init(&this->attribute);

	//size_t stacksize
	//void*  stackaddr
	return this;
}
=======
	this->once_control = PTHREAD_ONCE_INIT;
	this->isRunOnce = NO;//default is NO
	this->runnable = runnable;
	pthread_attr_init(&this->attribute);
	//if you need, you can set the attribute use the raw pthread APIs
	//example: pthread_attr_getstacksize(m_thread->attribute);
	return this;
}
>>>>>>> version 0108
