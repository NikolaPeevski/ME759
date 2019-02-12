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

	srand(time(0));

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

    // Get the starting timestamp
    clock_gettime(CLOCK_MONOTONIC, &start);
    //Compute multiplication
    for (int i = 0; i < frstRowSize; ++i) {
        for (int j = 0; j < frstRowSize; ++j) {
            thrdA [(i * frstRowSize) + j] = frst[(i * frstRowSize) + j] * scnd[(j * frstRowSize) + i]  ;
        }
    }
    // Get the ending timestamp
    clock_gettime(CLOCK_MONOTONIC, &end);

    // We multiply seconds by 10^6 to convert to us
    size_t duration_usecA = (end.tv_sec - start.tv_sec) * 1000 * 1000;
    // We divide nanoseconds by 10^3 to convert to us
    duration_usecA += (end.tv_nsec - start.tv_nsec) / 1000;

    // Compute Frobenius norm
    double frobNormA = 0;

    for (int l = 0; l < thrdSize*thrdSize; ++l) {
        frobNormA += pow(2, thrdA[l]);
    }

    frobNormA = sqrt(frobNormA);

    //Reverse order, Assume CaseB

    int *frstBuff = frst;

    for (int i = 0; i < frstRowSize; ++i) {
        for (int j = 0; j < frstRowSize; ++j) {
            frst[(j * frstRowSize) + i] = frstBuff[(i * frstRowSize) + j];
        }
    }
    int *scndBuff = scnd;

    for (int i = 0; i < scndRowSize; ++i) {
        for (int j = 0; j < scndRowSize; ++j) {
            scnd[(i * scndRowSize) + j] = scndBuff[(j * scndRowSize) + i];
        }
    }


    int* thrdB = malloc(thrdSize * thrdSize * sizeof(int));

    // Get the starting timestamp
    clock_gettime(CLOCK_MONOTONIC, &start);

    //Compute multiplication
    for (int i = 0; i < frstRowSize; ++i) {
        for (int j = 0; j < frstRowSize; ++j) {
            thrdB[(i * frstRowSize) + j] = frst[(j * frstRowSize) + i] * scnd[(i * frstRowSize) + j]  ;
        }
    }
    // Get the ending timestamp
    clock_gettime(CLOCK_MONOTONIC, &end);

    // We multiply seconds by 10^6 to convert to us
    size_t duration_usecB = (end.tv_sec - start.tv_sec) * 1000 * 1000;
    // We divide nanoseconds by 10^3 to convert to us
    duration_usecB += (end.tv_nsec - start.tv_nsec) / 1000;

    int comparator = 0;
    //Compare multiplications

    for (int k = 0; k < thrdSize*thrdSize; ++k) {
        if (thrdA[k] != thrdB[k]) {
            printf("%d %d differe.\n", thrdA[k] ,thrdB[k]);
            comparator = 1;
            break;
        }
    }

    printf("The two multiplications are %s.", comparator == 0 ? "same" : "different");


    // Compute Frobenius norm
    double frobNormB = 0;

    for (int l = 0; l < thrdSize*thrdSize; ++l) {
        frobNormB += pow(2, thrdB[l]);
    }

    frobNormB = sqrt(frobNormB);

    FILE *_file = fopen("problem2.txt", "w+");

    fprintf(_file, "%f,%f\n", frobNormA, frobNormB);
    fprintf(_file, "%zu\n", duration_usecA);
    fprintf(_file, "%zu", duration_usecB);
    fclose(_file);
	return 0;
}

