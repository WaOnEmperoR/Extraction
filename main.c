#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main()
{
    FILE *fpo;
    int  i, j;
    unsigned char  pixel;

    fpo = fopen( "output/out2.pgm", "w") ;
    fprintf( fpo, "P5\n800 600\n255\n" );

    for ( j = 0 ; j < 600 ; j++ )
    {
        for ( i = 0 ; i < 800 ; i++ )
        {
            pixel = (unsigned char)( 255 * (float)rand()/RAND_MAX );
            //      fprintf(stderr,"%4.3f\n", (unsigned char)( 255 * (float)rand()/RAND_MAX ) );
            fwrite( &pixel, sizeof(unsigned char), 1, fpo );
        }
    }
    fclose(fpo);

    Mat* fp_original = IO_ReadPGM("adminduk/001.pgm");

    printf("Hello world!\n");
    return 0;
}
