#include <stdio.h>
#include <ctype.h>
#include <string.h>

FILE *ptrFile;
char chr;
char line[500];

struct _ingredients
{
    char *name;
    int quantity;
};

struct _recipe
{
    char *name;
    char *decription;
    char *categories;
    char *profile;
    struct _ingredients *list;
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
    struct _recipe recipes;
    ptrFile = fopen("Recipes.txt", "r");
    if (ptrFile != NULL)
    {
        printf("File opened.\n");

        // Use the data within the file.
        int contRecipes = 0;
        int state = 0;

        while (!feof(ptrFile))
        {
            // recipes[contRecipes];
            while (fgets(line, sizeof(line), ptrFile))
            {
                if (all_space(line))
                {
                    state = 0;
                    contRecipes++;
                    printf("new \n");
                }
                else
                {
                    switch (state)
                    {
                    case 0:
                        printf("name--");

                        /* Name recipes[contRecipes].name = */
                        state++;
                        break;
                    case 1:
                        printf("descriptio--");

                        /* Description */
                        state++;
                        break;
                    case 2:
                        /* Categories */
                        printf("catego--");

                        state++;
                        break;
                    case 3:
                        /* Profile */
                        printf("descriptio--");

                        state++;
                        break;
                    case 4:
                        /* Ingredients */
                        printf("ingredi-");
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
    return 0;
}