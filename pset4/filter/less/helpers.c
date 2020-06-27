#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{   
    // We go through each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float r = image[h][w].rgbtRed;
            float g = image[h][w].rgbtGreen;
            float b = image[h][w].rgbtBlue;
            // Find the average value for each pixel
            int mid = round((b + g + r) / 3.0);
            // Assigned a new value for up shades
            image[h][w].rgbtRed = mid;
            image[h][w].rgbtGreen = mid;
            image[h][w].rgbtBlue = mid;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float b = image[h][w].rgbtBlue;
            float g = image[h][w].rgbtGreen;
            float r = image[h][w].rgbtRed;
            // Formula from specification
            int sepiaRed = round(.393 * r + .769 * g + .189 * b);
            int sepiaGreen = round(.349 * r + .686 * g + .168 * b);
            int sepiaBlue = round(.272 * r + .534 * g + .131 * b);
            // if >= 255 then = 255
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        // Walk only half the width of the row
        for (int w = 0; w < width / 2; w++)
        {   
            // Move mirror using tmp
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{   
    // Temporary array
    RGBTRIPLE newPixel[height][width];
    // We go through the whole image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float rm = 0.0;
            float gm = 0.0;
            float bm = 0.0;
            int count = 0;
            // Use the current row, the row before the current and after
            for (int f = h - 1; f <= h + 1; f++)
            {   
                // If in the limit of the first and last row
                if (f >= 0 && f < height)
                {
                    for (int d = w - 1; d <= w + 1; d++)
                    {
                        if (d >= 0 && d < width)
                        {
                            float r1 = image[f][d].rgbtRed;
                            float g1 = image[f][d].rgbtGreen;
                            float b1 = image[f][d].rgbtBlue;
                            rm += r1;
                            gm += g1;
                            bm += b1;
                            count += 1;
                        }

                    }
                }
            }

            int mid_r = round(rm / count);
            int mid_g = round(gm / count);
            int mid_b = round(bm / count);
            // Write new values to a temporary array
            newPixel[h][w].rgbtRed = mid_r;
            newPixel[h][w].rgbtGreen = mid_g;
            newPixel[h][w].rgbtBlue = mid_b;
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Update old array
            image[h][w].rgbtRed = newPixel[h][w].rgbtRed;
            image[h][w].rgbtGreen = newPixel[h][w].rgbtGreen;
            image[h][w].rgbtBlue = newPixel[h][w].rgbtBlue;
        }
    }
    return;
}
