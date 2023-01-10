#include "helpers.h"
#include "math.h" // for using round

// Convert image to grayscale
// The function grayscale should take an image and turn it into a black-and-white version of the same image.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // average the values of 3 integers
            int avg = round((image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue) / 3.0);
            image[row][col].rgbtRed = image[row][col].rgbtGreen = image[row][col].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
// The function sepia should take an image and turn it into a sepia version of the same image.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /* sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue */

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sepiaRed = round(0.393 * image[row][col].rgbtRed + 0.769 * image[row][col].rgbtGreen + 0.189 * image[row][col].rgbtBlue);
            int sepiaGreen = round(0.349 * image[row][col].rgbtRed + 0.686 * image[row][col].rgbtGreen + 0.168 * image[row][col].rgbtBlue);
            int sepiaBlue = round(0.272 * image[row][col].rgbtRed + 0.534 * image[row][col].rgbtGreen + 0.131 * image[row][col].rgbtBlue);
            image[row][col].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[row][col].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[row][col].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
// The reflect function should take an image and reflect it horizontally.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            original[row][col] = image[row][col];
        }
    }

    // swap the values of pixels on opposite sides of a row
    for (int row = 0; row < height; row++)
    {
        for (int col = 0, swap = width - 1; col < width; col++)
        {
            image[row][col] = original[row][swap];
            swap--;
        }
    }

    return;
}

// Blur image
// The blur function should take an image and turn it into a box-blurred version of the same image.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* When implementing the blur function, you might find that blurring one pixel ends up affecting the blur of another pixel.
    Perhaps create a copy of image (the function’s third argument) by declaring a new (two-dimensional) array with code like
    RGBTRIPLE copy[height][width]; and copying image into copy, pixel by pixel, with nested for loops? And then read pixels’
    colors from copy but write (i.e., change) pixels’ colors in image? */

    RGBTRIPLE original[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            original[row][col] = image[row][col];
        }
    }

    // Assigning variables
    float totalr, totalg, totalb;
    int count = 0;
    totalr = totalg = totalb = 0;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            for (int arrrow = row - 1; arrrow <= row + 1; arrrow++)
            {
                for (int arrcol = col - 1; arrcol <= col + 1; arrcol++)
                {
                    if (arrcol < width && arrrow < height && arrcol >= 0 && arrrow >= 0)
                    {
                        totalr += original[arrrow][arrcol].rgbtRed;
                        totalg += original[arrrow][arrcol].rgbtGreen;
                        totalb += original[arrrow][arrcol].rgbtBlue;
                        count++;
                    }
                }
            }
            image[row][col].rgbtRed = round(totalr / count);
            image[row][col].rgbtGreen = round(totalg / count);
            image[row][col].rgbtBlue = round(totalb / count);
            count = 0;
            totalr = totalg = totalb = 0;
        }
    }
    return;
}
