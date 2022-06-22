// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <Kernel/Memory/allocator.h>

void initMemManager();
void* memAlloc(size_t size);
void memFree(void* ptr);
void shutdownMemManager();

#endif // __MEMORY_MANAGER__
