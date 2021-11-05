#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <Kernel/Memory/allocator.h>

void initMemManager();
void* custom_malloc(size_t size);
void custom_free(void* ptr);
void shutdownMemManager();

#endif // __MEMORY_MANAGER__
