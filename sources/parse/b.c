#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expandArray(char ***original, int originalRows, int originalCols) {
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
            expanded[i + 1][j + 1] = (*original)[i][j];
        }
    }

    // Free the memory allocated for the original array
    for (int i = 0; i < originalRows; i++) {
        free((*original)[i]);
    }
    free(*original);

    // Update the original pointer to point to the new array
    *original = expanded;

    // Print the expanded array
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            printf("%c", expanded[i][j]);
        }
        printf("\n");
    }
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

    // Copy original array to heap-allocated array
    char **heapArray = malloc(originalRows * sizeof(char *));
    for (int i = 0; i < originalRows; i++) {
        heapArray[i] = malloc((originalCols + 1) * sizeof(char)); // +1 for the null terminator
        strcpy(heapArray[i], original[i]);
    }

    // Expand the array and print the result
    expandArray(&heapArray, originalRows, originalCols);

    // Free the memory allocated for the new array
    for (int i = 0; i < originalRows + 2; i++) {
        free(heapArray[i]);
    }
    free(heapArray);

    return 0;
}
