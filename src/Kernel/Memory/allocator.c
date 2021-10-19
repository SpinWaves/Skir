#include <Kernel/Memory/allocator.h>
#include <Utils/utils.h>
#include <stdlib.h>
#include <stdio.h>

void* memalloc(Allocator* allocator, size_t size)
{
    if(allocator->heap == NULL)
        return;
    if(!canHold(allocator, size))
        return;
    void* ptr = NULL;
    if(allocator->free_flags != NULL)
    {
        allocator_flag* flag = allocator->free_flags;
        if(flag->size >= size)
        {
            ptr = (void*)(allocator->heap + flag->offset + sizeof(flag));

            // Removing flag from free_flags chain
            allocator->free_flags = flag->next;

            // Inserting flag in used_flags chain
            flag->next = allocator->used_flags;
            allocator->used_flags = flag;
            return ptr;
        }
        allocator_flag* flag_move = allocator->free_flags;
        while(flag != NULL)
        {
            if(flag->next != NULL)
            {
                if(flag->next->size >= size)
                {
                    flag_move = flag->next;
                    ptr = (void*)(allocator->heap + flag_move->offset + sizeof(flag_move));

                    // Removing flag from free_flags chain
                    flag->next = flag_move->next;

                    // Inserting flag in used_flags chain
                    flag_move->next = allocator->used_flags;
                    allocator->used_flags = flag_move;
                    return ptr;
                }
            }
            flag = flag->next;
        }
    }
    allocator_flag* flag = (allocator_flag*)(allocator->heap + allocator->mem_used);
    flag->size = size;
    flag->offset = allocator->mem_used + sizeof(allocator_flag);
    flag->next = allocator->used_flags;
    allocator->used_flags = flag;
    ptr = (void*)(allocator->heap + allocator->mem_used + sizeof(allocator_flag));
    allocator->mem_used += sizeof(allocator_flag) + size;

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

    unsigned int offset = (char*)ptr - allocator->heap;
    allocator_flag* flag = allocator->used_flags;
    if(flag->offset == offset)
    {
        // Removing flag from used_flags chain
        allocator->used_flags = flag->next;

        // Inserting flag in free_flags chain
        flag->next = allocator->free_flags;
        allocator->free_flags = flag;
        ptr = NULL;
        return;
    }
    allocator_flag* flag_move = allocator->used_flags;
    while(flag != NULL)
    {
        if(flag->next != NULL && flag->next->offset == offset)
        {
            flag_move = flag->next;
            // Removing flag from used_flags chain
            flag->next = flag_move->next;

            // Inserting flag in free_flags chain
            flag_move->next = allocator->free_flags;
            allocator->free_flags = flag_move;
            ptr = NULL;
            return;
        }
        flag = flag->next;
    }

    ptr = NULL;
}
