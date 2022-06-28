#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculating average for each pixel, setting it to a variable grey and overwrite grey to the pixel
    float grey;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grey = ((image[i][j].rgbtBlue +  image[i][j].rgbtRed +  image[i][j].rgbtGreen) / 3.00);
            image[i][j].rgbtBlue = round(grey);
            image[i][j].rgbtRed = round(grey);
            image[i][j].rgbtGreen = round(grey);
        }
    }
    return;
}

int max(int value)
// Checking if value is higher then 255
{
    if (value > 255)
    {
        return 255;
    }
    return value;
}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // setting values according to sepia func
            sepiaRed = max(round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189)));
            sepiaGreen = max(round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168)));
            sepiaBlue = max(round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131)));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];
    for (int i = 0; i < height; i++)
    {
        // taking only half of width
        for (int j = 0; j < width / 2; j++)
        {
            // setting left side pixels rgba to temp variable
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            // Setting left side pixels rgba to right side values
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            // Setting right side values to left side from temp variable
            image[i][width - j - 1].rgbtBlue = temp[0];
            image[i][width - j - 1].rgbtGreen = temp[1];
            image[i][width - j - 1].rgbtRed = temp[2];
        }
    }
    return;
}

int blur_value(int i, int j, int height, int width, int color, RGBTRIPLE image[height][width])
{
    float counter = 0;
    int sum = 0;

    // Loop starts 1 row before and ends 1 row after
    for (int k = i - 1; k < (i + 2); k++)
    {
        // Loop starts 1 column before and ends 1 column after
        for (int l = j - 1; l < (j + 2); l ++)
        {
            // If pixel does not exists ( its beyond the image )
            if (k < 0 || l < 0 || k >= height || l >= width)
            {
                continue;
            }
            // Checking if its red or green or blue
            if (color == 0)
            {
                sum += image[k][l].rgbtRed;
            }
            else if (color == 1)
            {
                sum += image[k][l].rgbtGreen;
            }
            else
            {
                sum += image[k][l].rgbtBlue;
            }
            // Counting blocks
            counter++;

        }
    }
    // returning average of that grids
    return round(sum / counter);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur_value(i, j, height, width, 0, copy);
            image[i][j].rgbtGreen = blur_value(i, j, height, width, 1, copy);
            image[i][j].rgbtBlue = blur_value(i, j, height, width, 2, copy);
        }
    }
    return;
}
