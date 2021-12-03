// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#ifndef __ALLOCATOR__
#define __ALLOCATOR__

#include <stddef.h>
#include <stdbool.h>

/**
 * This allocator is based on Akel's JamAllocator logic (https://github.com/SpinWaves/Akel).
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

void initAllocator(Allocator* allocator, size_t size);
void* memalloc(Allocator* allocator, size_t size);
bool canHold(Allocator* allocator, size_t size);
bool contains(Allocator* allocator, void* ptr);
void memfree(Allocator* allocator, void* ptr);
void destroyAllocator(Allocator* allocator);

#endif // __ALLOCATOR__
