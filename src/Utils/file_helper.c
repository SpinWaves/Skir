// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <stdbool.h>
#include <sys/stat.h>

bool file_exists(char* filename)
{
	struct stat buffer;
	return stat(filename, &buffer) == 0;
}
