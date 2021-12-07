// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <IO/system_files.h>
#include <Kernel/kernel.h>

#include <stdio.h>
#include <string.h>

char** get_config_file(const char* path)
{
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
        log_report(FATAL_ERROR, "Couldn't open config file");

    char** get = custom_malloc(1024);
    
    char line[1024] = { 0 };
    while(!feof(fp))
    {
        memset(line, 0, 1024);
        fgets(line, 1024, fp);
        if(line[0] == '#')
            continue;

        int len = strlen(line);
        char *pos = strchr(line, '=');
        if(pos == NULL)
            continue;

        char key[64] = { 0 };
        char val[64] = { 0 };

        int offset = 1;
        if(line[len - 1] == '\n')
            offset = 2;

        strncpy(key, line, pos - line);
        if(pos[1] == ' ')
            strncpy(val, pos + 2, line + len - offset - pos);
        else
            strncpy(val, pos + 1, line + len - offset - pos);
        if(key[strlen(key) - 1] == ' ')
            key[strlen(key) - 1] = 0;

        printf("%s -> %s\n", key, val);
    }
    fclose(fp);
}
