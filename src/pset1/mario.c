#include <stdio.h>
#include <cs50.h>

/**
 * Nick Sifniotis
 * 28th December 2015
 * 
 * A little utility function. Repeats the character to_repeat
 * on the screen num_times. No line breaks are added.
 */
void repeat_chars(char to_repeat, int num_times)
{
    for (int i = 0; i < num_times; i++)
    {
        printf("%c", to_repeat);
    }
}

/**
 * Nick Sifniotis
 * 28th December 2015
 * 
 * mario.c
 * Display the Super Mario Brothers half-pyramid.
 * The height of the pyramid is input by the user. Valid heights
 * are between 0 and 23 inclusive.
 */
int main(void)
{
    int height = -1;
    while (height < 0 || height > 23)
    {
        printf ("Height: ");
        height = GetInt();
    }
    
    for (int i = 0; i < height; i++)
    {
        repeat_chars(' ', (height - 1) - i);
        repeat_chars('#', i + 2);
        printf("\n");
    }
}