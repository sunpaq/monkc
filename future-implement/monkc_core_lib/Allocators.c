/*
Copyright (c) <2013>, <Sun Yuli>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <Monk-C> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "MCRuntime.h"

/*
	Memory Allocators

	alternative allocators in APUE
	1. libmalloc
	2. vmalloc
	3. quick-fit
	4. alloca ---> can alloc mem on stack
*/

//pthread_mutex_t _mc_alloc_mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_t _mc_free_mutex = PTHREAD_MUTEX_INITIALIZER;

//gcc will link the thread safe version?

void* mc_malloc(size_t size)
{
	//pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = malloc(size);
		((MCObject*)ret)->ref_count = 1;
	//pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

extern void _push_anony_obj(MCObject* anony);
void* mc_malloc_anony(size_t size)
{
	//pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = malloc(size);
		((MCObject*)ret)->ref_count = REFCOUNT_ANONY_OBJ;
		_push_anony_obj((MCObject*)ret);
	//pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

void* mc_calloc(size_t size)
{
	//pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = calloc(1, size);
		((MCObject*)ret)->ref_count = 1;
	//pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

void* mc_realloc(void* ptr, size_t size)
{
	//pthread_mutex_lock(&_mc_alloc_mutex);
		void* ret = realloc(ptr, size);
	//pthread_mutex_unlock(&_mc_alloc_mutex);
	return ret;
}

void mc_free(void *ptr)
{
	//pthread_mutex_lock(&_mc_free_mutex);
		free(ptr);
	//pthread_mutex_unlock(&_mc_free_mutex);
}

