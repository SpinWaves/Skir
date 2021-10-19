#ifndef __ALLOCATOR__
#define __ALLOCATOR__

#include <stddef.h>
#include <stdbool.h>

/**
 * This allocator is based on Akel JamAllocator logic (https://github.com/SpinWaves/Akel).
 */

typedef struct allocator_flag
{
    unsigned int size;
    unsigned int offset;

    // Linked list of flags
    struct allocator_flag* next;
} allocator_flag;

typedef struct
{
    const char* heap;
    const char* heap_end;
    size_t heap_size;
    size_t mem_used;

    allocator_flag* used_flags;
    allocator_flag* free_flags;
} Allocator;


void* memalloc(Allocator* allocator, size_t size);
bool canHold(Allocator* allocator, size_t size);
bool contains(Allocator* allocator, void* ptr);
void memfree(Allocator* allocator, void* ptr);

#define new_allocator(name, size)   static char pool_##name[size] = {0}; \
                                    static Allocator name = {pool_##name, (void*)(pool_##name + size), size, 0, NULL, NULL};
                                    

#endif // __ALLOCATOR__
