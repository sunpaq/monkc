#include "monkc.h"


inline void mc_trylock(int* lock_p)
{
	if(lock_p==nil){
		error_log("mc_trylock(int* lock_p) lock_p is nil\n");
		return;
	}

	for(;;){
		if(mc_atomic_get_integer(lock_p) != 0)
			continue;
		if(!mc_atomic_set_integer(lock_p, 0, 1))
			break;
	}
}

inline void mc_unlock(int* lock_p)
{
	if(lock_p==nil){
		error_log("mc_unlock(int* lock_p) lock_p is nil\n");
		return;
	}

	(*lock_p) = 0;
}

