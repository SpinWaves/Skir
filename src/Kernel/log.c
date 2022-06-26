// Copyright (C) 2021 - 2022 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8 (https://solo.to/kbz_8)

#include <Kernel/log.h>
#include <Utils/c_output.h>
#include <stdio.h>
#include <time.h>
#include <Kernel/Memory/memory.h>
#include <Utils/file_helper.h>

void init_logs()
{
    if(file_exists(LOG_DIR"/session.log"))
        remove(LOG_DIR"/session.log");
}

void log_report(log_type type, const char* msg, ...)
{
    char buffer[strlen(msg) + 1024];
    va_list args;
    va_start(args, msg);
    vsprintf(buffer, msg, args);
    va_end(args);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    FILE* file = fopen(LOG_DIR"/session.log", "a");

    if(!file)
    {
        printf("%sLog: unable to open file: %s%s\n", OUT_RED, LOG_DIR"/session.log", OUT_DEF);
        return;
    }

    switch(type)
    {
        case MESSAGE: fprintf(file, "%d-%d-%d-%d:%d -- Message ---- ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); printf("%s[Log Message] %s%s\n", OUT_BLUE, buffer, OUT_DEF); break;
        case WARNING: fprintf(file, "%d-%d-%d-%d:%d -- Warning ---- ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); printf("%s[Log Warning] %s%s\n", OUT_MAGENTA, buffer, OUT_DEF); break;
        case ERROR: fprintf(file, "%d-%d-%d-%d:%d -- Error ---- ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,  tm.tm_hour, tm.tm_min); printf("%s[Log Error] %s%s\n", OUT_RED, buffer, OUT_DEF); break;
        case FATAL_ERROR: fprintf(file, "%d-%d-%d-%d:%d -- Fatal error ---- ",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); printf("%s[Log Fatal Error] %s%s\n", OUT_RED, buffer, OUT_DEF); break;

        default: break;
    }
    fprintf(file, "%s\n", buffer);
    fclose(file);

    if(type == FATAL_ERROR)
    {
        shutdownMemManager();
        exit(-1);
    }
}
