/**
* Ryan Oliver
* CS50
* PSET 4 Recover
*
* Recovers deleted jpeg files from memory card
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensures proper usage of command
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file.raw\n");
        return 1;
    }

    // remembering filename
    char *infile = argv[1];

    // Opens input file
    FILE *inputFile = fopen(infile, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    // creating buffer block
    BYTE buffer[512];

    // tracking jpg filename counter
    int counter = 0;
    // initializes img file pointer
    FILE *img = NULL;

    while (fread(buffer, 512, 1, inputFile))
    {
        // Checking for JPEG signature
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            //checks to see if file is still open and closes if so.
            if (img != NULL)
            {
                fclose(img);
            }

            char filename[8];
            // create new filename for jpg
            sprintf(filename, "%03i.jpg", counter);

            // open image file
            img = fopen(filename, "w");

            counter++;

        }
        // checks if file is still open
        if (img != NULL)
        {
            // write bytes to file
            fwrite(buffer, 512, 1, img);
        }

    }
    // checks if tile is still open
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(inputFile);

    // success
    return 0;
}