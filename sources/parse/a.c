#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expandArray(char **original, int originalRows, int originalCols)
{
    int newRows = originalRows + 2;
    int newCols = originalCols + 2;
    
    // Allocate memory for the new array
    char **expanded = malloc(newRows * sizeof(char *));
    for (int i = 0; i < newRows; i++) {
        expanded[i] = malloc(newCols * sizeof(char));
        memset(expanded[i], '.', newCols); // Fill the entire row with dots
    }

    // Copy the original array into the center of the new array
    for (int i = 0; i < originalRows; i++) {
        for (int j = 0; j < originalCols; j++) {
            expanded[i + 1][j + 1] = original[i][j];
        }
    }

    // Print the expanded array
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            printf("%c", expanded[i][j]);
        }
        printf("\n");
    }

    // Free the memory allocated for the new array
    for (int i = 0; i < newRows; i++) {
        free(expanded[i]);
    }
    free(expanded);
}

int main() {
    // Original 2D array
    char *original[] = {
        "111",
        "101",
        "111"
    };
    int originalRows = 3;
    int originalCols = 3;

    // Expand the array and print the result
    expandArray(original, originalRows, originalCols);

    return 0;
}
