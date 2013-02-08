#ifndef _MCBuffer
#define _MCBuffer
#include "MCContext.h"
#include <stdio.h>

typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
	//
	size_t size;
	char data[];
}MCCharBuffer;

typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
	//
	size_t size;
	int data[];
}MCIntBuffer;

typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
	//
	size_t size;
	unsigned data[];
}MCUnsignedBuffer;

typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
	//
	size_t size;
	long data[];
}MCLongBuffer;

typedef struct {
	MCClass* isa;
	BOOL need_bind_method;
	int ref_count;
	//
	size_t size;
	double data[];
}MCDoubleBuffer;

MCCharBuffer* NewMCCharBuffer(size_t size);
MCIntBuffer* NewMCIntBuffer(size_t size);
MCUnsignedBuffer* NewMCUnsignedBuffer(size_t size);
MCLongBuffer* NewMCLongBuffer(size_t size);
MCDoubleBuffer* NewMCDoubleBuffer(size_t size);

#endif