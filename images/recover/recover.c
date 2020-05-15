#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Create infile
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Integer for naming files
    int file_count = 0;

    // Create outfile
    char *outfile = malloc(10 * sizeof(char));
    FILE *outptr;

    // Create buffer for reading and writing
    int memory_block = 512;
    BYTE *buffer = malloc(memory_block * sizeof(BYTE));

    // Main looping
    while (fread(buffer, sizeof(BYTE), memory_block, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (file_count == 0)
            {
                sprintf(outfile, "%03i.jpg", file_count);
                outptr = fopen(outfile, "w");
                if (outptr == NULL)
                {
                    fclose(inptr);
                    return 1;
                }
                file_count++;
            }
            else
            {
                fclose(outptr);
                sprintf(outfile, "%03i.jpg", file_count);
                outptr = fopen(outfile, "w");
                file_count++;
            }
        }
        fwrite(buffer, sizeof(BYTE), memory_block, outptr);
    }

    // Free allocated memory
    free(buffer);
    free(outfile);
    free(outptr);

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    return 0;
}

