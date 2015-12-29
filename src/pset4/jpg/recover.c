#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */


bool is_jpg(uint8_t *buffer)
{
    return (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && ((buffer[3] & 0xE0)== 0xE0));
}


int main(int argc, char* argv[])
{
    FILE* input_file = fopen("card.raw", "r");
    FILE* output_file = NULL;
    int counter = 0;
    
    uint8_t buffer[512];

    while (fread(&buffer, sizeof(buffer), 1, input_file) != 0)
    {
        if (is_jpg (buffer))
        {
            if (output_file != NULL)
                fclose(output_file);
                
            char new_filename[8];
            sprintf(new_filename, "%.3u.jpg", counter);
            
            output_file = fopen(new_filename, "w");
            counter++;
        }
        
        if (output_file != NULL)
            fwrite(&buffer, sizeof(buffer), 1, output_file);
    }

    if (output_file != NULL)
        fclose(output_file);
        
    fclose(input_file);
}
