#include "image3d.h"

imageRGB creerImageGris(imageRGB image)
{
	imageRGB imageGris = creerImage(image.R, image.H, image.L);
	for (int i = 0; i < image.H * image.R; i++)
	{
		for (int j = 0; j < image.L * image.R; j++)
		{
			int sum = 0;
			for (int k = 0; k < 3; k++)
				sum += image.img[k][i][j];
			for (int k = 0; k < 3; k++)
				imageGris.img[k][i][j] = sum / 3;
		}
	}
	return imageGris;
}

unsigned char getFlouPixel(imageRGB image, int k, int x, int y, int intens)
{
	int sum = 0, count = 0;
	int x1 = (x - intens >= 0) ? x - intens : 0;
	int y1 = (y - intens >= 0) ? y - intens : 0;
	int x2 = (x + intens < image.H * image.R) ? x + intens : image.H * image.R - 1;
	int y2 = (y + intens < image.L * image.R) ? y + intens : image.L * image.R - 1;

	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			sum += image.img[k][i][j];
			count++;
		}
	}
	return (sum/count);
}

imageRGB flou(imageRGB image, int intensite)
{
	imageRGB imageFlou = creerImage(image.R, image.H, image.L);
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < image.H * image.R; i++)
		{
			for (int j = 0; j < image.L * image.R; j++)
				imageFlou.img[k][i][j] = getFlouPixel(image, k, i, j, intensite);
		}
	}
	return imageFlou;
}

unsigned char gradientSobel(imageRGB image, int k, int x, int y)
{
	int sumX = 0, sumY = 0;
	int x1 = (x - 1 >= 0) ? x - 1 : 0;
	int y1 = (y - 1 >= 0) ? y - 1 : 0;
	int x2 = (x + 1 < image.H * image.R) ? x + 1 : image.H * image.R - 1;
	int y2 = (y + 1 < image.L * image.R) ? y + 1 : image.L * image.R - 1;
	int gx[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
	int gy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			sumX += image.img[k][i][j] * gx[i - x + 1][j - y + 1];
			sumY += image.img[k][i][j] * gy[i - x + 1][j - y + 1];
		}
	}
	unsigned char result = sqrt(pow(sumX, 2) + pow(sumY, 2));
	return (result > 255 ? 255 : result);
}

imageRGB detectContours(imageRGB image)
{
	image = creerImageGris(image);
	imageRGB newImage = creerImage(image.R, image.H, image.L);
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < image.H * image.R; i++)
		{
			for (int j = 0; j < image.L * image.R; j++)
				newImage.img[k][i][j] = gradientSobel(image, k, i, j);
		}
	}
	return newImage;
}

imageRGB inverserImage(imageRGB image)
{
	imageRGB newImage = creerImage(image.R, image.H, image.L);
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < image.H * image.R; i++)
		{
			for (int j = 0; j < image.L * image.R; j++)
				newImage.img[k][i][j] = 255 - image.img[k][i][j];
		}
	}
	return newImage;
}