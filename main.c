#include "image3d.h"

imageRGB getDimensions(imageRGB image, int *etape)
{
	printf("Veuillez entrer les dimensions de votre image  (ou 0 pour retourner):\n");
	printf("Longueur: ");
	scanf("%d", &image.L);
	if (image.L == 0)
		return loadImage(etape);
	printf("Hauteur: ");
	scanf("%d", &image.H);
	if (image.H == 0)
		return loadImage(etape);
	printf("Resolution: ");
	scanf("%d", &image.R);
	if (image.R == 0)
		return loadImage(etape);

	return image;
}

imageRGB saisirImage(int *etape)
{
	imageRGB image;

	system("cls");
	printf("- Entrer les pixels de l'image manuelement\n");
	printf("---------------------------\n\n");
	image = getDimensions(image, etape);
	image = creerImage(image.R, image.H, image.L);
	imageClavier(image);
}

imageRGB genererImage(int *etape)
{
	imageRGB image;

	system("cls");
	printf("- Generer une image aleatoire\n");
	printf("-----------------------------\n\n");
	image = getDimensions(image, etape);
	image = creerImage(image.R, image.H, image.L);
	imageAleatoire(image);
}

imageRGB chargerFichier(int *etape)
{
	imageRGB image;
	char filename[50];
	FILE *fptr = NULL;

	system("cls");
	printf("- Charger une image a partir d'un fichier\n");
	printf("-----------------------------------------\n\n");
	while (!fptr)
	{
		printf("Veuillez entrer le nom du fichier (ou 0 pour retourner): images/");
		fflush(stdin);
		scanf("%s", filename);
		if (!strcmp(filename, "0"))
			return loadImage(etape);
		char *name = ft_strjoin("images/", filename);
		fptr = fopen(name, "rb");
		free(name);

		if (!fptr)
			printf("Fichier introuvable!\n");
	}

	return lireImageFichier(fptr);
}

imageRGB loadImage(int *etape)
{
	int choix;
	imageRGB image;
	int flag = 1;

	*etape = 2;
	system("cls");
	printf("Etape 1: Chargez votre image:\n");
	while (1)
	{
		printf("------------------------------------------\n");
		printf("1 - Entrer les pixels de l'image manuelement.\n");
		printf("2 - Generer une image aleatoire.\n");
		printf("3 - Charger une image a partir d'un fichier.\n");
		printf("------------------------------------------\n");
		printf("Veuillez selectioner une method de chargement d'image: ");
		scanf("%d", &choix);
		switch (choix)
		{
			case 1:
				image = saisirImage(etape);
				break;
			case 2:
				image = genererImage(etape);
				break;
			case 3:
				image = chargerFichier(etape);
				break;
			default:
				*etape = 1;
				flag = 0;
		}
		if (flag)
			break;
		else
			printf("Choix invalide!\n");
	}
	
	return image;
}

imageRGB appiquerFiltre(imageRGB image, int *etape)
{
	int input;
	imageRGB newImage;
	int flag = 1;

	system("cls");
	printf("Etape 2: Appliquer un filtre:\n");
	*etape = 3;
	while (1)
	{
		printf("------------------------------------------\n");
		printf("1 - Image grise.\n");
		printf("2 - Detection de contours.\n");
		printf("3 - Inverser image.\n");
		printf("4 - Continuer sans appliquer un filtre.\n");
		printf("5 - Retourner a l'etape precedente.\n");
		printf("------------------------------------------\n");
		scanf("%d", &input);
		switch (input)
		{
			case 1:
				newImage = creerImageGris(image);
				break;
			case 2:
				newImage = detectContours(image);
				break;
			case 3:
				newImage = inverserImage(image);
				break;
			case 4:
				return image;
			case 5:
				*etape = 1;
				return image;
			default:
				*etape = 2;
				flag = 0;
		}
		if (flag)
			break;
		else
			printf("Choix invalide!\n");
	}
}

void enregistrerImage(imageRGB image, int *etape)
{
	char filename[50];
	int input;
	int flag = 1;

	system("cls");
	printf("Etape 3: Exporter image:\n");
	printf("Veuillez entrer le nom du fichier a exporter (ou 0 pour retourner): output/");
	scanf("%s", &filename);
	
	if (!strcmp("0", filename))
	{
		*etape = 2;
		return;
	}
	creerFichier(image, filename);
	printf("Votre fichier a ete creer avec succee.\n");
	printf("Entrer 1 pour traiter une nouvelle image, 0 pour quitter: \n");
	scanf("%d", input);
	if (!input)
		*etape = 0;
	else
		*etape = 1;
}

int main()
{
	imageRGB image;
	int etape = 1;

	system("cls");
	printf("Bienvenue dans le monde de traitement d'image!");
	Sleep(3000);

	while (etape)
	{
		switch (etape)
		{
			case 1:
				image = loadImage(&etape);
				break;
			case 2:
				image = appiquerFiltre(image, &etape);
				break;
			case 3:
				enregistrerImage(image, &etape);
				break;
		}
	}	
	return 0;
}

// int main()
// {
// 	FILE *fptr = fopen("images/image.ppm", "rb");
// 	imageRGB image = lireImageFichier(fptr);
// 	creerFichier(image, "test");
// 	return 0;
// }
