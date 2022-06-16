// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#ifndef __SYSTEM_FILES__
#define __SYSTEM_FILES__

typedef struct config_infos
{
    char* key;
    char* val;
    struct config_infos* next;
} config_infos;

void initConfigInfoManager();
void openConfigFile(const char* path);
const char* get_config_value(const char* key);
void shutdownConfigInfoManager();

#endif // __SYSTEM_FILES__
