#ifndef __ALLOCATOR__
#define __ALLOCATOR__

typedef struct
{
    void* heap;
} Allocator;

void initAllocator(Allocator* allocator);
void shutdownAllocator(Allocator* allocator);

#endif // __ALLOCATOR__
