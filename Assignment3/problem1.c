// Define _POSIX_C_SOURCE before including time.h so we can access the timers
#define _POSIX_C_SOURCE 201902L
// We need math.h for pow, though it isn't required for the timers
#include <math.h>
#include <stdio.h>
#include <printf.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

size_t g_totalbytes = 0;

int *generateArray(int size, size_t *arrSize) {
    const size_t arr_size = 1024;
    printf("Size is %d\n", size);
    if (size == 0) size = 1;
//    printf("%lf\n", pow(2, size));
//    printf("%lx\n", ((size_t)(pow(size, 2))) * arr_size);
    *arrSize = (pow(2, size)) * arr_size;
//    printf("Array size is %zu\n", *arrSize);
    int* res = malloc(*arrSize * sizeof(int));
    for (int i = 0; i < *arrSize; ++i) {
        res[i] = (rand() % 2 ? 1 : -1);
    }
    return res;

}

size_t strideArray(int const *arr, size_t arrSize, int stride) {

    int sum = 0;

    int i = 0;
    while(i * stride < arrSize) {
        sum += arr[i * stride];
        ++i;
    }
    //total bites ran
    printf("%zu\n", i * sizeof(int));
    return i * sizeof(int);
}

size_t benchmark(int arraySize, int stride) {

    struct timespec start;
    struct timespec end;
    size_t arrSize = 0;
    int *arr = generateArray(arraySize, &arrSize);
    
//    printf("Array size is %d\n", arraySize);
    // Get the starting timestamp
    clock_gettime(CLOCK_MONOTONIC, &start);
    size_t totalBytes = strideArray(arr, arrSize, stride);
    // Get the ending timestamp
    clock_gettime(CLOCK_MONOTONIC, &end);

    // We multiply seconds by 10^6 to convert to us
    size_t duration_usec = (end.tv_sec - start.tv_sec) * 1000 * 1000;
    // We divide nanoseconds by 10^3 to convert to us
    duration_usec += (end.tv_nsec - start.tv_nsec) / 1000;

    // Report the total time in us
    printf("Total time: %zuus\n", duration_usec);
    printf("Total bytes ran: %zu\n", totalBytes);
    free(arr);
    g_totalbytes = arrSize * sizeof(int);

    return (totalBytes / 1048576) / ((duration_usec == 0 ? 1 : duration_usec) / 1e+6);

}

int main() {

    remove("results.dat");
    FILE *fptr;
    fptr = fopen("results.dat", "wba");

    int strideArray[5] = {1, 7, 14, 28, 56};
    int benchMarkArrayHigh = 20;
    int iterator = 0;
    while (iterator < 5) {
        for (int i = 0; i < benchMarkArrayHigh; ++i) {
            size_t avg = 0;
            for (int j = 0; j < 20; ++j) {
                printf("Strider is %d, size is %d\n", strideArray[iterator], i);
                avg += benchmark(i, strideArray[iterator]);
            }

            printf("Average throughput is %f B/s\n", avg/20.f);
            printf("%zu, %d, %f\n", g_totalbytes, strideArray[iterator], avg/20.f);
            fprintf(fptr, "%zu, %d, %f\n", g_totalbytes, strideArray[iterator], avg/20.f);
        }
        iterator++;
        printf("Iterator is %d %s\n", iterator, 9 > iterator ? "true" : "false");
    }

    fclose(fptr);
    return 0;
}
