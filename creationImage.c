#include "image3d.h"

imageRGB creerImage(int r, int h, int l)
{
	imageRGB image;
	image.R = r;
	image.H = h;
	image.L = l;

	for (int i = 0; i < 3; i++)
	{
		image.img[i] = (unsigned char **) malloc(h * r * sizeof(unsigned char *));
		for (int j = 0; j < h * r; j++)
			image.img[i][j] = (unsigned char *) malloc(l * r);
	}

	return image;
}


void imageAleatoire(imageRGB image)
{
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < image.H * image.R; i++)
		{
			for (int j = 0; j < image.L * image.R; j++)
			{
				image.img[k][i][j] = rand() % 256;
			}
		}
	}
}

void imageClavier(imageRGB image)
{
	char *colors[] = {"Rouge", "Verte", "Bleue"};
	for (int k = 0; k < 3; k++)
	{
		printf("Image %s:\n", colors[k]);
		for (int i = 0; i < image.H * image.R; i++)
		{
			for (int j = 0; j < image.L * image.R; j++)
			{
				printf("Pixel en ligne: %d, colone %d: ", i, j);
				scanf("%hhu", image.img[k][i] + j);
			}
		}
	}
}
