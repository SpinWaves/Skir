#include <Kernel/Memory/memory_manager.h>

void initMemManager()
{
    initAllocator(&__allocator, 4096 * 4096);
}

void* custom_malloc(size_t size)
{
    return memalloc(&__allocator, size);
}
void custom_free(void* ptr)
{
    memfree(&__allocator, ptr);
}

void shutdownMemManager()
{
    destroyAllocator(&__allocator);
}
