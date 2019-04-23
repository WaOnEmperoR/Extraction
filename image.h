#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "matrix.h"

/**
 * Read an image from a PGM image file.
 * The client code will be responsible for calling @c Mat_Release.
 * @param fileName The name of the PGM image file.
 * @return Image matrix of type UCHAR.
 */
Mat* IO_ReadPGM(const char* fileName);

/**
 * Read an image from a PPM image file.
 * The client code will be responsible for calling @c Mat_Release.
 * @param fileName The name of the PPM image file.
 * @return Image matrix of type COLOR_PIXEL.
 */
Mat* IO_ReadPPM(const char* fileName);

/**
 * Write the given image matrix to a PGM image file.
 * @param fileName The name of the PGM image file.
 * @param mat The image matrix (of type UCHAR) to be written.
 */
void IO_WritePGM(const char* fileName, Mat* mat);

/**
 * Write the given image matrix to a PPM image file.
 * @param fileName The name of the PPM image file.
 * @param mat The image matrix (of type COLOR_PIXEL) to be written.
 */
void IO_WritePPM(const char* fileName, Mat* mat);

/**
 * @deprecated  Use @c IO_ReadPGM instead.
 *
 * Read an image from a PGM image file.
 * The client code will be responsible for calling @c Mat_Release.
 * @param fileName The name of the PGM image file.
 * @return Image matrix of type UCHAR.
 */
Mat ReadPGM(const char* fileName);

/**
 * @deprecated  Use @c IO_ReadPPM instead.
 *
 * Read an image from a PPM image file.
 * The client code will be responsible for calling @c Mat_Release.
 * @param fileName The name of the PPM image file.
 * @return Image matrix of type COLOR_PIXEL.
 */
Mat ReadPPM(const char* fileName);

/**
 * @deprecated  Use @c IO_WritePGM instead.
 *
 * Write the given image matrix to a PGM image file.
 * @param fileName The name of the PGM image file.
 * @param mat The image matrix (of type UCHAR) to be written.
 */
void WritePGM(const char* fileName, Mat* mat);

/**
 * @deprecated  Use @c IO_WritePPM instead.
 *
 * Write the given image matrix to a PPM image file.
 * @param fileName The name of the PPM image file.
 * @param mat The image matrix (of type COLOR_PIXEL) to be written.
 */
void WritePPM(const char* fileName, Mat* mat);

#endif // IMAGE_H_INCLUDED
