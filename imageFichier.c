#include "image3d.h"

imageRGB getImage(FILE *file)
{
	char *str;
	unsigned char buf[2];

	buf[1] = '\0';
	str = ft_strdup("");
	fread(buf, 1, 1, file);
	while (1)
	{
		str = ft_strjoin(str, buf);
		fread(buf, 1, 1, file);
		if (buf[0] == '\n')
			break;
	}
	char **dims = ft_split(str, ' ');
	return creerImage(1, atoi(dims[1]), atoi(dims[0]));
}

imageRGB lireImageFichier(FILE *file)
{
	unsigned char *buf;

	fseek(file, 3, SEEK_SET);
	// creer l'image
	imageRGB image = getImage(file);
	buf = (unsigned char *) malloc(image.L * image.R * 3);

	fread(buf, 1, 1, file);
	//skip 255
	fseek(file, 3, SEEK_CUR);

	//remplir les tableaux
	for (int i = 0; i < image.H * image.R; i++)
	{
		fread(buf, image.L * image.R * 3, 1, file);
		int l = 0;
		for (int j = 0; j < image.L * image.R; j++)
		{
			for (int k = 0; k < 3; k++)
				image.img[k][i][j] = buf[l++];
		}
	}

	free(buf);
	return image;
}

void insertHead(FILE *file, imageRGB image)
{
	fwrite("P6\n", 3, 1, file);
	fprintf(file, "%d %d\n", image.L * image.R, image.H * image.R);
	fwrite("255\n", 4, 1, file);
}

void remplirFichier(FILE *file, imageRGB image)
{
	for (int i = 0; i < image.H * image.R; i++)
	{
		for (int j = 0; j < image.L * image.R; j++)
		{
			for (int k = 0; k < 3; k++)
				fwrite(&image.img[k][i][j], 1, 1, file);
		}
	}
}

void creerFichier(imageRGB image, char *fileName)
{
	char *name = ft_strjoin(fileName, ".ppm");
	fileName = ft_strjoin("output/", name);
	FILE *file = fopen(fileName, "wb");
	free(name);
	free(fileName);

	insertHead(file, image);
	remplirFichier(file, image);
}