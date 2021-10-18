#include <Kernel/Memory/allocator.h>

void initAllocator(Allocator* allocator, size_t size)
{
    if(allocator->heap != NULL)
        return;
    
    allocator->heap = malloc(size);
    // TODO : log error
    allocator->heap_size = size;
    allocator->mem_used = 0;
    allocator->heap_end = (void*)((char*)allocator->heap + size);

    allocator->used_flags = (allocator_flag*)calloc(255, sizeof(allocator_flag*));
    allocator->free_flags = (allocator_flag*)calloc(255, sizeof(allocator_flag*));
}

void* alloc(Allocator* allocator, size_t size)
{
    // TODO : log error heap == NULL
    // TODO : log error cannot hold
    void* ptr = NULL;
    if(allocator->free_flags[0] != NULL)
    {

    }
    if(ptr == NULL)
    {
        allocator_flag* flag = (allocator_flag*)((void*)((char*)allocator->heap + allocator->mem_used));
        flag->size = size;
        flag->offset = allocator->mem_used;
    }
}
bool canHold(Allocator* allocator, size_t size)
{
    return allocator->heap_size - allocator->mem_used >= size ? true : false:
}
bool contains(Allocator* allocator, void* ptr)
{
    return ptr > allocator->heap && ptr < allocator->heap_end ? true : false:
}
void free(Allocator* allocator, void* ptr)
{

}

void shutdownAllocator(Allocator* allocator)
{
    if(allocator->heap == NULL)
        return;

    // TODO : log warning if leaks
    
    free(allocator->heap);
    free(allocator->used_flags);
    free(allocator->free_flags);

    allocator->heap = NULL;
    allocator->used_flags = NULL;
    allocator->free_flags = NULL;
}
