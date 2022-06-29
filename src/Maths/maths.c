// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "maths.h"
#include <limits.h>
#include <stdarg.h>

int m_abs(int a)
{
	int mask = (a >> (sizeof(int) * CHAR_BIT - 1));
	return (a + mask) ^ mask;
}

float m_fabs(float a)
{
	long i = *(long*)&a;
	i &= ~(1u << 31);
	return *(float*)&i;
}

int randint(int a, int b)
{
	return rand() % (b - a) + a;
}

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2)
{
    return (num1 > num2) ? num2 : num1;
}

int max_va(int number, ...)
{
	int max = 0;
	int step = 0;
	va_list ap;

	va_start(ap, number);
	for(int i = 0; i < number; i++)
	{
		if((step = va_arg(ap, int)) > max)
			max = step;
	}
	va_end(ap);

	return max;
}

int min_va(int number, ...)
{
	int min = 0;
	int step = 0;
	va_list ap;

	va_start(ap, number);
	for(int i = 0; i < number; i++)
	{
		if((step = va_arg(ap, int)) < min)
			min = step;
	}
	va_end(ap);

	return min;
}

float fsqrt(float x)
{
	unsigned int i = *(unsigned int*)&x;
	i += 127 << 23;
	i >>= 1;
	return *(float*)&i;
}
