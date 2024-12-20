#ifndef IMAGE3D_H
# define IMAGE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <windows.h>

typedef struct
{
	unsigned int R;
	unsigned int L;
	unsigned int H;
	unsigned char **img[3];
} imageRGB;

imageRGB	creerImage(int r, int h, int l);
imageRGB	lireImageFichier(FILE *file);
imageRGB	creerImageGris(imageRGB image);
imageRGB	flou(imageRGB image, int intensite);
imageRGB	detectContours(imageRGB image);
imageRGB	inverserImage(imageRGB image);
imageRGB 	loadImage();
void		imageAleatoire(imageRGB image);
void		imageClavier(imageRGB image);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
void		creerFichier(imageRGB image, char *fileName);

#endif