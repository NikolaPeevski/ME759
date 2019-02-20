#include <stdio.h>
#include <iostream>
#include <randoms.h>
#include <math.h>

__global__ void sum(double* arrA, double* arrB, double* arrC, size_t size) {
    for (int i = 0; i < size; ++i) {
        double sum = arrA[i] + arrB[i];
        arrC[i] = sum * sum;
    }
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
        printf("Wrong input");
        return 0;
    }
    size_t size = 0;
    sscanf(argv[1], "%zu", &size);

    int threadCount = 0;
    sscanf(argv[2], "%d", &threadCount);

    unsigned seed = 0;
    sscanf(argv[3], "%u", &seed);

    double *hA = (double*)malloc(size * sizeof(double));
    double *hB = (double*)malloc(size * sizeof(double));
    double *hC = (double*)malloc(size * sizeof(double));

    double *dA;
    double *dB;
    double *dC;

    random_doubles(hA, -1, 1, size, seed);
    random_doubles(hB, -1, 1, size, seed);

    cudaMalloc(&dA, size * sizeof(double));
    cudaMalloc(&dB, size * sizeof(double));
    cudaMalloc(&dC, size * sizeof(double));

    //Start inclusive timing
    cudaMemcpy(dA, hA, size * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, size * sizeof(double), cudaMemcpyHostToDevice);

    //Start exclusive timing
    sum<<<1, threadCount>>>(dA, dB, dC, size);
    cudaDeviceSynchronize();

    //Stop exclusive timing

    cudaMemcpy(hC, dC, size * sizeof(double), cudaMemcpyDeviceToHost);
    //Stop inclusive timing
    double norm = 0;
    for (int i = 0; i < size; ++i) {
#        printf("%f\n", hC[i]);
	norm += hC[i];
    }

    norm = sqrt(norm);

    printf("%u\n", size);
    printf("%d\n", threadCount);
    printf("Exclusive timing.. Add it pls\n");
    printf("Inclusive timing.. Add it pls\n");
    printf("Inclusive timing.. Add it pls\n");
    printf("%f", norm);
    
    free(hA);
    free(hB);
    free(hC);
    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);
}
