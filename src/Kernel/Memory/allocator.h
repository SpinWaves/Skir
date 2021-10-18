#ifndef __ALLOCATOR__
#define __ALLOCATOR__

#include <stddef.h>
#include <stdbool.h>

/**
 * This allocator is based on Akel JamAllocator (https://github.com/SpinWaves/Akel).
 * The only differences are in the transition from C++ to C.
 */

typedef struct
{
    size_t size;
    unsigned int offset;
} allocator_flag;

typedef struct
{
    void* heap;
    void* heap_end;
    size_t heap_size;
    size_t mem_used;

    // Dynamic arrays
    allocator_flag* used_flags;
    allocator_flag* free_flags;
} Allocator;

void initAllocator(Allocator* allocator, size_t size);

void* alloc(Allocator* allocator, size_t size);
bool canHold(Allocator* allocator, size_t size);
bool contains(Allocator* allocator, void* ptr);
void free(Allocator* allocator, void* ptr);

void shutdownAllocator(Allocator* allocator);

#endif // __ALLOCATOR__
