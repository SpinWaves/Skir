#include <Kernel/Memory/memory_manager.h>

void* custom_malloc(size_t size)
{
    return memalloc(&__allocator, size);
}
void custom_free(void* ptr)
{
    memfree(&__allocator, ptr);
}
