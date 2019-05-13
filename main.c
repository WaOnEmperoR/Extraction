#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "minutia.h"
#include "minutiae.h"

//! Byte swap short
//int16_t swap_int16( int16_t val )
//{
//    return (val << 8) | ((val >> 8) & 0xFF);
//}
//
////! Byte swap int
//int32_t swap_int32( int32_t val )
//{
//    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
//    return (val << 16) | ((val >> 16) & 0xFFFF);
//}

//void ReadTemplate(char* fileName)
//{
//    FILE *fin;
//    int character;
//    fin = fopen(fileName, "rb");
//
//    int buffer[2000];
//    char FMR[100];
//    short buf_c[20];
//    short jumlah_minutiae, direction, quality;
//    int xPacked, standardDpiHeight, temp, type_par, bit14, bit15;
//
//    fread(FMR, 1, 8, fin);
//    printf("Magic Number : ");
//    for (int i=0; i<8; i++)
//    {
//        printf("%c", FMR[i]);
//    }
//    printf("\n");
//
//    fread(buffer, 4, 1, fin);
//    printf("Total Length : %d\n", swap_int32(buffer[0]));
//
//    fread(buffer, 2, 1, fin);
//    printf("Rubbish (zeroed) : %d\n", swap_int16(buffer[0]));
//
//    fread(buffer, 2, 1, fin);
//    printf("Image size in pixel X : %d\n", swap_int16(buffer[0]));
//
//    fread(buffer, 2, 1, fin);
//    standardDpiHeight = swap_int16(buffer[0]);
//    printf("Image size in pixel Y : %d\n", standardDpiHeight);
//
//    fread(buffer, 2, 1, fin);
//    printf("Pixels per cm X : %d\n", swap_int16(buffer[0]));
//
//    fread(buffer, 2, 1, fin);
//    printf("Pixels per cm Y : %d\n", swap_int16(buffer[0]));
//
//    fread(buf_c, 1, 1, fin);
//    printf("Number of Fingerprint : %hi\n", buf_c[0]);
//
//    fread(buf_c, 1, 1, fin);
//    printf("Buffer : %hi\n", buf_c[0]);
//
//    fread(buf_c, 1, 1, fin);
//    printf("Buffer : %hi\n", buf_c[0]);
//
//    fread(buf_c, 1, 1, fin);
//    printf("Buffer : %hi\n", buf_c[0]);
//
//    fread(buf_c, 1, 1, fin);
//    printf("Fingerprint quality : %hi\n", buf_c[0]);
//
//    fread(buf_c, 1, 1, fin);
//    printf("Number of minutiae : %hi\n", buf_c[0]);
//    jumlah_minutiae = buf_c[0];
//
//    printf("=====================================\n");
//    for (int j=0; j<jumlah_minutiae; j++)
//    {
//        printf("Minutiae ke : %d\n", j+1);
//
//        fread(buffer, 2, 1, fin);
//        xPacked = swap_int16(buffer[0]);
//        printf("Pixels position X : %d\n", xPacked & 0x3FFF);
//        type_par = xPacked & 0xC000;
//        //printf("Minutia Type : %d\n", type_par);
//        //printf("%d %d\n", (type_par >> 14) & 1, (type_par >> 15) & 1);
//        bit14 = (type_par >> 14) & 1;
//        bit15 = (type_par >> 15) & 1;
//        if (bit14 == 1)
//        {
//            printf("Minutia Type : Bifurcation\n");
//        }
//        else if (bit15==1)
//        {
//            printf("Minutia Type : Ridge Ending\n");
//        }
//        else
//        {
//            printf("Minutia Type : Unknown Type\n");
//        }
//        //printf("Bit 27 : %d\n", type_par&(1 << 26));
//        //printf("Bit 28 : %d\n", type_par&(1 << 27));
//
//        //27 dan 28
//        fread(buffer, 2, 1, fin);
//        temp = swap_int16(buffer[0]);
//        //printf("Before : %04X\n", temp);
//        temp = temp & 0x3FFF;
//        //printf("After : %d %04X\n", temp, temp);
//        //printf("Standard DPI %d\n", standardDpiHeight - 1);
//        printf("Pixels position Y : %d\n", standardDpiHeight - 1 - temp);
//
//        fread(buf_c, 1, 1, fin);
//        printf("Direction : %hi\n", buf_c[0]);
//
//        fread(buf_c, 1, 1, fin);
//        printf("Minutia Quality : %hi\n", buf_c[0]);
//
//        printf("-----------------\n");
//    }
//}

int main()
{
    FILE *fpo;
    int  i, j;
    unsigned char  pixel;

//    fpo = fopen( "output/out2.pgm", "w") ;
//    fprintf( fpo, "P5\n800 600\n255\n" );
//
//    for ( j = 0 ; j < 600 ; j++ )
//    {
//        for ( i = 0 ; i < 800 ; i++ )
//        {
//            pixel = (unsigned char)( 255 * (float)rand()/RAND_MAX );
//            //      fprintf(stderr,"%4.3f\n", (unsigned char)( 255 * (float)rand()/RAND_MAX ) );
//            fwrite( &pixel, sizeof(unsigned char), 1, fpo );
//        }
//    }
//    fclose(fpo);

//    Mat* fp_original = IO_ReadRAW("adminduk/002-ex.RAW", 320, 480, 255);

//    DebugPGM(fp_original);

//    Mat* fp_original = IO_ReadPGM("adminduk/002-gen.pgm");

//    WritePGM("adminduk/002-gen.pgm", fp_original);

    Minutia* minutia = Minutia_Init("adminduk/154.iso");

    printf("==========\n");

    Minutia_Read(minutia);

//    free(minutia);

    Minutia_Write("adminduk/154-extra.iso", minutia);

//    ReadTemplate("adminduk/154.iso");
//    printf("Hello world!\n");
    return 0;
}
