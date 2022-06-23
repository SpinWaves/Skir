// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __MATHS__
#define __MATHS__

#include <math.h>

int m_abs(int a);
float m_fabs(float a);
int randint(int a, int b);

inline int max(int num1, int num2);
inline int min(int num1, int num2);

float fsqrt(float x);

#define DIV_BY_2(x) (x >> 1)

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#endif // __MATHS__
