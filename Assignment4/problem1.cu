#include <stdio.h>
#include <iostream>

__global__ void sum(int* arr, int threadSize) {
    arr[(blockIdx.x * threadSize) + threadIdx.x] = blockIdx.x + threadIdx.x;
}

int main() {

    const size_t blockSize = 2;
    const size_t threadSize = 8;
    int* dArray;
    int *hostArray = (int*)malloc(blockSize * threadSize * sizeof(int));
    cudaMalloc(&dArray, blockSize * threadSize * sizeof(int));

    sum<<<2, 8>>>(dArray, threadSize);
    cudaDeviceSynchronize();
    cudaMemcpy(hostArray, dArray, blockSize * threadSize * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < threadSize*blockSize; i++) {
	printf("%d\n", hostArray[i]);
	}

    free(dArray);
    free(hostArray);
}
