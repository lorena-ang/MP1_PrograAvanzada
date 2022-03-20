#include <stdio.h>
#include <ctype.h>

FILE *ptrFile;
char chr;
char line[500];

int all_space(const char *str) {
    while (*str) {
        if (!isspace(*str++)) {
            return 0;
        }
    }
    return 1;
}

int main() {
    ptrFile = fopen("Recipes.txt", "r");
    if (ptrFile != NULL) {
        printf("File opened.\n");

        // Use the data within the file.
        while (!feof(ptrFile)) {
            while (fgets(line, sizeof(line), ptrFile)) {
                printf("%s", line); 
                if (all_space(line)) {
                    printf("Hola"); 
                }
            }
        }
        if (fclose(ptrFile) == 0) {
            printf("File closed.\n");
        } else {
            printf("Unable to close file.\n");
        }
    } else {
        printf("Unable to open file.\n");
    }
    return 0;
}