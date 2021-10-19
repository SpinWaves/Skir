#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <Kernel/Memory/allocator.h>

new_allocator(__allocator, 1024 * 1024)

void* custom_malloc(size_t size);
void custom_free(void* ptr);

#endif // __MEMORY_MANAGER__
