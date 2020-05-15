#include "helpers.h"
#include <math.h>
#include <stdio.h>

// int * gx(int i, int j, int height, int width, RGBTRIPLE image[height][width]);
// int * gy(int i, int j, int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int new_grey = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            // printf("%f %i\n", grey, new_grey);
            image[i][j].rgbtBlue = new_grey;
            image[i][j].rgbtGreen = new_grey;
            image[i][j].rgbtRed = new_grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE new_pixel;

            new_pixel = image[i][j];

            image[i][j] = image[i][width - j - 1];

            image[i][width - j - 1] = new_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_image[height][width];
    float avg_blue, avg_green, avg_red, avg_count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg_count = 0;
            avg_blue = 0;
            avg_green = 0;
            avg_red = 0;
            for (int h = - 1; h <= 1; h++)
            {
                if (i + h >= 0 && i + h < height)
                {
                    for (int w = - 1; w <= 1; w++)
                    {
                        if (j + w >= 0 && j + w < width)
                        {
                            avg_blue += image[i + h][j + w].rgbtBlue;
                            avg_green += image[i + h][j + w].rgbtGreen;
                            avg_red += image[i + h][j + w].rgbtRed;
                            avg_count++;
                            // printf("%i%i - %i %i %i\n", (i + h),(j + w), avg_blue, avg_green, avg_red);
                        }
                    }
                }
            }
            temp_image[i][j].rgbtBlue = round(avg_blue / avg_count);
            temp_image[i][j].rgbtGreen = round(avg_green / avg_count);
            temp_image[i][j].rgbtRed = round(avg_red / avg_count);

            // printf("%i %i %i\n", temp_image[i][j].rgbtBlue, temp_image[i][j].rgbtGreen, temp_image[i][j].rgbtRed);
        }
    }
    // Fill the color values from temporary to the original image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary image array
    RGBTRIPLE temp_image[height][width];
    // An array for diagonal coloour checking
    int matrix_x[3][3] =
    {
        {- 1, 0, 1},
        {- 2, 0, 2},
        {- 1, 0, 1}
    };
    // An array for horizontal coloour checking
    int matrix_y[3][3] =
    {
        {- 1, - 2, - 1},
        {0, 0, 0},
        {1, 2, 1}
    };
    // The big loop over all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int x[3] = {0, 0, 0};
            int y[3] = {0, 0, 0};
            for (int h = - 1; h <= 1; h++)
            {
                if (i + h >= 0 && i + h < height)
                {
                    for (int w = - 1; w <= 1; w++)
                    {
                        if (j + w >= 0 && j + w < width)
                        {
                            x[0] += matrix_x[h + 1][w + 1] * image[i + h][j + w].rgbtBlue;
                            x[1] += matrix_x[h + 1][w + 1] * image[i + h][j + w].rgbtGreen;
                            x[2] += matrix_x[h + 1][w + 1] * image[i + h][j + w].rgbtRed;

                            y[0] += matrix_y[h + 1][w + 1] * image[i + h][j + w].rgbtBlue;
                            y[1] += matrix_y[h + 1][w + 1] * image[i + h][j + w].rgbtGreen;
                            y[2] += matrix_y[h + 1][w + 1] * image[i + h][j + w].rgbtRed;
                            //printf("%i %i %i\n", image[i + h][j + w].rgbtBlue, image[i + h][j + w].rgbtGreen, image[i + h][j + w].rgbtRed);
                            //printf("%i %i %i %i\n", matrix_x[h + 1][w + 1], x[0], x[1], x[2]);
                            //printf("%i %i %i %i\n", matrix_y[h + 1][w + 1], y[0], y[1], y[2]);
                            //printf("%i %i\n", matrix_x[h + 1][w + 1]*x[0], matrix_y[h + 1][w + 1]*y[0]);
                        }
                    }
                }
            }
            // Populate the temporary image array with color values
            int a = round(sqrt(x[0] * x[0] + y[0] * y[0]));
            temp_image[i][j].rgbtBlue = (a > 255) ? 255 : a;
            int b = round(sqrt(x[1] * x[1] + y[1] * y[1]));
            temp_image[i][j].rgbtGreen = (b > 255) ? 255 : b;
            int c = round(sqrt(x[2] * x[2] + y[2] * y[2]));
            temp_image[i][j].rgbtRed = (c > 255) ? 255 : c;
            //printf("%i %i %i\n", temp_image[i][j].rgbtBlue, temp_image[i][j].rgbtGreen, temp_image[i][j].rgbtRed);
        }
    }

    // Fill the color values from temporary to the original image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp_image[i][j];
        }
    }
    return;
}

/*
int * gx(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int matrix[3][3] =
    {
        {-1, 0, 1}
        {-2, 0, 2}
        {-1, 0, 1}
    };

    int colors[3] = {0, 0, 0};
    for (int h = -1; h <= 1; h++)
    {
        if (i + h > 0 && i + h < height)
        {
            for(int w = -1; w <= 1; w++)
            {
                if (j + w > 0 && j + w < width)
                {
                    colors[0] += matrix[h + 1][w + 1] * image[i + h][j + w].rgbtBlue;
                    colors[1] += matrix[h + 1][w + 1] * image[i + h][j + w].rgbtGreen;
                    colors[2] += matrix[h + 1][w + 1] * image[i + h][j + w].rgbtRed;
                }
            }
        }
    }
    return colors;
}

int * gy(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int matrix[3][3] =
    {
        {-1, -2, 1}
        {0, 0, 0}
        {1, 2, 1}
    };

    int colors[3] = {0, 0, 0};
    for (int h = -1; h <= 1; h++)
    {
        if (i + h > 0 && i + h < height)
        {
            for(int w = -1; w <= 1; w++)
            {
                if (j + w > 0 && j + w < width)
                {
                    colors[0] += matrix[h + 1][w + 1] * image[i + h][j + w].rgbtBlue;
                    colors[1] += matrix[h + 1][w + 1] * image[i + h][j + w].rgbtGreen;
                    colors[2] += matrix[h + 1][w + 1] * image[i + h][j + w].rgbtRed;
                }
            }
        }
    }
    return colors;
}
*/

