/**
* Ryan Oliver
* CS50
* PSET 4 whodunit
*
* Removes red pigments from a "clue image" to display the secret message
*/

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: whodunit inputfile outputfile\n");
        return 1;
    }

    //saving filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    //opens input file
    FILE *inputFile = fopen(infile, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open file %s. \n", infile);
        return 2;
    }

    //opens output file
    FILE *outputFile = fopen(outfile, "w");
    if (outputFile == NULL)
    {
        fclose(inputFile);
        fprintf(stderr, "Could not create file %s. \n", outfile);
        return 3;
    }

    //reads in BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputFile);

    //reads in BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputFile);

    //makes sure file is 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 ||
        bi.biCompression != 0)
    {
        fclose(outputFile);
        fclose(inputFile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputFile);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputFile);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over inputfile's scanlines(rows)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels(columns) in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);

            //takes red from bitmap image
            if (triple.rgbtRed == 0xff)
            {
                triple.rgbtRed = 0x00;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
        }

        // skip over padding, if any
        fseek(inputFile, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputFile);
        }
    }

    // close infile
    fclose(inputFile);

    // close outfile
    fclose(outputFile);


    //success
    return 0;
}