#include "typedef.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

size_t DataTypeSize(DataType t)
{
  size_t size;

  switch (t) {
    case UCHAR: size = sizeof(uchar); break;
    case INT: size = sizeof(int); break;
    case FLOAT: size = sizeof(float); break;
    case DOUBLE: size = sizeof(double); break;
    case COLOR_PIXEL: size = sizeof(ColorPixel); break;
    default:
      ABORT("DataType %d not recognized\n", t);
  }

  return size;
}
