// Copyright (C) 2021 SpinWaves (https://github.com/SpinWaves)
// This file is a part of "Keep Running"
// For conditions of distribution and use, see the LICENSE
//
// Author : kbz_8

#include <Kernel/log.h>
#include <Utils/c_output.h>
#include <stdio.h>
#include <time.h>
#include <Kernel/Memory/memory.h>

void log_report(log_type type, const char* msg)
{
    char path[sizeof(LOG_DIR) + 48];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(path, "%s/session.txt", LOG_DIR, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    FILE* file = fopen(path, "w");
    if(!file)
    {
        printf("%sLog: unable to open file: %s%s\n", OUT_RED, path, OUT_DEF);
        return;
    }
    switch(type)
    {
        case MESSAGE: fprintf(file, "%d-%d-%d-%d:%d -- Message ---- ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); printf("%s%s%s\n", OUT_BLUE, msg, OUT_DEF); break;
        case WARNING: fprintf(file, "%d-%d-%d-%d:%d -- Warning ---- ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); printf("%s%s%s\n", OUT_MAGENTA, msg, OUT_DEF); break;
        case ERROR: fprintf(file, "%d-%d-%d-%d:%d -- Error ---- ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,  tm.tm_hour, tm.tm_min); printf("%s%s%s\n", OUT_RED, msg, OUT_DEF); break;
        case FATAL_ERROR: fprintf(file, "%d-%d-%d-%d:%d -- Fatal error ---- ",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min); printf("%s%s%s\n", OUT_RED, msg, OUT_DEF); break;

        default: break;
    }
    fprintf(file, "%s\n", msg);
    fclose(file);

    if(type == FATAL_ERROR)
    {
        shutdownMemManager();
        abort();
    }
}
