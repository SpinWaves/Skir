#include <Kernel/Memory/memory_manager.h>

static Allocator __allocator;

void* custom_malloc(size_t size)
{
    return memalloc(&__allocator, size);
}
void custom_free(void* ptr)
{
    memfree(&__allocator, ptr);
}

void initMemManager()
{
    initAllocator(&__allocator, 1024);
}
void shutdownMemManager()
{
    destroyAllocator(&__allocator);
}
