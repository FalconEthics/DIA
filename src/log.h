// log.h: Header for logging utilities in DIA.
// Declares the interface for writing log messages to a file.

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

// Writes a formatted message to the log file (if enabled)
void log_msg(FILE *logFile, const char *fmt, ...);

#endif // LOG_H