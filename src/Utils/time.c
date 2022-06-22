// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "time.h"
#include <time.h>

__time getCurrentTime()
{
	time_t rawtime;
	time(&rawtime);
	struct tm* now = localtime(&rawtime);

	__time t;

	t.sec = now->tm_sec;
	t.min = now->tm_min;
	t.hour = now->tm_hour;
	t.day = now->tm_mday;
	t.month = now->tm_mon + 1;
	t.year = now->tm_year + 1900;

	return t;
}

long get_nanos()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}
