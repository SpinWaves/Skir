#ifndef __LOG__
#define __LOG__

enum log_type
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
};

void log_report(log_type type, const char* msg);

#endif // __LOG__
