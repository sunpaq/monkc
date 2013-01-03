#include "MCContext.h"

/*
The pthread API:

pthread_create (thread,attr,start_routine,arg)
pthread_exit (status)
pthread_cancel (thread)

pthread_attr_init (attr)
pthread_attr_destroy (attr)

pthread_join (threadid, status)
pthread_detach (threadid)
pthread_attr_setdetachstate (attr, detachstate)
pthread_attr_getdetachstate (attr, detachstate)

pthread_attr_getstacksize (attr, stacksize)
pthread_attr_setstacksize (attr, stacksize)
pthread_attr_getstackaddr (attr, stackaddr)
pthread_attr_setstackaddr (attr, stackaddr)

pthread_self ()
pthread_equal (thread1,thread2)

pthread_once (once_control, init_routine)

pthread_mutex_init (mutex,attr)
pthread_mutex_destroy (mutex)
//use NULL to get default attribute
pthread_mutexattr_init (attr)
pthread_mutexattr_destroy (attr)
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER; //statically init
pthread_mutex_init(mymutex) //dynamically init

pthread_mutex_lock (mutex)
pthread_mutex_trylock (mutex)
pthread_mutex_unlock (mutex)
*/

#ifndef _MCRunnable
#define _MCRunnable _MCObject;\
	_FunctionPointer(init_routine);\

class(MCRunnable);
method(MCRunnable, run, xxx);
constructor(MCRunnable, _FunctionPointer(init_routine));

#endif

#ifndef _MCThread 
#define _MCThread _MCObject;\
	pthread_t self;\
	pthread_attr_t attribute;\
	BOOL isRunOnce;\
	size_t stacksize;\
	void*  stackaddr;\
	MCRunnable* runnable;\

class(MCThread);
method(MCThread, start, void* result);
method(MCThread, stop, void* result);
method(MCThread, join, MCThread* threadToWait, void** result);
method(MCThread, detach, MCThread* thread);
method(MCThread, equal, MCThread* thread);
method(MCThread, bye, xxx);

void MCThread_cancel(MCThread* thread);
pthread_once_t once_control;

constructor(MCThread, MCRunnable* runnable);

#define MCMutexLock(lock) pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER
#define MCLock(lock) pthread_mutex_lock(&lock)
#define MCUnlock(lock) pthread_mutex_unlock(&lock)

#endif