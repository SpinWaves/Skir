// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/Memory/memory_manager.h>

static Allocator __allocator;

void* custom_malloc(size_t size)
{
    return memalloc(&__allocator, size);
}
void custom_free(void* ptr)
{
    memfree(&__allocator, ptr);
}

void initMemManager()
{
    initAllocator(&__allocator, 20000000);
}
void shutdownMemManager()
{
    destroyAllocator(&__allocator);
}
