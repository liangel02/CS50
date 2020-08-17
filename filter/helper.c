#include "helpers.h"

// Convert image to grayscale


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0, j = 0;
    int sum = 0;
    int avg = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            avg = sum/3;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i = 0, j = 0;
    int sepiaRed = 0;
    int sepiaGreen = 0;
    int sepiaBlue = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap rbg values for corresponding pixels
    int i = 0, j = 0;
    int middle = width/2;
    int horizDist = 0;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < middle; j++)
        {
            horizDist = middle - j;
            swap(&image[i][j].rgbtRed, &image[i][middle + horizDist-1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][middle + horizDist-1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][middle + horizDist-1].rgbtBlue);
        }
    }
    return;
}

void swap(unsigned char *a, unsigned char *b)
{
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h = 0, w = 0, i = 0, j = 0;
    int sumRed = 0, sumBlue = 0, sumGreen = 0;
    int count = 0;
    //pixel with index [h][w]
    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {
            //iterate through all 9 pixels around it
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    //if pixel around the pixel in question exists
                    if ((h-1+i >= 0) && (h-1+i < height) && (w-1+j >= 0) && (w-1+j < width))
                    {
                        sumRed += image[h-1+i][w-1+j].rgbtRed;
                        sumGreen += image[h-1+i][w-1+j].rgbtGreen;
                        sumBlue += image[h-1+i][w-1+j].rgbtBlue;
                        count ++;
                    }
                }
            }
            image[h][w].rgbtRed = sumRed/count;
            image[h][w].rgbtGreen = sumGreen/count;
            image[h][w].rgbtBlue = sumBlue/count;
            //reset variables back to 0 for next pixel
            sumRed = sumBlue = sumGreen = 0;
            count = 0;
        }
    }
    return;
}

