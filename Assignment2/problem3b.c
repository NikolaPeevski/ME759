#include <stdio.h>
#include <stdlib.h>
#include <printf.h>

/**
 *
 * @param fileName
 * @return
 */
FILE *getFile(char *fileName) {
    FILE *_file = fopen(fileName, "r");

    return _file;
}

void parseFile(char *fileName, int matrixSize, int *matrixArray, int featureSize, int *featureArray) {
    FILE *_file = getFile(fileName);
    if (_file == NULL) {
        return;
    }
    int ch = 0;
    int i = 0;
    int parsedMatrix = 0;

    while (fscanf(_file, "%d", &ch) == 1) {
        if (parsedMatrix != 1) {
           matrixArray[i] = ch;
        } else {
            featureArray[i] = ch;
        }
        i++;
        if (i == matrixSize && parsedMatrix != 1) {
//            printf("\n");
            i = 0;
            parsedMatrix = 1;
        }
    }
}

int calcCorrelation(const int *matrix, int matrixSize, int startIndex, const int *featureMatrix, int featureSize) {
    int crossSum = 0;
//    printf("Startindex %d \n", startIndex);


    for (int j = 0; j < featureSize; j++) {
        for(int i = 0; i < featureSize; i++) {
//            printf("Summing Matrix index %d with Feature index %d \n", (j * matrixSize) + startIndex + i, (j * featureSize) + i);
//            printf("Summing value: %d with value: %d \n", matrix[(j * matrixSize) + startIndex + i], featureMatrix[(j * featureSize) + i]);
            crossSum += (matrix[(j * matrixSize) + startIndex + i] * featureMatrix[(j * featureSize) + i]);
        }
    }


    return crossSum;
}

void match(char *fileName, int matrixSize, int featureSize) {

    int matrixQad = matrixSize * matrixSize;
    int featureQuad = featureSize * featureSize;
    int correlationVal = -1;
    int correlationI = -1;
    int correlationJ = -1;
    int correlationSize = (matrixSize - featureSize) + 1;
    int correlationQuad = correlationSize * correlationSize;
    int *correlationMatrix = malloc(correlationQuad * sizeof(int));

    int *matrixArray = malloc(matrixQad * sizeof(int));
    int *featureArray = malloc(featureQuad * sizeof(int));

    parseFile(fileName, matrixQad, matrixArray, featureQuad, featureArray);
//    printf("\n");
//    for (int l = 0; l < matrixSize; ++l) {
//        for (int i = 0; i < matrixSize; ++i) {
//            printf("%d ", matrixArray[matrixSize*l + i]);
//        }
//        printf("\n");
//    }
//    printf("\n");
//    for (int l = 0; l < featureSize; ++l) {
//        for (int i = 0; i < featureSize; ++i) {
//            printf("%d ", featureArray[featureSize*l + i]);
//        }
//        printf("\n");
//    }

//    for (int m = 0; m < matrixQad; ++m) {
//        printf("%d ", matrixArray[m]);
//    }

    int j = 0;
    for (int k = 0; k < matrixSize - featureSize + 1; k++) {
        for (int i = 0; i < matrixSize; i++) {
//            printf("Current depth %d\n", k * matrixSize);
            if (matrixSize > (i + (featureSize - 1))) {
//                printf("Fitting feature with start index: %d \n", (k * matrixSize) + i);
                int _correlation = calcCorrelation(matrixArray,matrixSize, (k * matrixSize) + i, featureArray, featureSize);

                if (_correlation > correlationVal || (correlationI == -1 && correlationJ == -1)) {
                    correlationVal = _correlation;
                    correlationI = k;
                    correlationJ = i;
                }

//                printf("Correlation value: %d\n", correlationMatrix[j]);
                j++;
            }
        }
//        printf("\n");
    }
    printf("%d\n", correlationI);
    printf("%d\n", correlationJ);
    printf("%d\n", correlationVal);
    free(correlationMatrix);
    free(matrixArray);
    free(featureArray);
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Wrong input");
        return 0;
    }
    int matrix = 0;
    int featureMatrix = 0;
    sscanf(argv[1], "%d", &matrix);
    sscanf(argv[2], "%d", &featureMatrix);

//    printf("%s\n%s\n", argv[1], argv[2]);
    match("problem3.dat", matrix, featureMatrix);
    return 0;
}
