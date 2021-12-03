// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#ifndef __MEMORY_MANAGER__
#define __MEMORY_MANAGER__

#include <Kernel/Memory/allocator.h>

void initMemManager();
void* custom_malloc(size_t size);
void custom_free(void* ptr);
void shutdownMemManager();

#endif // __MEMORY_MANAGER__
