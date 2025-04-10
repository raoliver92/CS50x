// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //converts fractions to integer and gets numerator / denominator
    char x = fraction[0];
    char y = fraction[2];
    //initializes duration
    int duration = 0;
    //checks for numerator
    if (x == '1')
    {
        //performs switch to check denominator if numerator is 1
        switch (y)
        {
            case '8' :
                duration = 1;
                break;
            case '4' :
                duration = 2;
                break;
            case '2' :
                duration = 4;
                break;
            case '1' :
                duration = 8;
        }

    }
    else if (x == '3' && y == '8')
    {
        //returns numerator as x if numerator is any other number.
        duration = 3;
    }

    //returns duration
    return duration;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
//     //initializes frequency
//     int frequency = 0;

    //initializes notes
    char n = note[0];
    int octave = note[strlen(note) - 1];

    //Initialize frequency
    double freq = 0.0;

    //adjusts to int
    octave -= 48;

    //Determines note
    switch (n)
    {
        case 'A' :
            freq = 440.0;
            break;
        case 'B' :
            freq = 440.0 * (pow(2.0, (2.0 / 12.0)));
            break;
        case 'C' :
            freq = 440.0 / (pow(2.0, (9.0 / 12.0)));
            break;
        case 'D' :
            freq = 440.0 / (pow(2.0, (7.0 / 12.0)));
            break;
        case 'E' :
            freq = 440.0 / (pow(2.0, (5.0 / 12.0)));
            break;
        case 'F' :
            freq = 440.0 / (pow(2.0, (4.0 / 12.0)));
            break;
        case 'G' :
            freq = 440.0 / (pow(2.0, (2.0 / 12.0)));
            break;
    }

    //Shift octave
    if (octave > 4)
    {
        for (int i = 0; i < octave - 4; i++)
        {
            freq *= 2.0;
        }
    }
    else if (octave < 4)
    {
        for (int i = 0; i < 4 - octave; i++)
        {
            freq /= 2.0;
        }
    }

    //Check for accidentals
    if (note[1] == 'b')
    {
        freq /= (pow(2.0, (1.0 / 12.0)));
    }
    else if (note[1] == '#')
    {
        freq *= (pow(2.0, (1.0 / 12.0)));
    }


    int frequency = round(freq);

    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{

    //checks if string is an empty string or end line
    if (strcmp(s, ""))
    {
        return false;
    }
    else
    {
        return true;
    }
}
