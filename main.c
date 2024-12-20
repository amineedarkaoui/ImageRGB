#include "image3d.h"

imageRGB getDimensions(imageRGB image)
{
	printf("Veuillez entrer les dimensions de votre image  (ou 0 pour retourner):\n");
	printf("Longueur: ");
	scanf("%d", &image.L);
	if (image.L == 0)
		return loadImage();
	printf("Hauteur: ");
	scanf("%d", &image.H);
	if (image.H == 0)
		return loadImage();
	printf("Resolution: ");
	scanf("%d", &image.R);
	if (image.R == 0)
		return loadImage();

	return image;
}

imageRGB saisirImage()
{
	imageRGB image;

	system("cls");
	printf("- Taper l'image manuelement\n");
	printf("---------------------------\n\n");
	image = getDimensions(image);
	image = creerImage(image.R, image.H, image.L);
	imageClavier(image);
}

imageRGB genererImage()
{
	imageRGB image;

	system("cls");
	printf("- Generer une image aleatoire\n");
	printf("-----------------------------\n\n");
	image = getDimensions(image);
	image = creerImage(image.R, image.H, image.L);
	imageAleatoire(image);
}

imageRGB chargerFichier()
{
	imageRGB image;
	char filename[50];
	FILE *fptr = NULL;

	system("cls");
	printf("- Charger une image a partir d'un fichier\n");
	printf("-----------------------------\n\n");
	while (!fptr)
	{
		printf("Veuillez entrer le nom du fichier (ou 0 pour retourner): images/");
		fflush(stdin);
		scanf("%s", filename);
		if (!strcmp(filename, "0"))
			return loadImage();
		char *name = ft_strjoin("images/", filename);
		fptr = fopen(name, "rb");
		free(name);

		if (!fptr)
			printf("Fichier introuvable!\n");
	}

	return lireImageFichier(fptr);
}

imageRGB loadImage()
{
	int choix;
	imageRGB image;

	system("cls");
	printf("Etape 1: Chargez votre image:\n");
	printf("------------------------------------------\n");
	printf("1 - Entrer les pixels de l'image manuelement.\n");
	printf("2 - Generer une image aleatoire.\n");
	printf("3 - Charger une image a partir d'un fichier.\n");
	printf("------------------------------------------\n");
	printf("Veuillez selectioner une method de chargement d'image: ");
	while (1)
	{
		scanf("%d", &choix);
		break;
	}
	switch (choix)
	{
		case 1:
			image = saisirImage();
			break;
		case 2:
			image = genererImage();
			break;
		case 3:
			image = chargerFichier();
			break;
	}

	return image;
}

int appiquerFiltre()
{
	
}

int main()
{
	system("cls");
	printf("Bienvenue dans le monde de traitement d'image!");
	Sleep(3000);

	imageRGB image = loadImage();
	if (appiquerFiltre())
		choisirFiltre();
	else
		enregistrerImage(image);
	return 0;
}
