#include "log.h"
#include <stdio.h>
#include <stdarg.h>

void log_msg(FILE *logFile, const char *fmt, ...) {
    if (!logFile) return;
    va_list args;
    va_start(args, fmt);
    vfprintf(logFile, fmt, args);
    va_end(args);
}