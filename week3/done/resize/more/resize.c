// ADDED

// gcc -o resize resize.c cs50.c  
// ./resize .5 large.bmp small.bmp


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy scale infile outfile\n");
        return 1;
    }

    float scale = atof(argv[1]);
    if (scale <= 0)
    {
        fprintf(stderr, "Scale must be a positive number.\n");
        return 1;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int old_width = bi.biWidth;
    int old_height = bi.biHeight;
    int new_width = (int)(old_width * scale);
    int new_height = (int)(old_height * scale);

    int old_padding = (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (new_width * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth = new_width;
    bi.biHeight = new_height;
    bi.biSizeImage = (sizeof(RGBTRIPLE) * new_width + new_padding) * abs(new_height);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE *row = malloc(old_width * sizeof(RGBTRIPLE));

    for (int i = 0; i < abs(old_height); i++)
    {
        fread(row, sizeof(RGBTRIPLE), old_width, inptr);
        fseek(inptr, old_padding, SEEK_CUR);

        if (scale >= 1.0)
        {
            for (int j = 0; j < scale; j++)
            {
                for (int k = 0; k < new_width; k++)
                {
                    int old_pixel_index = (int)(k / scale);
                    fwrite(&row[old_pixel_index], sizeof(RGBTRIPLE), 1, outptr);
                }
                for (int l = 0; l < new_padding; l++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        else
        {

            if (i % (int)(1 / scale) == 0)
            {
                for (int k = 0; k < new_width; k++)
                {
                    int old_pixel_index = (int)(k / scale);
                    fwrite(&row[old_pixel_index], sizeof(RGBTRIPLE), 1, outptr);
                }
                for (int l = 0; l < new_padding; l++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    }

    free(row);
    fclose(inptr);
    fclose(outptr);
    return 0;
}
