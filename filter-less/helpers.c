#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterating through rows
    for (int i = 0; i < height; i++)
    {
        //iterating through each pixel
        for (int a = 0; a < width; a++)
        {
            //updating values RGB values for each pixel
            float average = (image[i][a].rgbtRed + image[i][a].rgbtGreen + image[i][a].rgbtBlue) / 3.0;
            image[i][a].rgbtRed = round(average);
            image[i][a].rgbtGreen = round(average);
            image[i][a].rgbtBlue = round(average);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //iterating through rows
    for (int i = 0; i < height; i++)
    {
        //iterating through each pixel and updating its RGB value
        for (int a = 0; a < width; a++)
        {
            //using  the sepia fomula to calculate the RGB values
            float sepiaRed = (0.393 * image[i][a].rgbtRed + 0.769 * image[i][a].rgbtGreen + 0.189 * image[i][a].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            float sepiaGreen = (0.349 * image[i][a].rgbtRed + 0.686 * image[i][a].rgbtGreen + 0.168 * image[i][a].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            float sepiaBlue = (0.272 * image[i][a].rgbtRed + 0.534 * image[i][a].rgbtGreen + 0.131 * image[i][a].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //updating the values
            image[i][a].rgbtRed = round(sepiaRed);
            image[i][a].rgbtGreen = round(sepiaGreen);
            image[i][a].rgbtBlue = round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            copy[i][a] = image[i][a];
        }
    }

    // Reflect the image
    for (int i = 0; i < height; i++)
    {
        int reflection = width - 1;
        for (int a = 0; a < width; a++)
        {
            image[i][a] = copy[i][reflection];
            reflection--;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Creating a copy of the original 2 dimentional array of pixels
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            copy[i][a] = image[i][a];
        }
    }

    //iterating through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int a = 0; a < width; a++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            //iterating through the surrounding pixels
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = a - 1; y <= a + 1; y++)
                {
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        //incrementing the sum of the surrounding pixels
                        sumRed += copy[x][y].rgbtRed;
                        sumGreen += copy[x][y].rgbtGreen;
                        sumBlue += copy[x][y].rgbtBlue;
                        count++;
                    }
                }
            }
            //updating the RGB values
            image[i][a].rgbtRed = round((float) sumRed / count);
            image[i][a].rgbtGreen = round((float) sumGreen / count);
            image[i][a].rgbtBlue = round((float) sumBlue / count);
        }
    }
}
