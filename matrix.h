#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "typedef.h"

/* Define alias. */
typedef struct Mat Mat;

/**
 * This structure represents a matrix (2-dimensional arrangement of data).
 */
struct Mat
{
    int rows; /**< Number of rows. */
    int cols; /**< Number of columns. */
    DataType type; /**< Matrix element's data type. */

    /**
     * 2-dimensional arrays to store the matrix data.
     * Which pointer to be used (u, i, f, d, cp) depends on matrix data type.
     */
    union
    {
        uchar** u; /**< Treat data as UCHAR. */
        int** i; /**< Treat data as INT. */
        float** f; /**< Treat data as FLOAT. */
        double** d; /**< Treat data as DOUBLE. */
        ColorPixel** cp; /**< Treat data as COLOR_PIXEL. */
    } data;
};

/**
 * Initialize a matrix with the given size and data type.
 * The client code is responsible for calling @c Mat_Release.
 * @param rows The number of rows of the matrix.
 * @param cols The number of columns of the matrix.
 * @param type The data type of the matrix elements.
 * @return The pointer to the initialized matrix.
 */
Mat* Mat_Init(int rows, int cols, DataType type);

/**
 * Perform a deep matrix clone.
 * The client code is responsible for calling @c Mat_Release.
 * @param mat The pointer to the matrix to be cloned.
 * @return The pointer to the cloned matrix.
 */
Mat* Mat_Clone(Mat* mat);

/**
 * Release the given matrix.
 * All memory spaces associated with the matrix will be deallocated.
 * @param mat The pointer to the matrix to be released.
 */
void Mat_Release(Mat* mat);

/**
 * Convert the given grayscale matrix (UCHAR) to a color matrix (COLOR_PIXEL).
 * The client code is responsible for calling @c Mat_Release.
 * @param mat The pointer to the matrix to be converted.
 * @return The pointer to the corresponding color matrix.
 */
Mat* Mat_ConvertToColor(Mat* mat);

/**
 * Convert the given FLOAT matrix to a UCHAR matrix.
 * The client code is responsible for calling @c Mat_Release
 * @param mat The pointer to the matrix to be converted.
 * @return The pointer to the corresponsing UCHAR matrix.
 */
Mat* Mat_FloatToChar(Mat* mat);

/**
 * Invert each pixel the given UCHAR matrix (formula: value xor 255).
 * If @c dst parameter is NULL, a new matrix will be initialized to store the
 * inversion result. Otherwise, the result will be stored in @c dst.
 * The client code is responsible for calling @c Mat_Release.
 * @param src The matrix to be inverted.
 * @param dst The matrix to store the inversion result.
 * @result Pointer to the newly initialized matrix or @c dst.
 */
Mat* Mat_Invert(Mat* src, Mat* dst);

/**
 * @deprecated  Use @c Mat_Init instead.
 *
 * Initialize a matrix with the given size and data type.
 * The client code is responsible for calling @c Mat_Release.
 * @param rows The number of rows of the matrix.
 * @param cols The number of columns of the matrix.
 * @param type The data type of the matrix elements.
 * @return The initialized matrix.
 */
Mat MatInit(int rows, int cols, DataType type);

/**
 * @deprecated Use @c Mat_Clone instead.
 *
 * Perform a deep matrix clone.
 * The client code is responsible for calling @c Mat_Release.
 * @param mat The pointer to the matrix to be cloned.
 * @return The cloned matrix.
 */
Mat MatClone(Mat* mat);

/**
 * @deprecated Use @c Mat_Release instead.
 *
 * Release the given matrix.
 * All memory spaces associated with the matrix will be deallocated.
 * @param mat The pointer to the matrix to be released.
 */
void MatRelease(Mat* mat);

/**
 * @deprecated Use @c Mat_ConvertToColor instead.
 *
 * Convert the given grayscale matrix (UCHAR) to a color matrix (COLOR_PIXEL).
 * The client code is responsible for calling @c Mat_Release.
 * @param src The pointer to the matrix to be converted.
 * @param[out] dst The pointer to the matrix in which the converted data will be stored.
 */
void ConvertToColorMat(Mat* src, Mat* dst);

#endif // MATRIX_H_INCLUDED
