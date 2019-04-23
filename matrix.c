
#include "matrix.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

Mat* Mat_Init(int rows, int cols, DataType type)
{
  assert(rows > 0 && cols > 0);

  Mat* mat;
  int rowBytes, i;

  /* Allocate memory spaces for matrix header. */
  mat = malloc(sizeof(Mat));
  mat->rows = rows;
  mat->cols = cols;
  mat->type = type;

  /* Allocate memory spaces to store the actual matrix data. */
  mat->data.u = malloc(mat->rows * sizeof(void*));

  rowBytes = cols * DataTypeSize(type); /* Bytes per row. */
  for (i = 0; i < rows; i++) {
    mat->data.u[i] = malloc(rowBytes); /* Allocate per-row spaces. */
    memset(mat->data.u[i], 0, rowBytes); /* Initialize to 0. */
  }

  return mat;
}

Mat* Mat_Clone(Mat* mat)
{
  assert(mat->rows > 0 && mat->cols > 0);

  Mat* newMat;
  int rowBytes, i;

  /* Allocate memory spaces for matrix header. */
  newMat = malloc(sizeof(Mat));
  newMat->rows = mat->rows;
  newMat->cols = mat->cols;
  newMat->type = mat->type;

  /* Allocate memory spaces to store the actual matrix data. */
  newMat->data.u = malloc(newMat->rows * sizeof(void*));

  rowBytes = newMat->cols * DataTypeSize(newMat->type); /* Bytes per row. */
  for (i = 0; i < newMat->rows; i++) {
    newMat->data.u[i] = malloc(rowBytes); /* Allocate per-row spaces. */
    memcpy(newMat->data.u[i], mat->data.u[i], rowBytes); /* Copy data. */
  }

  return newMat;
}

void Mat_Release(Mat* mat)
{
  assert(mat != NULL);
  int i;

  /* Deallocate per row memory spaces. */
  for (i = 0; i < mat->rows; i++)
    free(mat->data.u[i]);

  free(mat->data.u); /* Deallocate row pointers. */
  free(mat); /* Dealocate matrix. */
}

Mat* Mat_ConvertToColor(Mat* mat)
{
  assert(mat != NULL && mat->type == UCHAR);

  Mat* dst;
  int i, j;

  dst = Mat_Init(mat->rows, mat->cols, COLOR_PIXEL);
  for (j = 0; j < mat->rows; j++) {
    for (i = 0; i < mat->cols; i++) {
      dst->data.cp[j][i].r = mat->data.u[j][i];
      dst->data.cp[j][i].g = mat->data.u[j][i];
      dst->data.cp[j][i].b = mat->data.u[j][i];
    }
  }

  return dst;
}

Mat* Mat_FloatToChar(Mat* mat)
{
  assert(mat->type == FLOAT);

  int i, j;
  float val, min = 0, max = 1;
  Mat* newMat;

  /* Search for the min/max value of the matrix. */
  for (j = 0; j < mat->rows; j++) {
    for (i = 0; i < mat->cols; i++) {
      val = mat->data.f[j][i];
      if (val < min) min = val;
      if (val > max) max = val;
    }
  }

  /* Initialize UCHAR matrix and do conversion from FLOAT. */
  newMat = Mat_Init(mat->rows, mat->cols, UCHAR);
  for (j = 0; j < mat->rows; j++) {
    for (i = 0; i < mat->cols; i++) {

      /* Scale FLOAT to UCHAR. */
      uchar newVal = (uchar) ((mat->data.f[j][i] - min) * 255 / (max - min));
      newMat->data.u[j][i] = newVal;
    }
  }

  return newMat;
}

Mat* Mat_Invert(Mat* src, Mat* dst)
{
  assert(src != NULL && src->type == UCHAR);
  if (dst != NULL) {
    assert(dst->type == UCHAR &&
        dst->rows == src->rows &&
        dst->cols == src->cols);
  } else {
    /* If dst is not provided, initialize one. */
    dst = Mat_Init(src->rows, src->cols, UCHAR);
  }

  /* Do inversion. */
  int i, j;
  for (j = 0; j < src->rows; j++)
    for (i = 0; i < src->cols; i++)
      dst->data.u[j][i] = src->data.u[j][i] ^ 255;

  return dst;
}

Mat MatInit(int rows, int cols, DataType type)
{
  Mat* mat;

  mat = Mat_Init(rows, cols, type);
  return *mat;
}

Mat MatClone(Mat* mat)
{
  Mat* newMat;

  newMat = Mat_Clone(mat);
  return *newMat;
}

void MatRelease(Mat* mat)
{
  assert(mat != NULL);
  int i;

  /* Deallocate per row memory spaces. */
  for (i = 0; i < mat->rows; i++)
    free(mat->data.u[i]);

  free(mat->data.u); /* Deallocate row pointers. */
  mat->data.u = NULL;

  /* Deallocate matrix header. */
  mat->rows = 0;
  mat->cols = 0;
  mat->type = 0;
}

void ConvertToColorMat(Mat* src, Mat* dst)
{
  *dst = *Mat_ConvertToColor(src);
}
