// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/Memory/memory_manager.h>

static Allocator __allocator;

void* memAlloc(size_t size)
{
    return memalloc(&__allocator, size);
}
void memFree(void* ptr)
{
    memfree(&__allocator, ptr);
}

void initMemManager()
{
    initAllocator(&__allocator, 4096 * 4096);
}
void shutdownMemManager()
{
    destroyAllocator(&__allocator);
}
