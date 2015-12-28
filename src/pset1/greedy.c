#include <stdio.h>
#include <cs50.h>
#include <math.h>


/**
 * Nick Sifniotis
 * 28th December 2015
 * 
 * greedy.c
 * 
 * Compute the minimum number of coins required to make change.
 * The amount of change to make is specified by the user - it must be
 * non-negative.
 * 
 * The default calculation uses American currency. To use Australian
 * denominations, switch the flag use_australian from false to true.
 */
int main(void)
{
    bool use_australian = false;
    
    float unprocessed_input = -1.0;
    while (unprocessed_input < 0.0)
    {
        printf("Please enter amount of change: ");
        unprocessed_input = GetFloat();
    }
    int change_input = round(unprocessed_input * 100);
    
    int yank_denominations[] = { 4, 25, 10, 5 };
    int skip_denominations[] = { 7, 200, 100, 50, 20, 10, 5 };
    
    int* denominations = (use_australian) ? skip_denominations : yank_denominations;
    
    
    int result = 0;
    for (int i = 1, j = denominations[0]; i < j; i ++)
    {
        result += change_input / denominations[i];
        change_input %= denominations[i];
    }
    result += change_input;
    
    printf ("%d\n", result);
}