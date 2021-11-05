#include <Kernel/Memory/memory_manager.h>

static Allocator* __allocator = NULL;

void* custom_malloc(size_t size)
{
    return memalloc(__allocator, size);
}
void custom_free(void* ptr)
{
    memfree(__allocator, ptr);
}

void initMemManager()
{
    __allocator = malloc(sizeof(Allocator));
    initAllocator(__allocator, 1024);
}
void shutdownMemManager()
{
    destroyAllocator(__allocator);
    free(__allocator);
}
