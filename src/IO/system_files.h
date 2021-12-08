// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __SYSTEM_FILES__
#define __SYSTEM_FILES__

typedef struct config_infos
{
    char key[0];
    char val[960];
    struct config_infos* next;
} config_infos;

void initConfigInfoManager();
void openConfigFile(const char* path);
config_infos* get_info(const char* key);
void shutdownConfigInfoManager();

#endif // __SYSTEM_FILES__
