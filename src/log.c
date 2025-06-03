// log.c: Logging utility for DIA.
// Provides a simple function to write formatted log messages to a file.

#include "log.h"
#include <stdio.h>
#include <stdarg.h>

// Writes a formatted message to the log file (if logging is enabled)
void log_msg(FILE *logFile, const char *fmt, ...) {
    if (!logFile) return; // If no log file, do nothing
    va_list args;
    va_start(args, fmt);
    vfprintf(logFile, fmt, args);
    va_end(args);
}