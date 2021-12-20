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
config_infos* exists(const char* key)
{
    config_infos* buffer = __config_manager;
    while(buffer != NULL)
    {
        if(buffer->key != NULL && key != NULL)
        {
            if(strcmp(buffer->key, key) == 0)
                return buffer;
        }
        buffer = buffer->next;
    }
    return NULL;
}
void openConfigFile(const char* path)
{
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
        log_report(FATAL_ERROR, "Couldn't open config file");

    char line[1024] = {0};
    config_infos* buffer = NULL;
    while(!feof(fp))
    {
        config_infos* inf = custom_malloc(sizeof(config_infos));
        inf->next = __config_manager;

        memset(line, 0, 1024);
        fgets(line, 1024, fp);
        if(line[0] == '#')
            continue;

        int len = strlen(line);
        char* pos = strchr(line, '=');
        if(pos == NULL)
            continue;

        int offset = 1;
        if(line[len - 1] == '\n')
            offset = 2;

        int key_len = (int)(pos - line);
        inf->key = custom_malloc(key_len);
        int val_len = (int)(line + len - offset - pos);
        inf->val = custom_malloc(val_len);

        memset(inf->key, 0, key_len);
        memset(inf->val, 0, val_len);
 
        if(line[key_len - 1] == ' ')
            strncpy(inf->key, line, key_len - 1);
        else
            strncpy(inf->key, line, key_len);

        if(pos[1] == ' ')
            strncpy(inf->val, pos + 2, val_len - 1);
        else
            strncpy(inf->val, pos + 1, val_len);
        
        if((buffer = exists(inf->key)) != NULL)
        {
            custom_free(buffer->val);
            buffer->val = inf->val;
            custom_free(inf->key);
            custom_free(inf);
        }
        else
            __config_manager = inf;
    }
    fclose(fp);
}
const char* get_config_value(const char* key)
{
    config_infos* buffer = exists(key);
    if(buffer != NULL)
        return buffer->val;
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
