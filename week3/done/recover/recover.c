// EDITED

// gcc -o recover recover.c cs50.c  
// ./recover card.raw

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    unsigned char buffer[512];
    int file_count = 0;
    char filename[9];  // Buffer to store the filename
    FILE *img = NULL;

    while (fread(buffer, 512, 1, inptr) == 1)
    {
        // Check for the start of a new JPG file
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a new JPG is found, close the previous file
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a filename for the found JPG
            sprintf(filename, "%03i.jpg", file_count);
            printf("Begining of JPG file found: %s\n", filename);

            // Open the new JPG file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(inptr);
                return 3;
            }

            file_count++;
        }

        // If an img file is open, write the buffer to it
        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    // Close any remaining files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(inptr);

    return 0;
}




