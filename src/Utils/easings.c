// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#include <Utils/easings.h>

inline double easeInBack(float x)
{
    return 2.70158 * x * x * x - 1.70158 * x * x;
}
