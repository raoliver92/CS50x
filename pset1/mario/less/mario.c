#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Enter a positive number no greater than 23: ");
    }
    while(n<0 || n>23);

    // printf("Height: %i", n);

    //Print Left Pyramid
    for(int i=1; i<=n; i++)
    {
        //Prints spaces to right align
        for(int k=n; k>i; k--)
        {
            printf(" ");
        }
        //Prints Hash Stairs
        for(int j=0; j<=i; j++)
        {
            printf("#");
        }

        // //Prints 'Space' between stairs
        // for(int space=0; space<n; space++)
        // {
        //     printf(" \n");
        // }

        // //Print right Hash Stairs
        // for(int j=0; j<=i; j++)
        // {
        //     printf("#");
        // }

        printf("\n");
    }

}