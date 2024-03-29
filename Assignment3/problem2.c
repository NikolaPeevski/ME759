#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


/**
 * Generates a row style matrix
 * @param size
 * @return
 */
int *generateMatrix(size_t size) {


	size_t squareSize = size * size;
	int *res = malloc(squareSize * sizeof(int));

    srand(time(NULL));

	for(int i = 0; i < squareSize; i++) {
		res[i] = (rand() % 2 ? 1 : -1);
	}
	return res;
}


int main() {
    //Initialize Arrays & Sizes
	size_t frstRowSize = 1024;
	int* frst = malloc(frstRowSize * frstRowSize * sizeof(int));
	size_t scndRowSize = 1024;
	int* scnd = malloc(scndRowSize * scndRowSize* sizeof(int));
    //Generate Arrays, Assume CaseA
	frst = generateMatrix(frstRowSize);
	scnd = generateMatrix(scndRowSize);

	//Compute thrd
	int thrdSize = 1024;
	int* thrdA = malloc(thrdSize * thrdSize * sizeof(int));
    struct timespec start;
    struct timespec end;
    for (int m = 0; m < thrdSize*thrdSize; ++m) {
        thrdA[m] = 0;
    }
    // Get the starting timestamp
    clock_gettime(CLOCK_MONOTONIC, &start);
    //Compute multiplication
    for (int i = 0; i < frstRowSize; ++i) {
        for (int j = 0; j < frstRowSize; ++j) {
            for (int k = 0; k < frstRowSize; ++k) {
                thrdA [(i * frstRowSize) + j] += frst[(i * frstRowSize) + k] * scnd[(j * frstRowSize) + k];
            }
        }
    }
    // Get the ending timestamp
    clock_gettime(CLOCK_MONOTONIC, &end);

    // We multiply seconds by 10^6 to convert to us
    size_t duration_usecA = (end.tv_sec - start.tv_sec) * 1000 * 1000;
    // Multiply by 1e-6 to convert to milliseconds
    duration_usecA += (end.tv_nsec - start.tv_nsec) * 1e-6;

    // Compute Frobenius norm
    double frobNormA = 0;

    for (int l = 0; l < thrdSize*thrdSize; ++l) {
        frobNormA += pow(thrdA[l], 2);
    }
    frobNormA = sqrt(frobNormA);

    int* thrdB = malloc(thrdSize * thrdSize * sizeof(int));

    // Get the starting timestamp
    clock_gettime(CLOCK_MONOTONIC, &start);

    //Compute multiplication
    for (int i = 0; i < frstRowSize; ++i) {
        for (int j = 0; j < frstRowSize; ++j) {
            for (int k = 0; k < frstRowSize; ++k) {
                thrdB [(i * frstRowSize) + j] += scnd[(i * frstRowSize) + k] * frst[(j * frstRowSize) + k];
            }
        }
    }
    // Get the ending timestamp
    clock_gettime(CLOCK_MONOTONIC, &end);

    // We multiply seconds by 10^6 to convert to us
    size_t duration_usecB = (end.tv_sec - start.tv_sec) * 1000 * 1000;
    // Multiply by 1e-6 to convert to milliseconds
    duration_usecB += (end.tv_nsec - start.tv_nsec) * 1e-6;

    int comparator = 0;
    //Compare multiplications

    for (int k = 0; k < thrdSize*thrdSize; ++k) {
        if (thrdA[k] != thrdB[k]) {
            printf("%d %d differe.\n", thrdA[k] ,thrdB[k]);
            comparator = 1;
            break;
        }
    }

//    printf("The two multiplications are %s.", comparator == 0 ? "same" : "different");


    // Compute Frobenius norm
    double frobNormB = 0;

    for (int l = 0; l < thrdSize*thrdSize; ++l) {
        frobNormB += pow(thrdB[l], 2);
    }

    frobNormB = sqrt(frobNormB);

    FILE *_file = fopen("problem2.txt", "w+");

    fprintf(_file, "%f,%f\n", frobNormA, frobNormB);

    fprintf(_file, "%zu\n", duration_usecA);
    fprintf(_file, "%zu", duration_usecB);
    fclose(_file);
    free(frst);
    free(scnd);
    free(thrdA);
    free(thrdB);
	return 0;
}

