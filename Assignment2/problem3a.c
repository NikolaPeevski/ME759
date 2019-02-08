#include <stdio.h>
#include <printf.h>
#include <stdlib.h>
#include <time.h>

void generateMatrix(int size) {

    FILE *fptr;
    fptr = fopen("problem3.dat", "aw");

    //if file does not exist, create it
    if(fptr == NULL)
    {
        fptr = fopen("problem3.dat", "wba");
    }

    int squareSize = size * size;

    srand(time(0));

    for(int i = 0; i < squareSize; i++) {

        fprintf(fptr, "%d", rand() % 2 ? 1 : -1);

        if ((size == 2 || i != 1) && (i + 1) % size == 0) {
            fprintf(fptr, "\n");
        } else {
            fprintf(fptr, " ");
        }
    }
    fclose(fptr);
}

void generateFeature(int size) {
    generateMatrix(size);
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Wrong input");
        return 0;
    }
    remove("problem3.dat");
    int matrix = 0;
    int featureMatrix = 0;
    sscanf(argv[1], "%d", &matrix);
    sscanf(argv[2], "%d", &featureMatrix);
    generateMatrix(matrix);
    generateFeature(featureMatrix);

    return 0;
}
