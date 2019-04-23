
#include "image.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

Mat* IO_ReadPGM(const char* fileName)
{
  const int bufSize = 100;
  char buf[bufSize];

  FILE* in = fopen(fileName, "r");
  if (in == NULL) {
    /* File does not exists? */
    ABORT("Error in opening image file: %s\n", fileName);
  }

  /* Read magic number. Currently only raw PGM file (P5) is supported. */
  fgets(buf, bufSize, in);
  if (strcmp(buf, "P5\n") != 0) {
    ABORT("Magic number is not recognized\n");
  }

  /* Read the size of the image. */
  do { fgets(buf, bufSize, in); } while (buf[0] == '#');
  int cols = atoi(strtok(buf, " "));
  int rows = atoi(strtok(NULL, " "));

  /* Get maxval. Ignore this value and treat maxval as 255. */
  do { fgets(buf, bufSize, in); } while (buf[0] == '#');

  /* Read image data. */
  Mat* mat = Mat_Init(rows, cols, UCHAR);
  int j;
  for (j = 0; j < mat->rows; j++)
    fread(mat->data.u[j], DataTypeSize(UCHAR), cols, in);

  fclose(in);
  return mat;
}

Mat* IO_ReadPPM(const char* fileName)
{
  const int bufSize = 100;
  char buf[bufSize];

  FILE* in = fopen(fileName, "r");
  if (in == NULL) {
    /* File does not exists? */
    ABORT("Error in opening image file: %s\n", fileName);
  }

  /* Read magic number. Currently only raw PGM file (P5) is supported. */
  fgets(buf, bufSize, in);
  if (strcmp(buf, "P6\n") != 0) {
    ABORT("Magic number is not recognized\n");
  }

  /* Read the size of the image. */
  do { fgets(buf, bufSize, in); } while (buf[0] == '#');
  int cols = atoi(strtok(buf, " "));
  int rows = atoi(strtok(NULL, " "));

  /* Get maxval. Ignore this value and treat maxval as 255. */
  do { fgets(buf, bufSize, in); } while (buf[0] == '#');

  /* Read image data. */
  Mat* mat = Mat_Init(rows, cols, COLOR_PIXEL);
  int j;
  for (j = 0; j < mat->rows; j++)
    fread(mat->data.cp[j], DataTypeSize(COLOR_PIXEL), cols, in);

  fclose(in);
  return mat;
}

void IO_WritePGM(const char* fileName, Mat* mat)
{
  assert(mat->type == UCHAR || mat->type == FLOAT);
  int j, isFloat;
  FILE* out;

  /* Attempt to open file. */
  out = fopen(fileName, "w");
  if (out == NULL) {
    ABORT("Error in writing image file: %s\n", fileName);
  }

  /* If mat is of type FLOAT, do conversion. */
  isFloat = (mat->type == FLOAT) ? 1 : 0;
  if (isFloat) mat = Mat_FloatToChar(mat);

  /* Write file header and image data. */
  fprintf(out, "P5\n%d %d\n255\n", mat->cols, mat->rows);
  for (j = 0; j < mat->rows; j++)
    fwrite(mat->data.u[j], DataTypeSize(UCHAR), mat->cols, out);

  /* Be a good C programmer. Do some memory clean-up. */
  if (isFloat) Mat_Release(mat);
  fclose(out);
}

void IO_WritePPM(const char* fileName, Mat* mat)
{
  assert(mat->type == COLOR_PIXEL);

  FILE* out = fopen(fileName, "w");
  if (out == NULL) {
    ABORT("Error in writing image file: %s\n", fileName);
  }

  /* Write file header. */
  fprintf(out, "P6\n%d %d\n255\n", mat->cols, mat->rows);

  /* Write image data. */
  int j;
  for (j = 0; j < mat->rows; j++)
    fwrite(mat->data.cp[j], DataTypeSize(COLOR_PIXEL), mat->cols, out);
  fclose(out);
}

Mat ReadPGM(const char* fileName)
{
  return *(IO_ReadPGM(fileName));
}

Mat ReadPPM(const char* fileName)
{
  return *(IO_ReadPPM(fileName));
}

void WritePGM(const char* fileName, Mat* mat)
{
  IO_WritePGM(fileName, mat);
}

void WritePPM(const char* fileName, Mat* mat)
{
  IO_WritePPM(fileName, mat);
}
