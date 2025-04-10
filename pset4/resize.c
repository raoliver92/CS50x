/**
* Ryan Oliver
* CS50
* PSET 4 Resize
*
* Resizes a bitmap image to an integer to your choice
*/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile.\n");
        return 1;
    }
    // checks if value of n is valid
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n must be a positive integer <= 100. You provided %i.\n", n);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inputFile = fopen(infile, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outputFile = fopen(outfile, "w");
    if (outputFile == NULL)
    {
        fclose(inputFile);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputFile);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputFile);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputFile);
        fclose(inputFile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //Copying size
    int height = bi.biHeight;
    int width = bi.biWidth;

    //Updating size
    bi.biHeight *= n;
    bi.biWidth *= n;

    // determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //image size
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + newPadding);

    //file size
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputFile);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputFile);


    //getting memory for scanline
    RGBTRIPLE *mem = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(height); i < biHeight; i++)
    {
        int c = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);

            // adding pixel n times
            for (int l = 0; l < n; l++)
            {
                *(mem+(c)) = triple;
                c++;
            }
        }

        // skip over padding, if any
        fseek(inputFile, padding, SEEK_CUR);

        // write RGB triple to outputfile
        for (int k = 0; k < n; k++)
        {
            fwrite((mem), sizeof(RGBTRIPLE), bi.biWidth, outputFile);

            //write padding
            for (int x = 0; x < newPadding; x++)
            {
                fputc(0x00, outputFile);
            }
        }
    }

    //free memory
    free(mem);

    // close infile
    fclose(inputFile);

    // close outfile
    fclose(outputFile);

    // success
    return 0;
}
