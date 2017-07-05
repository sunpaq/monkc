#include "MCThread.h"

oninit(MCThread)
{
	//init the vars
	pthread_once_t ponce = PTHREAD_ONCE_INIT;
	obj->once_control = ponce;
	obj->isRunOnce = 0;//default is NO
	//if you need, you can set the attribute use the raw pthread APIs
	//example: pthread_attr_getstacksize(m_thread->attribute);
	pthread_attr_init(&obj->attribute);
    
    obj->functionPointer = null;
    obj->functionArgument = null;
	return obj;
}

method(MCThread, void, bye, voida)
{
    pthread_attr_destroy(&obj->attribute);
}

method(MCThread, MCThread*, initWithFPointerArgument, void* fp, void* farg)
{
    if (fp==null)
    {
        error_log("%s\n","fp can not be nil, do nothing");
        return null;
    }
    obj->functionPointer = fp;
    obj->functionArgument = farg;
    return obj;
}

method(MCThread, MCThread*, initWithFPointer, void* fp)
{
    return MCThread_initWithFPointerArgument(obj, fp, null);
}

method(MCThread, int, detach, voida)
{
    return pthread_detach(obj->tid);
}

method(MCThread, int, start, voida)
{
    int res;
    if (obj->isRunOnce==1)
    {
        res = pthread_once(&(obj->once_control), obj->functionPointer);
        
    }else{
        
        res = pthread_create(&obj->tid,//tid, pthread_t type
                             &obj->attribute,
                             obj->functionPointer,
                             obj->functionArgument);
    }
    return res;
}

method(MCThread, int, equal, MCThread* thread)
{
    return pthread_equal(obj->tid, thread->tid);
}

utility(MCThread, int, cancelThread, pthread_t tid)
{
#ifdef __APPLE__
	return pthread_cancel(tid);
#elif __ANDROID__
	return 0;
#else
	return pthread_cancel(tid);
#endif
}

utility(MCThread, int, joinThread, pthread_t tid)
{
    //did not pass an returen value pointer
    return pthread_join(tid, NULL);
}

utility(MCThread, void, exitWithStatus, void* status)
{
    pthread_exit(status);
}

utility(MCThread, pthread_t, currentThread)
{
    return pthread_self();
}

onload(MCThread)
{
    if (load(MCObject)) {
        binding(MCThread, void, bye, voida);
        binding(MCThread, MCThread*, initWithFPointerArgument, void* fp, void* farg);
        binding(MCThread, MCThread*, initWithFPointer, void* fp);
        binding(MCThread, int, detach, voida);
        binding(MCThread, int, start, voida);
        binding(MCThread, int, equal, MCThread* thread);
        return cla;
    }else{
        return null;
    }
}

