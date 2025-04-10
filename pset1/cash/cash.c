#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float input;
    //Asks user for input and checks if positive number.
    do
    {
        input = get_float("Change owed: ");
    }
    while(input<0);
    //converting dollars to cents
    float f = round(input * 100);

    //converting float to int
    int cents = f;
    //initializes counter
    int count = 0;
    //check for quarters
    while(cents >= 25)
    {
        count += 1;
        cents = cents - 25;
    }
    //check for dimes
    while(cents >= 10)
    {
        count += 1;
        cents = cents - 10;
    }
    //check for nickels
    while(cents >= 5)
    {
        count += 1;
        cents = cents - 5;
    }
    //check for pennies
    while(cents >= 1)
    {
        count += 1;
        cents = cents - 1;
    }

    printf("%i\n", count);


}