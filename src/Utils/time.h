// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __UTILS_TIME__
#define __UTILS_TIME__

typedef struct
{
	int sec;   // 0-60
	int min;   // 0-59
	int hour;  // 0-23
	int day;   // 1-30/31
	int month; // 1-12
	int year;
} __time;

__time getCurrentTime();
long get_nanos();

#endif // __UTILS_TIME__
