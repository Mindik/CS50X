#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bmp.h"



int main(void)
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE test[3][3];

    test[0][0].rgbtRed = 0;
    test[0][0].rgbtGreen = 10;
    test[0][0].rgbtBlue = 25;

    test[0][1].rgbtRed = 0;
    test[0][1].rgbtGreen = 10;
    test[0][1].rgbtBlue = 30;

    test[0][2].rgbtRed = 40;
    test[0][2].rgbtGreen = 60;
    test[0][2].rgbtBlue = 80;

    test[1][0].rgbtRed = 20;
    test[1][0].rgbtGreen = 30;
    test[1][0].rgbtBlue = 90;

    test[1][1].rgbtRed = 30;
    test[1][1].rgbtGreen = 40;
    test[1][1].rgbtBlue = 100;

    test[1][2].rgbtRed = 80;
    test[1][2].rgbtGreen = 70;
    test[1][2].rgbtBlue = 90;

    test[2][0].rgbtRed = 20;
    test[2][0].rgbtGreen = 20;
    test[2][0].rgbtBlue = 40;

    test[2][1].rgbtRed = 30;
    test[2][1].rgbtGreen = 10;
    test[2][1].rgbtBlue = 30;

    test[2][2].rgbtRed = 50;
    test[2][2].rgbtGreen = 40;
    test[2][2].rgbtBlue = 10;



    int height = 3;
    int width = 3;

    RGBTRIPLE newPixel[height][width];
    for (int h = 1; h < 2; h++)
    {
        for (int w = 1; w < 2; w++)
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
                            float rx = test[f][d].rgbtRed * Gx[f - h + 1][d - w + 1];
                            float gx = test[f][d].rgbtGreen * Gx[f - h + 1][d - w + 1];
                            float bx = test[f][d].rgbtBlue * Gx[f - h + 1][d - w + 1];
                            r_x += rx;
                            g_x += gx;
                            b_x += bx;

                            float ry = test[f][d].rgbtRed * Gy[f - h + 1][d - w + 1];
                            float gy = test[f][d].rgbtGreen * Gy[f - h + 1][d - w + 1];
                            float by = test[f][d].rgbtBlue * Gy[f - h + 1][d - w + 1];
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
            test[h][w].rgbtRed = newPixel[h][w].rgbtRed;
            test[h][w].rgbtGreen = newPixel[h][w].rgbtGreen;
            test[h][w].rgbtBlue = newPixel[h][w].rgbtBlue;


        }
    }
    printf("%d %d %d\n", test[1][1].rgbtRed, test[1][1].rgbtGreen, test[1][1].rgbtBlue);

}


