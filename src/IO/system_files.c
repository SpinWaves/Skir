// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Skir"
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

extern Text_chain* head;
extern Application app;

void openConfigFile(const char* path)
{
    FILE* fp = fopen(path, "r");
    if(fp == NULL)
        log_report(FATAL_ERROR, "Couldn't open config file");

    char line[1024] = { 0 };
    config_infos* buffer = NULL;
    while(!feof(fp))
    {
        config_infos* inf = memAlloc(sizeof(config_infos));
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

        char* newline = strstr(line, "\\n");
        while(newline != NULL)
        {
            newline[0] = ' ';
            newline[1] = '\n';
            newline = strstr(newline + 2, "\\n");
        }

        int key_len = (int)(pos - line);
        inf->key = memAlloc(key_len);
        int val_len = (int)(line + len - offset - pos);
        inf->val = memAlloc(val_len);

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
            printf("%s - %s\n", buffer->val, inf->val);
            memFree(buffer->val);
            buffer->val = inf->val;
            memFree(inf->key);
            memFree(inf);
        }
        else
            __config_manager = inf;
    }
    fclose(fp);

    Text_chain* text_link = head;
    while(text_link != NULL)
    {
        if(text_link->text->key != NULL)
            updateText(text_link->text, app.renderer, get_config_value(text_link->text->key));
        text_link = text_link->next;
    }
}

const char* get_config_value(const char* key)
{
    config_infos* buffer = exists(key);
    return buffer != NULL ? buffer->val : "error";
}

void shutdownConfigInfoManager()
{
    config_infos* buffer = __config_manager;
    config_infos* double_buffer = NULL;
    while(buffer != NULL)
    {
        double_buffer = buffer->next;
        memFree(buffer->key);
        memFree(buffer->val);
        memFree(buffer);
        buffer = double_buffer;
    }
}
