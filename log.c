
#include "log.h"
#include <stdarg.h>

LogLevel maxLvl = INFO;

void Log_SetLevel(LogLevel lvl)
{
  maxLvl = lvl;
}

void Log(LogLevel lvl, const char * format, ...)
{
  if (lvl > maxLvl) return;

  va_list args;
  va_start(args, format);

  vfprintf(stderr, format, args);

  va_end(args);
}
