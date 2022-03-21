#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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

	printf("----------------------\n");
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
		printf("----------------------\n");
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

	cont = 0;
	for (int i = 0; i < numIng * contRecipes; i++)
	{
		if (i % contRecipes == 0)
		{
			printf("\n%s\t", ingArr[cont]);

			cont++;
		}
		printf("%d\t", *(mat + i));
	}

	printf("\n");
	return 0;
}