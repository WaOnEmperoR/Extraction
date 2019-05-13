#include "minutia.h"
#include "minutiae.h"
#include "log.h"
#include "typedef.h"
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

    fread(buffer, 2, 1, fin);// rubbish

    fread(buffer, 2, 1, fin);
    minutia->imgSizeX = (int) swap_int16(buffer[0]);

    fread(buffer, 2, 1, fin);
    minutia->imgSizeY = (int) swap_int16(buffer[0]);
    standardDpiHeight = minutia->imgSizeY;

    fread(buffer, 2, 1, fin);
    minutia->pixelCmX = (int) swap_int16(buffer[0]);

    fread(buffer, 2, 1, fin);
    minutia->pixelCmY = (int) swap_int16(buffer[0]);

    fread(buf_c, 1, 1, fin);
    minutia->fingerprintNum = (int) buf_c[0];

    fread(buf_c, 1, 1, fin); //rubbish
    fread(buf_c, 1, 1, fin); //rubbish
    fread(buf_c, 1, 1, fin); //rubbish

    fread(buf_c, 1, 1, fin);
    minutia->fingerprintQuality = (int) buf_c[0];

    fread(buf_c, 1, 1, fin);
    minutia->minutiaeNum = (int) buf_c[0];
    jumlah_minutiae = buf_c[0];

    minutia->minutiae_list = malloc(minutia->minutiaeNum * sizeof(Minutiae));

    for (int j=0; j<jumlah_minutiae; j++)
    {
        fread(buffer, 2, 1, fin);
        xPacked = swap_int16(buffer[0]);
        minutia->minutiae_list[j].x = (int) (xPacked & 0x3FFF);

        type_par = xPacked & (short) 0xC000;
        //printf("Minutia Type : %d\n", type_par);
        //printf("%d %d\n", (type_par >> 14) & 1, (type_par >> 15) & 1);
        switch (type_par)
        {
            case 0x4000 :
                minutia->minutiae_list[j].type=RIDGE_ENDING;
                break;
            case 0x8000 :
                minutia->minutiae_list[j].type=BIFURCATION;
                break;
            case 0 :
                minutia->minutiae_list[j].type=OTHER;
                break;
            default :
                break;
        }
//        bit14 = (type_par >> 14) & 1;
//        bit15 = (type_par >> 15) & 1;
//        if (bit14 == 1)
//        {
//            minutia->minutiae_list[j].type = BIFURCATION;
//        }
//        else if (bit15==1)
//        {
//            minutia->minutiae_list[j].type = RIDGE_ENDING;
//        }
//        else
//        {
//            minutia->minutiae_list[j].type = OTHER;
//        }

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

void IO_Minutia_Write(char* fileName, Minutia* minutia)
{
    FILE *fp;
    char str_header[] = "FMR\0 20";

    fp = fopen(fileName, "w");
    fwrite(str_header, 1, sizeof(str_header), fp);

    int* tot_len = swap_int32(minutia->total_length);
    fwrite(&tot_len, 1, 4, fp);

    char rubbish[] = "\0";

    //2B rubbish
    fwrite(rubbish, 2, sizeof(char), fp);

    short* imgX = swap_int16((short) minutia->imgSizeX);
    fwrite(&imgX, 1, sizeof(short), fp);

    short* imgY = swap_int16((short) minutia->imgSizeY);
    fwrite(&imgY, 1, sizeof(short), fp);

    short* pixCmX = swap_int16((short) minutia->pixelCmX);
    fwrite(&pixCmX, 1, sizeof(short), fp);

    short* pixCmY = swap_int16((short) minutia->pixelCmY);
    fwrite(&pixCmY, 1, sizeof(short), fp);

    short* fpNum = (short) minutia->fingerprintNum;
    fwrite(&fpNum, 1, 1, fp);

    //3B rubbish
    fwrite(rubbish, 1, sizeof(char), fp);
    fwrite(rubbish, 1, sizeof(char), fp);
    fwrite(rubbish, 1, sizeof(char), fp);

    short* fpQuality = (short) minutia->fingerprintQuality;
    fwrite(&fpQuality, 1, 1, fp);

    short* minutiaeNum = (short) minutia->minutiaeNum;
    fwrite(&minutiaeNum, 1, 1, fp);

    for (int i=0; i<minutia->minutiaeNum; i++)
    {
        int x_pos_masked = (minutia->minutiae_list[i].x & 0x3FFF);

        int type;
        switch (minutia->minutiae_list[i].type)
        {
            case RIDGE_ENDING :
                type = 0x4000;
                break;
            case BIFURCATION :
                type = 0x8000;
                break;
            case OTHER :
                type = 0;
                break;
            default :
                break;
        }
        short* x_pos_ready = swap_int16((short) (x_pos_masked | type));
        fwrite(&x_pos_ready, 1, sizeof(short), fp);

        int y_pos_masked = minutia->imgSizeY - minutia->minutiae_list[i].y - 1;
        y_pos_masked = y_pos_masked & 0x3FFF;

        short* y_pos_ready = swap_int16((short) y_pos_masked);
        fwrite(&y_pos_ready, 1, sizeof(short), fp);

        short* direction = (short) minutia->minutiae_list[i].direction;
        fwrite(&direction, 1, 1, fp);

        short* quality = (short) minutia->minutiae_list[i].quality;
        fwrite(&quality, 1, 1, fp);
    }

    fwrite(rubbish, 1, sizeof(char), fp);
    fwrite(rubbish, 1, sizeof(char), fp);

    fclose(fp);
}

void Minutia_Release(Minutia* minutia)
{
    assert(minutia != NULL);
    int i;

    free(minutia->minutiae_list);
    free(minutia);
}

void IO_Minutia_Read(Minutia* minutia)
{
    printf("%-25s %10d\n", "Minutia Length", minutia->total_length);
    printf("%-25s %10d\n", "Image Size X", minutia->imgSizeX);
    printf("%-25s %10d\n", "Image Size Y", minutia->imgSizeY);
    printf("%-25s %10d\n", "Pixel x size (cm)", minutia->pixelCmX);
    printf("%-25s %10d\n", "Pixel y size (cm)", minutia->pixelCmY);
    printf("%-25s %10d\n", "Number of Fingerprint", minutia->fingerprintNum);
    printf("%-25s %10d\n", "Fingerprint Quality", minutia->fingerprintQuality);
    printf("%-25s %10d\n", "Number of Minutiae", minutia->minutiaeNum);
    for (int i=0; i<minutia->minutiaeNum; i++)
    {
        printf("----------------\n");
        printf("%-25s %10d\n", "Minutiae Number", i);
        printf("%-25s %10d\n", "Minutiae X Position", minutia->minutiae_list[i].x);
        printf("%-25s %10d\n", "Minutiae Y Position", minutia->minutiae_list[i].y);
        printf("%-25s %10d\n", "Minutiae Type", minutia->minutiae_list[i].type);
        printf("%-25s %10f\n", "Minutiae Direction", minutia->minutiae_list[i].direction);
        printf("%-25s %10d\n", "Minutiae Quality", minutia->minutiae_list[i].quality);
    }
    printf("---------------\n");
}

void Minutia_Read(Minutia* minutia)
{
    IO_Minutia_Read(minutia);
}

void Minutia_Write(char* fileName, Minutia* minutia)
{
    IO_Minutia_Write(fileName, minutia);
}
