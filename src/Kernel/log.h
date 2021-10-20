#ifndef __LOG__
#define __LOG__

typedef enum
{
    MESSAGE,
    WARNING,
    ERROR,
    FATAL_ERROR
} log_type;

void log_report(log_type type, const char* msg);

#endif // __LOG__
