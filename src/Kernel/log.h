// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __LOG__
#define __LOG__

#include <stdarg.h>

typedef enum
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
} log_type;

void log_report(log_type type, const char* msg, ...);

#endif // __LOG__
