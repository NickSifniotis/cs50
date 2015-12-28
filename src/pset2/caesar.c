#include <ctype.h>
#include <stdio.h>
#include <cs50.h>


/**
 * Nick Sifniotis
 * 28 December 2015
 * 
 * caesar.c
 * 
 * Implementation of the caesar cipher.
 * The key is provided on the command line.
 * The program prompts for ciphertext and outputs the encoded message
 * to the console.
 */
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Yelling at the user!\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    string input_data = GetString();
    
    char rotated;
    int position = 0;
    while(input_data[position])
    {
        if (isupper(input_data[position]))
        {
            rotated = (((input_data[position] - 'A') + key) % 26) + 'A';
        }
        else if (islower(input_data[position]))
        {
            rotated = (((input_data[position] - 'a') + key) % 26) + 'a';
        }
        else
            rotated = input_data[position];
            
        printf ("%c", rotated);
        position++;
    }
    printf("\n");
    
    return 0;
}