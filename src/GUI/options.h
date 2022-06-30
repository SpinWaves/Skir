// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __OPTIONS__
#define __OPTIONS__

#include <Kernel/kernel.h>

void initOptionsPage(SDL_Renderer* renderer, int width, int height);
void callOptionsPage();
void hangUpOptionsPage();
bool isOptionsPageCalled();
void updateOptionsPage(Inputs *in);
void renderOptionsPage();
void shutdownOptionsPage();

#endif // __OPTIONS__
