#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int ht; // Variable assigned for height
    int r; // Row counting variable
    int c; // Column counting variable
    int s; // Variable assigned for space

    do
    {
        // Ask user to enter height between 1 to 8 only
        ht = get_int("Enter height between 1 to 8 only: ");
    }
    // condition to make height input between 1 to 8 only
    while (ht < 1 || ht > 8);

    // For each row, check if row is less than height then increment
    for (r = 0; r < ht; r++)
    {
        // To print space, the condition should be space must be less than height minus row minus 1
        for (s = 0; s < ht - r - 1; s++)
        {
            // Print space if condition is met
            printf(" ");
        }
        // Only print hash if column is less than or equal to row
        for (c = 0; c <= r; c++)
        {
            // Print a hash
            printf("#");
        }
        // Print Gap
        printf("  ");

        // Print the right lane hashes
        for (c = 0; c <= r; c++)
        {
            printf("#");
        }

        // Move to next row
        printf("\n");
    }
}