#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

/**
 * Nick Sifniotis
 * 28th December 2015
 * 
 * vigenere.c
 * 
 * Simple implementation of the Vigenere cipher.
 * There's nothing clever in this code.
 */
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Yelling at the user!\n");
        return 1;
    }

    string keyword = argv[1];
    int key_length = strlen(keyword);
    int key[key_length];
    
    for (int i = 0; i < key_length; i ++)
    {
        if (isupper(keyword[i]))
            key[i] = keyword[i] - 'A';
        else if (islower(keyword[i]))
            key[i] = keyword[i] - 'a';
        else
        {
            printf("Yelling at the user!\n");
            return 1;
        }
    }

    string input_text = GetString();

    char result;
    int counter = 0;
    int key_position = 0;
    while (input_text[counter])
    {
        if (isupper(input_text[counter]))
        {
            result = 'A' + (((input_text[counter] - 'A') + key[key_position]) % 26);
            key_position = (key_position + 1) % key_length;
        }
        else if (islower(input_text[counter]))
        {
            result = 'a' + (((input_text[counter] - 'a') + key[key_position]) % 26);
            key_position = (key_position + 1) % key_length;
        }
        else
            result = input_text[counter];
            
        printf("%c", result);
        counter++;
    }
    printf("\n");
}