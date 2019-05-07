#ifndef MINUTIAE_H_INCLUDED
#define MINUTIAE_H_INCLUDED

#include "typedef.h"

/**
 * Many fingerprint features are stored in a grid whose elements denote a
 * particular region in a fingerprint image. The following is the width and
 * height of each block in the grid.
 */
#define BLOCK_WIDTH 13
#define BLOCK_HEIGHT 13

/* Define alias. */
typedef struct Minutiae Minutiae;

/**
 * This structure describes a minutiae in a fingerprint.
 */
struct Minutiae {
    int y; /**< The y-coordinate of the minutiae. */
    int x; /**< The x-coordinate of the minutiae. */
    float direction; /**< The direction of the minutiae. */
    int quality;
    MinutiaeType type;
    int CN; /**< Crossing number. */
};

#endif // MINUTIAE_H_INCLUDED

int32_t swap_int32( int32_t val );
int16_t swap_int16( int16_t val );
