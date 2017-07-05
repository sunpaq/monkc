/* MCThread */

#ifndef MCThread_
#define MCThread_

#include <pthread.h>
#include "monkc.h"

class(MCThread, MCObject,
	pthread_t tid;
	pthread_attr_t attribute;
	pthread_once_t once_control;
	int isRunOnce;
    void* functionPointer;
    void* functionArgument;
);

method(MCThread, void, bye, voida);
method(MCThread, MCThread*, initWithFPointerArgument, void* fp, void* farg);
method(MCThread, MCThread*, initWithFPointer, void* fp);
method(MCThread, int, detach, voida);
method(MCThread, int, start, voida);
method(MCThread, int, equal, MCThread* thread);

utility(MCThread, int, cancelThread, pthread_t tid);
utility(MCThread, int, joinThread, pthread_t tid);
utility(MCThread, void, exitWithStatus, void* status);
utility(MCThread, pthread_t, currentThread);

/*
The pthread API:

[ pthread_attr_t ]

pthread_attr_init (attr)
pthread_attr_destroy (attr)
pthread_attr_setdetachstate (attr, detachstate)
pthread_attr_getdetachstate (attr, detachstate)
pthread_attr_getstacksize (attr, stacksize)
pthread_attr_setstacksize (attr, stacksize)
pthread_attr_getstackaddr (attr, stackaddr)
pthread_attr_setstackaddr (attr, stackaddr)

[ pthread control ]

pthread_create (thread,attr,start_routine,arg)
pthread_join (threadid, status)
pthread_detach (threadid)
pthread_exit (status)
pthread_cancel (thread)
pthread_self ()
pthread_equal (thread1,thread2)
pthread_once (once_control, init_routine)

[ pthread_mutex_attr_t ]

pthread_mutex_init (mutex,attr)
pthread_mutex_destroy (mutex)
pthread_mutexattr_init (attr) //use NULL to get default attribute
pthread_mutexattr_destroy (attr)
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER; //statically init
pthread_mutex_init(mymutex) //dynamically init

//mutex is "sleep-waiting" lock, cpu core can do other things to wait for lock.
pthread_mutex_lock (mutex)
pthread_mutex_trylock (mutex)
pthread_mutex_unlock (mutex)

[ No Spin attribute! ]

pthread_spinlock_t
pthread_spin_init
pthread_spin_destroy

//spin is "busy-waiting" lock, cpu core do nothing but still checking the lock
pthread_spin_lock (pthread_spinlock_t *lock);
pthread_spin_trylock (pthread_spinlock_t *lock);
pthread_spin_unlock (pthread_spinlock_t *lock);

[ pthread_cond_attr_t ]

pthread_cond_t myconvar = PTHREAD_COND_INITIALIZER;
pthread_cond_init (condition,attr)
pthread_cond_destroy (condition)
pthread_condattr_init (attr)
pthread_condattr_destroy (attr)

pthread_cond_wait (condition,mutex)
pthread_cond_signal (condition)
pthread_cond_broadcast (condition)

//usage:
pthread_mutex_lock       pthread_mutex_lock
pthread_cond_wait        pthread_cond_signal
pthread_mutex_unlock     pthread_mutex_unlock

*/


/* MC locks */


#define MCMutexLockNew(lock) 							pthread_mutex_t lock
#define MCMutexAttrNew(attr) 							pthread_mutexattr_t attr
#define MCMutexLockStaticInitializer 					PTHREAD_MUTEX_INITIALIZER
#define MCMutexLockInit(lock, attr) 					pthread_mutex_init(&lock, attr)
#define MCMutexLockDestroy(lock) 						pthread_mutex_destroy(&lock)

#define MCMutexLock(lock) 								pthread_mutex_lock(&lock)
#define MCMutexTrylock(lock) 							pthread_mutex_trylock(&lock)
#define MCMutexUnlock(lock) 							pthread_mutex_unlock(&lock)

//spin lock have no static initializer
#define MCSpinLockInit(lock, is_processes_shared)       pthread_spin_init(&lock, is_processes_shared)//YES/NO = non-zero/zero 
//#define MCSpinLockNew(lock) 							pthread_spinlock_t lock
//no spin attribute
#define MCSpinLockDestroy(lock) 						pthread_spin_destroy(&lock)
#define MCSpinLock(lock) 								pthread_spin_lock(&lock)
#define MCSpinTrylock(lock) 							pthread_spin_trylock(&lock)
#define MCSpinUnlock(lock) 								pthread_spin_unlock(&lock)

#define MCCondLockNew(lock) 							pthread_cond_t lock
#define MCCondAttrNew(attr) 							pthread_condattr_t attr
#define MCCondLockStaticInitializer 					PTHREAD_COND_INITIALIZER
#define MCCondLockInit(lock, attr) 						pthread_cond_init(&lock, attr)
#define MCCondLockDestroy(lock) 						pthread_cond_destroy(&lock)

#define MCCondWait(cond, mutex) 						pthread_cond_wait(&cond, &mutex)
#define MCCondSignal(cond) 								pthread_cond_signal(&cond)
#define MCCondBroadcast(cond) 							pthread_cond_broadcast(&cond)

#endif

//if you need, you can set the attribute use the raw pthread APIs
//example: pthread_attr_getstacksize(m_thread->attribute);