
int mc_atomic_get_integer(volatile int* target);
void* mc_atomic_get_pointer(volatile void** target);
int mc_atomic_set_integer(volatile int* target, volatile int old, volatile int value);
int mc_atomic_set_pointer(volatile void** target, volatile void* old, volatile void* value);

inline void mc_trylock(int* lock_p);
inline void mc_unlock(int* lock_p);