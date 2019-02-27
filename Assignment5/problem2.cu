#include <stdio.h>
#include <iostream>
#include <../randoms/randoms.h>
#include <math.h>

__global__ void sum(int* arrA, int* res, int rowSize, int colSize) {

	atomicAdd(&res[0],arrA[(blockIdx.x * colSize) + threadIdx.x]);
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        printf("Wrong input");
        return 0;
    }

    int rowSize = 32;
    int ColumnSize = 64;

    unsigned int seed = 0; 
    sscanf(argv[1], "%u", &seed);

    int *hA = (int*)malloc(rowSize * ColumnSize * sizeof(int));
    int *hb = (int*)malloc(sizeof(int));

    int *dA;
    int *db;

    random_ints(hA, -10, 10, rowSize * ColumnSize, seed);

    cudaMalloc(&dA, rowSize * ColumnSize * sizeof(int));
    cudaMalloc(&db, sizeof(int));

    cudaMemcpy(dA, hA, rowSize * ColumnSize * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(db, hb, sizeof(int), cudaMemcpyHostToDevice);
 
    sum<<<rowSize, ColumnSize>>>(dA, db, rowSize, ColumnSize);
    cudaDeviceSynchronize();

    cudaMemcpy(hb, db, sizeof(int), cudaMemcpyDeviceToHost);
    printf ("%d\n", hb[0]);

    free(hA);

    cudaFree(dA);
    cudaFree(db);
}
