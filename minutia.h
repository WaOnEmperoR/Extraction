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




#endif // MINUTIA_H_INCLUDED
