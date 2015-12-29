/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames and stuff
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding for scanlines
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (factor * bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // need to update the fields biHeight, biWidth (h and w in pixels)
    // and biSizeImage which is the total number of bytes including padding.
    BITMAPFILEHEADER output_bf = bf;
    BITMAPINFOHEADER output_bi = bi;
    output_bi.biHeight *= factor;
    output_bi.biWidth *= factor;
    output_bi.biSizeImage = ((output_bi.biWidth * sizeof(RGBTRIPLE)) + out_padding) * abs(output_bi.biHeight);
    output_bf.bfSize = output_bi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&output_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&output_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // hold the entire scanline in a temporary array.
        RGBTRIPLE holding_array[bi.biWidth];
        
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            holding_array[j] = triple;
        }

        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);


        // dump the line to the output file factor times
        // remebering to repeat the pixels horizontally too.
        
        for (int height_repeater = 0; height_repeater < factor; height_repeater++)
        {
            for (int pixel = 0; pixel < bi.biWidth; pixel++)
            {
                for (int width_repeater = 0; width_repeater < factor; width_repeater++)
                {
                    // write RGB triple to outfile
                    fwrite(&holding_array[pixel], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // insert the padding
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
