#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

FILE *ptrFile;
char chr;
char line[500];

struct _ingredients
{
	char name[50];
	int quantity;
};

struct _recipe
{
	char name[50];
	char decription[500];
	char categories[500];
	char profile[500];
	int numIngridients;
	struct _ingredients list[50];
};

int all_space(const char *str)
{
	while (*str)
	{
		if (!isspace(*str++))
		{
			return 0;
		}
	}
	return 1;
}

// Cálculo de la distancia euclidiana para la matriz de comparaciones.
double euclidean_distance(int *mat, int contRecipes, int numIng, int p, int q)
{
	int *recipeA = malloc(numIng * sizeof(int));
	int *recipeB = malloc(numIng * sizeof(int));
	int sum = 0;
	double eDistance;

	// Ingredientes de la receta A.
	for (int i = 0; i < numIng; i++)
	{
		*(recipeA + i) = *(mat + p + (i * contRecipes));
	}

	// Ingredientes de la receta B.
	for (int i = 0; i < numIng; i++)
	{
		*(recipeB + i) = *(mat + q + (i * contRecipes));
	}

	// Raíz cuadrada de la sumatoria de las diferencias al cuadrado entre los ingredientes de las recetas A y B.
	for (int i = 0; i < numIng; i++)
	{
		sum += pow(*(recipeA + i) - *(recipeB + i), 2);
	}
	eDistance = sqrt(sum);

	// Retorna la distancia euclidiana.
	return eDistance;
}

void getLowercase(char *s)
{
	while (*s != '\0')
	{
		if (*s == '\r' || *s == '\n')
		{
			*s = '\0';
			break;
		}
		// Es mayúscula
		if (*s >= 'A' && *s <= 'Z')
		{
			*s = tolower(*s);
		}
		// Mover a siguiente caracter
		++s;
	}
}

int main()
{
	struct _recipe recipes[50];
	int contRecipes = 0;

	ptrFile = fopen("Recipes.txt", "r");
	if (ptrFile != NULL)
	{
		printf("File opened.\n");

		// Use the data within the file.
		int state = 0;
		int numIng = 0;
		int cont = 0;

		while (!feof(ptrFile))
		{
			while (fgets(line, sizeof(line), ptrFile))
			{
				cont++;
				if (all_space(line))
				{
					state = 0;
					numIng = 0;
					contRecipes++;
				}
				else
				{
					char *res = strchr(line, ':') + 1;

					switch (state)
					{
					case 0:
						strcpy(recipes[contRecipes].name, res);
						state++;
						break;
					case 1:
						strcpy(recipes[contRecipes].decription, res);
						state++;
						break;
					case 2:
						strcpy(recipes[contRecipes].categories, res);
						state++;
						break;
					case 3:
						strcpy(recipes[contRecipes].profile, res);
						state++;
						break;
					case 4:

						if (strncmp(line, "Ingredients", 11) != 0)
						{
							recipes[contRecipes].list[numIng].quantity = atoi(res);
							memcpy(recipes[contRecipes].list[numIng].name, line, res - line - 1);
							numIng++;
							recipes[contRecipes].numIngridients = numIng;
						}
						break;
					default:
						break;
					}
				}
			}
		}
		if (fclose(ptrFile) == 0)
		{
			printf("File closed.\n");
		}
		else
		{
			printf("Unable to close file.\n");
		}
	}
	else
	{
		printf("Unable to open file.\n");
	}

	printf("--------------------------------------------------------------\n");
	int maxIng = 0;
	contRecipes++;
	for (int i = 0; i < contRecipes; i++)
	{
		printf("NAME: %s", recipes[i].name);
		printf("DESCRIPTION: %s", recipes[i].decription);
		printf("CATEGORIES: %s", recipes[i].categories);
		printf("PROFILE: %s", recipes[i].profile);
		printf("INGREDIENTS: %d\n", recipes[i].numIngridients);
		maxIng += recipes[i].numIngridients;
		for (int j = 0; j < recipes[i].numIngridients; j++)
		{
			printf("\t%s: %d\n", recipes[i].list[j].name, recipes[i].list[j].quantity);
		}
		printf("--------------------------------------------------------------\n");
	}

	char ingArr[50][maxIng];
	int numIng = 0;

	for (int i = 0; i < contRecipes; i++)
	{
		for (int j = 0; j < recipes[i].numIngridients; j++)
		{
			int found = 0;
			for (int k = 0; k < maxIng; k++)
			{
				if (strcmp(recipes[i].list[j].name, ingArr[k]) == 0)
				{
					found = 1;
					break;
				}
			}
			if (found == 0)
			{
				strcpy(ingArr[numIng], recipes[i].list[j].name);
				numIng++;
			}
		}
	}

	int *mat;
	mat = (int *)malloc(numIng * contRecipes * sizeof(int));
	int cont = 0;

	for (int row = 0; row < numIng; row++)
	{
		for (int col = 0; col < contRecipes; col++)
		{
			int value = 0;

			for (int j = 0; j < recipes[col].numIngridients; j++)
			{
				if (strcmp(recipes[col].list[j].name, ingArr[row]) == 0)
				{
					value = recipes[col].list[j].quantity;
					break;
				}
			}
			*(mat + cont) = value;
			cont++;
		}
	}

	printf("Formula matrix\n");
	cont = 0;
	for (int i = 0; i < contRecipes; i++)
	{
		printf("\t     %.*s", 8, recipes[i].name);
	}

	for (int i = 0; i < numIng * contRecipes; i++)
	{
		if (i % contRecipes == 0)
		{
			printf("\n%s\t\t", ingArr[cont]);

			cont++;
		}
		printf("%d\t\t", *(mat + i));
	}

	printf("\n\n");

	// PAIRWISE COMPARISONS
	// Creación de matriz para almacenar las comparaciones.
	double *matComparisons;
	matComparisons = (double *)malloc(contRecipes * contRecipes * sizeof(double));

	// Población de matriz de comparación.
	for (int i = 0; i < contRecipes; i++)
	{
		for (int j = 0; j < contRecipes; j++)
		{
			*(matComparisons + j + (i * contRecipes)) = euclidean_distance(mat, contRecipes, numIng, i, j);
		}
	}

	// Impresión de matriz de comparación.
	printf("Pairwise Comparisons\n");
    for (int i = 0; i < contRecipes; i++) {
		printf("\t     %.*s", 8, recipes[i].name);
	}
    printf("\n");

    for (int i = 0; i < contRecipes; i++) {
        printf("%.*s", 8, recipes[i].name);
        for(int j = 0; j < contRecipes; j++) {
            printf("%*.0f\t", 10, *(matComparisons+j+(i*contRecipes)));
        }
        printf("\n");
    }
    printf("\n");

	// EDGE NOTATION
	int sizeMat = ((contRecipes * contRecipes) - contRecipes) / 2;

	// Abrir archivo
	ptrFile = fopen("Edges.txt", "w");

	// Si hay errores
	if (ptrFile == NULL)
	{
		printf("Error opening the file %s", "Edges.txt");
		return -1;
	}

	// Imprimir y exportar a .txt matriz de edge notation
	printf("Edge Notation\n");
	printf("From\tTo\tDistance");
	printf("\n");
	for (int i = 0; i < contRecipes - 1; i++)
	{
		for (int j = 1; j < contRecipes; j++)
		{
			if (i != j)
			{
				char *strFrom = &(recipes[i].name)[7];
				getLowercase(strFrom);
				char *strTo = &(recipes[j].name)[7];
				getLowercase(strTo);
				// Imprimir
				printf("  %s      %s", strFrom, strTo);
				printf("\t   %.0f", *(matComparisons + j + (i * contRecipes)));
				printf("\n");
				// Exportar a archivo
				fprintf(ptrFile, "%s%s", strFrom, strTo);
				fprintf(ptrFile, "%.0f", *(matComparisons + j + (i * contRecipes)));
				fprintf(ptrFile, "\n");
			}
		}
	}
	// Cerrar archivo
	fclose(ptrFile);

	return 0;
}