#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* Display error message (same arguments as printf) and abort the program. */
#define ABORT(...) { \
    fprintf(stderr, "Program terminated <%s:%d>: ", __FILE__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
    exit(1); }

enum LogLevel {
  NO_LOG = 0,
  ERROR = 1,
  WARN = 2,
  INFO = 3,
  DEBUG = 4
};

typedef enum LogLevel LogLevel;

/**
 * Set the maximum log level to be displayed (default to DEBUG).
 * @param lvl The maximum log level.
 */
void Log_SetLevel(LogLevel lvl);

/**
 * Print a log string.
 * @param lvl The importance level of the log.
 * @param format String that contains the text to be written.
 * @param ... Value to be interpolated to the format string.
 */
void Log(LogLevel lvl, const char* format, ...);

#endif // LOG_H_INCLUDED
