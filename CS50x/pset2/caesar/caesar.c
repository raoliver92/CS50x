#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv [])
{
    if (argc != 2)
    {
        printf("please enter your key. (1 argument)!\n");
        return 1;
    }

    //accepting number from user
    string k = argv[1];

    //converting string "number" to integer
    int n = atoi(k);

    if(n < 0)
    {
        printf("please enter a positive number!\n");
    }
    else
    {

        //gets string from user
        string p = get_string("Enter your text: ");

        //Prints out plain text
        printf("plaintext:   %s\n", p);

        /*[TODO]:
            1. Make numbers loop back around to beginning of alphabet after z
            2. If number is larger than 26, Treat it as starting over. (i.e. 27 = 1, 28 =2, etc.)
        */
        //Completes cipher based on user key and prints out ciphertext.
        printf("ciphertext:  ");
        for(int i=0, l = strlen(p); i < l; i++)
        {
            char c[l];
            if(isalpha(p[i]))
            {
                if(isupper(p[i]))
                {
                    c[i] = (((p[i] + n) - 65) % 26) + 65;
                }
                else if(islower(p[i]))
                {
                    c[i] = (((p[i] + n) - 97) % 26) + 97;
                }
            }
            else
            {
                c[i] = p[i];
            }
            printf("%c", c[i]);
        }
        printf("\n");
        return 0;
    }

}