#include "MCBuffer.h"

MCCharBuffer* NewMCCharBuffer(size_t size)
{
	MCCharBuffer* instance = (MCCharBuffer*)malloc(sizeof(MCCharBuffer)+size);
	instance->size = size;
    memset(instance->data, 0, size);
	return instance;
}

MCCharBuffer* CopyToCharBuffer(MCCharBuffer* buff, char* src)
{
    strcpy(buff->data, src);
	return buff;
}

MCIntBuffer* NewMCIntBuffer(size_t size)
{
	MCIntBuffer* instance = (MCIntBuffer*)malloc(sizeof(MCIntBuffer)+size);
	instance->size = size;
	return instance;
}

MCUnsignedBuffer* NewMCUnsignedBuffer(size_t size)
{
	MCUnsignedBuffer* instance = (MCUnsignedBuffer*)malloc(sizeof(MCUnsignedBuffer)+size);
	instance->size = size;
	return instance;
}

MCLongBuffer* NewMCLongBuffer(size_t size)
{
	MCLongBuffer* instance = (MCLongBuffer*)malloc(sizeof(MCLongBuffer)+size);
	instance->size = size;
	return instance;
}

MCDoubleBuffer* NewMCDoubleBuffer(size_t size)
{
	MCDoubleBuffer* instance = (MCDoubleBuffer*)malloc(sizeof(MCDoubleBuffer)+size);
	instance->size = size;
	return instance;
}

void ReleaseMCBuffer(void* buffer)
{
	if (buffer)
		free(buffer);
}
