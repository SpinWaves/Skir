// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __ABOUT__
#define __ABOUT__

#include <Kernel/kernel.h>

void initAboutPage(SDL_Renderer* renderer, int width, int height);
void callAboutPage();
void hangUpAboutPage();
bool isAboutPageCalled();
void updateAboutPage(Inputs *in);
void renderAboutPage();
void shutdownAboutPage();

#endif // __ABOUT__
