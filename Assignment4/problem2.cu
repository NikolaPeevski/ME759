#include <stdio.h>
#include <iostream>
#include <randoms.h>
#include <math.h>

#include <time.h>

__global__ void sum(double* arrA, double* arrB, double* arrC, int threadCount) {
        int i = (blockIdx.x * threadCount) + threadIdx.x;
	double sum = arrA[i] + arrB[i];
        arrC[i] = sum * sum;
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
        printf("Wrong input");
        return 0;
    }
    struct timespec inclusive_start;
    struct timespec inclusive_end;

    struct timespec exclusive_start;
    struct timespec exclusive_end;

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
    clock_gettime(CLOCK_MONOTONIC, &inclusive_start);
    cudaMemcpy(dA, hA, size * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, hB, size * sizeof(double), cudaMemcpyHostToDevice);

    //Start exclusive timing
    clock_gettime(CLOCK_MONOTONIC, &exclusive_start);
    sum<<<(size + threadCount - 1) / threadCount, threadCount>>>(dA, dB, dC, threadCount);
    cudaDeviceSynchronize();

    //Stop exclusive timing
    clock_gettime(CLOCK_MONOTONIC, &exclusive_end);
    cudaMemcpy(hC, dC, size * sizeof(double), cudaMemcpyDeviceToHost);
    //Stop inclusive timing

    clock_gettime(CLOCK_MONOTONIC, &inclusive_end);
    double norm = 0;
    for (int i = 0; i < size; ++i) {
	    norm += hC[i];
    }

    norm = sqrt(norm);

    size_t inclusive_duration_usec = (inclusive_end.tv_sec - inclusive_start.tv_sec) * 1000 * 1000;

    inclusive_duration_usec += (inclusive_end.tv_nsec - inclusive_start.tv_nsec) / 1000;

    size_t exclusive_duration_usec = (exclusive_end.tv_sec - exclusive_start.tv_sec) * 1000 * 1000;

    exclusive_duration_usec += (exclusive_end.tv_nsec - exclusive_start.tv_nsec) / 1000;

    printf("%u\n", size);
    printf("%d\n", threadCount);
    printf("%zu \n", exclusive_duration_usec);
    printf("%zu \n", inclusive_duration_usec);
    printf("%f", norm);
    
    free(hA);
    free(hB);
    free(hC);
    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);
}
