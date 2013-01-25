#ifndef _MCBuffer
#define _MCBuffer

typedef struct {
	size_t size;
	char data[];
}MCCharBuffer;

typedef struct {
	size_t size;
	int data[];
}MCIntBuffer;

typedef struct {
	size_t size;
	unsigned data[];
}MCUnsignedBuffer;

typedef struct {
	size_t size;
	long data[];
}MCLongBuffer;

typedef struct {
	size_t size;
	double data[];
}MCDoubleBuffer;

#define NewMCCharBuffer(size) (MCCharBuffer*)mc_malloc(sizeof(MCCharBuffer)+size)
#define NewMCIntBuffer(size) (MCIntBuffer*)mc_malloc(sizeof(MCIntBuffer)+size)
#define NewMCUnsignedBuffer(size) (MCUnsignedBuffer*)mc_malloc(sizeof(MCUnsignedBuffer)+size)
#define NewMCLongBuffer(size) (MCLongBuffer*)mc_malloc(sizeof(MCLongBuffer)+size)
#define NewMCDoubleBuffer(size) (MCDoubleBuffer*)mc_malloc(sizeof(MCDoubleBuffer)+size)

#endif