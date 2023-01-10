#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Declaring variables
    typedef uint8_t BYTE;
    BYTE buffer[512];
    int bytes_read, count = 0;
    char filename[8];

    // opening memory
    FILE *f = fopen(argv[1], "r");
    FILE *img = NULL;

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    if (f == NULL)
    {
        printf("./recover card.raw");
        return 1;
    }

    // loop until true
    while (true)
    {
        // read 512 bytes
        bytes_read = fread(buffer, sizeof(BYTE), 512, f);

        // new image
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // if first image
            if (count == 0)
            {
                // create the image and write
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), bytes_read, img);
                count++;
            }
            else
            {
                // close the file
                fclose(img);
                sprintf(filename, "%03i.jpg", count);

                // open the file and write to it
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), bytes_read, img);
                count++;
            }
        }
        // if the JPEG is already found
        else if (count != 0)
        {
            // continue writing to it multiple times
            fwrite(buffer, sizeof(BYTE), bytes_read, img);

            if (bytes_read == 0)
            {
                fclose(img);
                fclose(f);
                return 0;
            }
        }
    }
    fclose(img);
    fclose(f);
}