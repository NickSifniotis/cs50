#include <ctype.h>
#include <stdio.h>
#include <cs50.h>


/**
 * Nick Sifniotis
 * 28 December 2015
 * 
 * initials.c
 * 
 * Accepts a name from the user and prints out the initials of that name.
 */
int main(int argc, string argv[])
{
    string input_name = GetString();
    
    bool print_next_letter = true;
    int position = 0;
    while (input_name[position])
    {
        if (print_next_letter)
        {
            printf("%c", toupper(input_name[position]));
            print_next_letter = false;
        }
        
        if (input_name[position] == ' ')
            print_next_letter = true;
            
        position++;
    }
    printf("\n");
}