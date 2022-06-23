// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include "maths.h"
#include <limits.h>

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

float fsqrt(float x)
{
	unsigned int i = *(unsigned int*)&x;
	i += 127 << 23;
	i >>= 1;
	return *(float*)&i;
}
