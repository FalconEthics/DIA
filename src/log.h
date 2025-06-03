#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

void log_msg(FILE *logFile, const char *fmt, ...);

#endif // LOG_H