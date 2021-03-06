#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED

#include <stdlib.h>

/* Data type alias. */
typedef unsigned char uchar;
typedef struct ColorPixel ColorPixel;
typedef struct Point Point;

/**
 * This structure represents a colored pixel.
 */
struct ColorPixel
{
    uchar r; /**< Red channel. */
    uchar g; /**< Green channel. */
    uchar b; /**< Blue channel. */
};

/**
 * This structure represents a point's coordinate.
 */
struct Point
{
    int x;
    int y;
};

/**
 * Enumeration of the most common data types.
 */
typedef enum
{
    UCHAR, INT, FLOAT, DOUBLE, COLOR_PIXEL
} DataType;

typedef enum
{
    BIFURCATION, RIDGE_ENDING, OTHER
}MinutiaeType;

/**
 * Get the size of the given data type.
 * @param The data type code.
 * @return The size of the corresponding data type.
 */
size_t DataTypeSize(DataType t);

/**
 * Get the size of the given minutiae type.
 * @param The minutiae type code.
 * @return The size of the corresponding minutiae type.
 */
size_t MinutiaeTypeSize(MinutiaeType t);

#endif // TYPEDEF_H_INCLUDED
