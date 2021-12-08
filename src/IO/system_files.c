// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <IO/system_files.h>
#include <Kernel/kernel.h>

#include <stdio.h>
#include <string.h>

static config_infos* __config_manager = NULL;

void initConfigInfoManager()
{
    __config_manager = NULL;
}
void openConfigFile(const char* path)
{
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
        log_report(FATAL_ERROR, "Couldn't open config file");

    char line[1024] = {0};
    while(!feof(fp))
    {
        config_infos* inf = custom_malloc(sizeof(config_infos));
        inf->next = __config_manager;
        __config_manager = inf;

        memset(line, 0, 1024);
        fgets(line, 1024, fp);
        if(line[0] == '#')
            continue;

        int len = strlen(line);
        char *pos = strchr(line, '=');
        if(pos == NULL)
            continue;

        int offset = 1;
        if(line[len - 1] == '\n')
            offset = 2;

        int key_len = (int)(pos - line);
        inf->key = custom_malloc(key_len);
        int val_len = (int)(line + len - offset - pos);
        inf->val = custom_malloc(val_len);
 
        memset(inf->key, 0, key_len - 1);
        memset(inf->val, 0, val_len - 1);

        strncpy(inf->key, line, pos - line);
        if(inf->key[strlen(inf->key) - 1] == ' ')
            inf->key[strlen(inf->key) - 1] = 0;
        if(pos[1] == ' ')
            strncpy(inf->val, pos + 2, line + len - offset - pos);
        else
            strncpy(inf->val, pos + 1, line + len - offset - pos);

        printf("%s -> %s\n", inf->key, inf->val); // for tests
    }
    fclose(fp);
}
char* get_info(const char* key)
{
    config_infos* buffer = __config_manager;
    while(buffer != NULL)
    {
        if(strcmp(buffer->key, key) == 0)
            return buffer->val;
    }
    return NULL;
}
void shutdownConfigInfoManager()
{
    config_infos* buffer = __config_manager;
    config_infos* double_buffer = NULL;
    while(buffer != NULL)
    {
        double_buffer = buffer->next;
        custom_free(buffer->key);
        custom_free(buffer->val);
        custom_free(buffer);
        buffer = double_buffer;
    }
}
