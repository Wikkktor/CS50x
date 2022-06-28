#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    if ( argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Store 512 bytes in an array
    unsigned char buffer[512];

    // Number of images generated
    int counter = 0;

    // File for recovered images
    FILE *out_f = NULL;

    // output filename
    char *f_name = malloc(8 * sizeof(char));

    while(fread(buffer, sizeof(char), 512, f))
    {
        // Check if it is JPEG file
         if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
         {
            // Write filename
            sprintf(f_name, "%03i.jpg", counter);

            // Open file
            out_f = fopen(f_name, "w");

            // Add to counter
            counter++;
         }
         if (out_f != NULL)
         {
            fwrite(buffer, sizeof(char), 512, out_f);
         }
    }
    free(f_name);
    fclose(out_f);
    return 0;




}