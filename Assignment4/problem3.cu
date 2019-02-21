#include <stdio.h>
#include <iostream>
#include <randoms.h>
#include <math.h>

__global__ void sum(float* arrA, float* arrB, float* arrC, int rowSize, int colSize) {
	extern __shared__ float data[];

	data[threadIdx.x] = arrA[(blockIdx.x * rowSize) + threadIdx.x] * arrB[threadIdx.x];

	__syncthreads();	
	for(int offset = blockDim.x / 2; offset > 0; offset >>= 1)
  	{
    		if(threadIdx.x < offset) {
      			data[threadIdx.x] += data[threadIdx.x + offset];
    		}
    		__syncthreads();
  	}
 	 if(threadIdx.x == 0) {
	    arrC[blockIdx.x] = data[0];
  	}
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL) {
        printf("Wrong input");
        return 0;
    }

    int rowSize = 16;
    int ColumnSize = 32;

    unsigned int seed = 0; 
    sscanf(argv[1], "%u", &seed);

    float *hA = (float*)malloc(rowSize * ColumnSize * sizeof(float));
    float *hb = (float*)malloc(ColumnSize * sizeof(float));;
    float *hC = (float*)malloc(rowSize * sizeof(float));;

    float *dA;
    float *db;
    float *dC;

    random_floats(hA, -10, 10, rowSize * ColumnSize, seed);
    random_floats(hb, -10, 10, ColumnSize, seed);

    cudaMalloc(&dA, rowSize * ColumnSize * sizeof(float));
    cudaMalloc(&db, ColumnSize * sizeof(float));
    cudaMalloc(&dC, rowSize * sizeof(float));

    cudaMemcpy(dA, hA, rowSize * ColumnSize * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(db, hb, ColumnSize * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dC, hC, rowSize * sizeof(float), cudaMemcpyHostToDevice);
 
    sum<<<rowSize, ColumnSize, ColumnSize * sizeof(float)>>>(dA, db, dC, rowSize, ColumnSize);
    cudaDeviceSynchronize();

    cudaMemcpy(hC, dC, rowSize * sizeof(float), cudaMemcpyDeviceToHost);
    double normD = 0;
    for (int i = 0; i < rowSize; ++i) {
        normD += hC[i] * hC[i];
    }

    normD = sqrt(normD);

    for (int i = 0; i < rowSize; ++i) {
        hC[i] = 0;
        for (int j = 0; j < ColumnSize; ++j) {
            hC[i] += hA[(rowSize * i) + j] * hb[j];
        }
    }

    double normH = 0;
    for (int i = 0; i < rowSize; ++i) {
        normH += hC[i] * hC[i];
    }
    normH = sqrt(normH);
    printf("%f\n", normH - normD);

    free(hA);
    free(hb);
    free(hC);
    cudaFree(dA);
    cudaFree(db);
    cudaFree(dC);
}
