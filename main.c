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
				printf("%d -- ", contRecipes);
				if (all_space(line))
				{
					state = 0;
					numIng = 0;
					contRecipes++;
					printf("new");
				}
				else
				{
					char *res = strchr(line, ':') + 1;

					switch (state)
					{
					case 0:
						printf("name--");
						strcpy(recipes[contRecipes].name, res);
						state++;
						break;
					case 1:
						printf("descriptio--");
						strcpy(recipes[contRecipes].decription, res);
						state++;
						break;
					case 2:
						printf("catego--");
						strcpy(recipes[contRecipes].categories, res);
						state++;
						break;
					case 3:
						printf("profile--");
						strcpy(recipes[contRecipes].profile, res);
						state++;
						break;
					case 4:
						/* Ingredients */

						if (strncmp(line, "Ingredients", 11) != 0)
						{
							printf("ingredi-");
							recipes[contRecipes].list[numIng].quantity = atoi(res);
							memcpy(recipes[contRecipes].list[numIng].name, line, res - line - 1);
							numIng++;
							recipes[contRecipes].numIngridients = numIng;
							printf("ingredi-");
						}
						break;
					default:
						break;
					}
				}
				printf("%s", line);
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

	for (int i = 0; i <= contRecipes; i++)
	{
		printf("NAME: %s", recipes[i].name);
		printf("DESCRIPTION: %s", recipes[i].decription);
		printf("CATEGORIES: %s", recipes[i].categories);
		printf("PROFILE: %s", recipes[i].profile);
		printf("INGREDIENTS: %d\n", recipes[i].numIngridients);
		for (int j = 0; j < recipes[i].numIngridients; j++)
		{
			printf("\t%s: %d\n", recipes[i].list[j].name, recipes[i].list[j].quantity);
		}
		printf("----------------------\n");
	}

	return 0;
}