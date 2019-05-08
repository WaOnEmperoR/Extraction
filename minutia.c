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
    minutia->total_length = (int) swap_int32(buffer[0]);
    printf("Total Length : %d\n", minutia->total_length);

    fread(buffer, 2, 1, fin);// rubbish

    fread(buffer, 2, 1, fin);
    minutia->imgSizeX = (int) swap_int16(buffer[0]);
    printf("Image Size X : %d\n", minutia->imgSizeX);

    fread(buffer, 2, 1, fin);
    minutia->imgSizeY = (int) swap_int16(buffer[0]);
    printf("Image Size Y : %d\n", minutia->imgSizeY);
    standardDpiHeight = minutia->imgSizeY;

    fread(buffer, 2, 1, fin);
    minutia->pixelCmX = (int) swap_int16(buffer[0]);

    fread(buffer, 2, 1, fin);
    minutia->pixelCmY = (int) swap_int16(buffer[0]);

    fread(buf_c, 1, 1, fin);
    minutia->fingerprintNum = (int) buf_c[0];
    printf("Fingerprint Num : %d\n", minutia->fingerprintNum);

    fread(buf_c, 1, 1, fin); //rubbish
    fread(buf_c, 1, 1, fin); //rubbish
    fread(buf_c, 1, 1, fin); //rubbish

    fread(buf_c, 1, 1, fin);
    minutia->fingerprintQuality = (int) buf_c[0];
    printf("Quality : %d\n", minutia->fingerprintQuality);

    fread(buf_c, 1, 1, fin);
    minutia->minutiaeNum = (int) buf_c[0];
    jumlah_minutiae = buf_c[0];
    printf("Minutiae Number : %d\n", minutia->minutiaeNum);

    minutia->minutiae_list = malloc(minutia->minutiaeNum * sizeof(Minutiae));

    for (int j=0; j<jumlah_minutiae; j++)
    {
        fread(buffer, 2, 1, fin);
        xPacked = swap_int16(buffer[0]);
        minutia->minutiae_list[j].x = (int) (xPacked & 0x3FFF);

//        printf("%d %d\n", (j+1), minutia->minutiae_list[j].x );

        type_par = xPacked & 0xC000;
        //printf("Minutia Type : %d\n", type_par);
        //printf("%d %d\n", (type_par >> 14) & 1, (type_par >> 15) & 1);
        bit14 = (type_par >> 14) & 1;
        bit15 = (type_par >> 15) & 1;
        if (bit14 == 1)
        {
            minutia->minutiae_list[j].type = BIFURCATION;
        }
        else if (bit15==1)
        {
            minutia->minutiae_list[j].type = RIDGE_ENDING;
        }
        else
        {
            minutia->minutiae_list[j].type = OTHER;
        }

        fread(buffer, 2, 1, fin);
        temp = swap_int16(buffer[0]);
        temp = temp & 0x3FFF;
        minutia->minutiae_list[j].y = (int) (standardDpiHeight - 1 - temp);

        fread(buf_c, 1, 1, fin);
        minutia->minutiae_list[j].direction = (float) buf_c[0];

        fread(buf_c, 1, 1, fin);
        minutia->minutiae_list[j].quality = (int) buf_c[0];

        minutia->minutiae_list[j].CN = 0;
    }

    return minutia;
}

void IO_Minutia_Read(Minutia* minutia)
{
    printf("%d\n", minutia->total_length);
    printf("%d\n", minutia->imgSizeX);
    printf("%d\n", minutia->fingerprintNum);
}

void Minutia_Read(Minutia* minutia)
{
    IO_Minutia_Read(minutia);
}
