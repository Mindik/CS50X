#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float r = image[h][w].rgbtRed;
            float g = image[h][w].rgbtGreen;
            float b = image[h][w].rgbtBlue;

            int mid = round((b + g + r) / 3.0);

            image[h][w].rgbtRed = mid;
            image[h][w].rgbtGreen = mid;
            image[h][w].rgbtBlue = mid;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
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
    RGBTRIPLE newPixel[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float rm = 0.0;
            float gm = 0.0;
            float bm = 0.0;
            int count = 0;
            for (int f = h - 1; f <= h + 1; f++)
            {
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
            newPixel[h][w].rgbtRed = mid_r;
            newPixel[h][w].rgbtGreen = mid_g;
            newPixel[h][w].rgbtBlue = mid_b;
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = newPixel[h][w].rgbtRed;
            image[h][w].rgbtGreen = newPixel[h][w].rgbtGreen;
            image[h][w].rgbtBlue = newPixel[h][w].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE newPixel[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float r_x = 0.0;
            float g_x = 0.0;
            float b_x = 0.0;

            float r_y = 0.0;
            float g_y = 0.0;
            float b_y = 0.0;

            for (int f = h - 1; f <= h + 1; f++)
            {
                if (f >= 0 && f < height)
                {
                    for (int d = w - 1; d <= w + 1; d++)
                    {
                        if (d >= 0 && d < width)
                        {
                            float rx = image[f][d].rgbtRed * Gx[f - h + 1][d - w + 1];
                            float gx = image[f][d].rgbtGreen * Gx[f - h + 1][d - w + 1];
                            float bx = image[f][d].rgbtBlue * Gx[f - h + 1][d - w + 1];
                            r_x += rx;
                            g_x += gx;
                            b_x += bx;

                            float ry = image[f][d].rgbtRed * Gy[f - h + 1][d - w + 1];
                            float gy = image[f][d].rgbtGreen * Gy[f - h + 1][d - w + 1];
                            float by = image[f][d].rgbtBlue * Gy[f - h + 1][d - w + 1];
                            r_y += ry;
                            g_y += gy;
                            b_y += by;
                        }

                    }
                }
            }

            int mid_r = round(sqrtf(powf(r_x, 2.0) + powf(r_y, 2.0)));
            int mid_g = round(sqrtf(powf(g_x, 2.0) + powf(g_y, 2.0)));
            int mid_b = round(sqrtf(powf(b_x, 2.0) + powf(b_y, 2.0)));

            if (mid_r >= 255)
            {
                mid_r = 255;
            }
            if (mid_g >= 255)
            {
                mid_g = 255;
            }
            if (mid_b >= 255)
            {
                mid_b = 255;
            }

            newPixel[h][w].rgbtRed = mid_r;
            newPixel[h][w].rgbtGreen = mid_g;
            newPixel[h][w].rgbtBlue = mid_b;
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = newPixel[h][w].rgbtRed;
            image[h][w].rgbtGreen = newPixel[h][w].rgbtGreen;
            image[h][w].rgbtBlue = newPixel[h][w].rgbtBlue;
        }
    }
    return;
}
