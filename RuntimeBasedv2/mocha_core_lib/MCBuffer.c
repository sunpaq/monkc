#include "MCBuffer.h"

MCCharBuffer* NewMCCharBuffer(size_t size)
{
	MCCharBuffer* instance = (MCCharBuffer*)mc_malloc(sizeof(MCCharBuffer)+size);
	instance->size = size;
	//
	instance->isa = nil;
	instance->need_bind_method = NO;
	instance->ref_count = 1;
}

MCIntBuffer* NewMCIntBuffer(size_t size)
{
	MCIntBuffer* instance = (MCIntBuffer*)mc_malloc(sizeof(MCIntBuffer)+size);
	instance->size = size;
	//
	instance->isa = nil;
	instance->need_bind_method = NO;
	instance->ref_count = 1;
}

MCUnsignedBuffer* NewMCUnsignedBuffer(size_t size)
{
	MCUnsignedBuffer* instance = (MCUnsignedBuffer*)mc_malloc(sizeof(MCUnsignedBuffer)+size);
	instance->size = size;
	//
	instance->isa = nil;
	instance->need_bind_method = NO;
	instance->ref_count = 1;
}

MCLongBuffer* NewMCLongBuffer(size_t size)
{
	MCLongBuffer* instance = (MCLongBuffer*)mc_malloc(sizeof(MCLongBuffer)+size);
	instance->size = size;
	//
	instance->isa = nil;
	instance->need_bind_method = NO;
	instance->ref_count = 1;
}

MCDoubleBuffer* NewMCDoubleBuffer(size_t size)
{
	MCDoubleBuffer* instance = (MCDoubleBuffer*)mc_malloc(sizeof(MCDoubleBuffer)+size);
	instance->size = size;
	//
	instance->isa = nil;
	instance->need_bind_method = NO;
	instance->ref_count = 1;
}