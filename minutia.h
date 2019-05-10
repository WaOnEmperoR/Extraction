#ifndef MINUTIA_H_INCLUDED
#define MINUTIA_H_INCLUDED

#include "typedef.h"
#include "minutiae.h"

typedef struct Minutia Minutia;

struct Minutia
{
    int total_length;
    int imgSizeX;
    int imgSizeY;
    int pixelCmX;
    int pixelCmY;
    int fingerprintNum;
    int fingerprintQuality;
    int minutiaeNum;

    Minutiae* minutiae_list;
};

Minutia* Minutia_Init(char* fileName);

void IO_Minutia_Read(Minutia* minutia);

void Minutia_Read(Minutia* minutia);

void IO_Minutia_Write(char* fileName, Minutia* minutia);

void Minutia_Write(char* fileName, Minutia* minutia);

int32_t swap_int32( int32_t val );
int16_t swap_int16( int16_t val );

#endif // MINUTIA_H_INCLUDED
