#include <Kernel/Memory/allocator.h>
#include <Utils/c_output.h>
#include <stdlib.h>
#include <stdio.h>

void initAllocator(Allocator* allocator, size_t size)
{
    if(allocator->heap != NULL)
        return;
    
    allocator->heap = malloc(size);
    // TODO : log error
    allocator->heap_size = size;
    allocator->mem_used = 0;
    allocator->heap_end = (void*)((char*)allocator->heap + size);

    allocator->used_flags = NULL;
    allocator->free_flags = NULL;
}

void* memalloc(Allocator* allocator, size_t size)
{
    // TODO : log error heap == NULL
    // TODO : log error cannot hold
    void* ptr = NULL;
    if(allocator->free_flags != NULL)
    {
        allocator_flag* flag = allocator->free_flags;
        while(flag != NULL)
        {
            if(flag->size >= size)
            {
                ptr = (void*)((char*)allocator->heap + flag->offset + sizeof(flag));
                
                // Removing flag from free_flags chain
                if(flag->next != NULL)
                    flag->next->prev = flag->prev;
                if(flag != allocator->free_flags)
                    flag->prev->next = flag->next;

                // Inserting flag in used_flags chain
                flag->next = allocator->used_flags;
                flag->prev = NULL;
                if(allocator->used_flags != NULL)
                    allocator->used_flags->prev = flag;
                allocator->used_flags = flag;
                break;
            }
            flag = flag->next;
        }
    }
    if(ptr == NULL)
    {
        allocator_flag* flag = (allocator_flag*)((void*)((char*)allocator->heap + allocator->mem_used));
        flag->size = size;
        flag->offset = allocator->mem_used + sizeof(allocator_flag);
        flag->prev = NULL;
        flag->next = allocator->used_flags;
        if(allocator->used_flags != NULL)
            allocator->used_flags->prev = flag;
        allocator->used_flags = flag;
        ptr = (void*)((char*)allocator->heap + allocator->mem_used + sizeof(allocator_flag));
        allocator->mem_used += sizeof(allocator_flag) + size;
    }
    printf("size: %d / %d  %p\n", size, allocator->mem_used, ptr);
    fflush( stdout );

    return ptr;
}
bool canHold(Allocator* allocator, size_t size)
{
    return allocator->heap_size - allocator->mem_used >= size;
}
bool contains(Allocator* allocator, void* ptr)
{
    return ptr > allocator->heap && ptr < allocator->heap_end;
}
void memfree(Allocator* allocator, void* ptr)
{
    if(!contains(allocator, ptr))
        return;
    
    if(allocator->used_flags == NULL)
        return;

    unsigned int offset = (char*)ptr - (char*)allocator->heap;
    allocator_flag* flag = allocator->used_flags;
    while(flag != NULL)
    {
        if(flag->offset == offset)
        {
            // Removing flag from used_flags chain
            if(flag != allocator->used_flags)
                flag->prev->next = flag->next;
            if(flag->next != NULL)
                flag->next->prev = flag->prev;

            // Inserting flag in free_flags chain
            flag->next = allocator->free_flags;
            flag->prev = NULL;
            if(allocator->free_flags != NULL)
                allocator->free_flags->prev = flag;
            allocator->free_flags = flag;
            break;
        }
        flag = flag->next;
    }

    ptr = NULL;
}

void destroyAllocator(Allocator* allocator)
{
    if(allocator->heap == NULL)
        return;

    if(allocator->used_flags != NULL)
        printf("%sAllocator: leak has been detected, freeing it...%s", OUT_MAGENTA, OUT_DEF);
    
    free(allocator->heap);
    free(allocator->used_flags);
    free(allocator->free_flags);

    allocator->heap = NULL;
    allocator->used_flags = NULL;
    allocator->free_flags = NULL;
}
