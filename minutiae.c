#include "minutia.h"
#include "minutiae.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

//! Byte swap short
int16_t swap_int16( int16_t val )
{
    return (val << 8) | ((val >> 8) & 0xFF);
}

//! Byte swap int
int32_t swap_int32( int32_t val )
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
    return (val << 16) | ((val >> 16) & 0xFFFF);
}

Minutia* Minutia_Init(char* fileName)
{
    FILE *fin;
    int character;
    fin = fopen(fileName, "rb");

    int buffer[2000];
    char FMR[100];
    short buf_c[20];
    short jumlah_minutiae, direction, quality;
    int xPacked, standardDpiHeight, temp, type_par, bit14, bit15;

    Minutia* minutia;

    minutia = malloc(sizeof(Minutia));

    fread(FMR, 1, 8, fin);
    fread(buffer, 4, 1, fin);
    minutia->total_length = swap_int32(buffer[0]);

    fread(buffer, 2, 1, fin);// rubbish

    fread(buffer, 2, 1, fin);
    minutia->imgSizeX = swap_int16(buffer[0]);

    fread(buffer, 2, 1, fin);
    minutia->imgSizeY = swap_int16(buffer[0]);
    standardDpiHeight = minutia->imgSizeY;

    fread(buffer, 2, 1, fin);
    minutia->pixelCmX = swap_int16(buffer[0]);

    fread(buffer, 2, 1, fin);
    minutia->pixelCmY = swap_int16(buffer[0]);

    fread(buf_c, 1, 1, fin);
    minutia->fingerprintNum = (int) buf_c[0];

    fread(buf_c, 3, 1, fin);

    fread(buf_c, 1, 1, fin);
    minutia->fingerprintQuality = (int) buf_c[0];

    fread(buf_c, 1, 1, fin);
    minutia->minutiaeNum = (int) buf_c[0];
    jumlah_minutiae = buf_c[0];

    minutia->minutiae_list = malloc(minutia->minutiaeNum * sizeof(Minutiae));

    for (int j=0; j<jumlah_minutiae; j++)
    {
        Minutiae* minutiae = malloc(sizeof(Minutiae));

        fread(buffer, 2, 1, fin);
        xPacked = swap_int16(buffer[0]);
        minutiae->x = (int) (xPacked & 0x3FFF);

        type_par = xPacked & 0xC000;
        //printf("Minutia Type : %d\n", type_par);
        //printf("%d %d\n", (type_par >> 14) & 1, (type_par >> 15) & 1);
        bit14 = (type_par >> 14) & 1;
        bit15 = (type_par >> 15) & 1;
        if (bit14 == 1)
        {
            minutiae->type = BIFURCATION;
        }
        else if (bit15==1)
        {
            minutiae->type = RIDGE_ENDING;
        }
        else
        {
            minutiae->type = OTHER;
        }

        fread(buffer, 2, 1, fin);
        temp = swap_int16(buffer[0]);
        temp = temp & 0x3FFF;
        minutiae->y = (int) (standardDpiHeight - 1 - temp);

        fread(buf_c, 1, 1, fin);
        minutiae->direction = (float) buf_c[0];

        fread(buf_c, 1, 1, fin);
        minutia->minutiae_list[j].quality = (int) buf_c[0];

        minutiae->CN = 0;

    }

}
