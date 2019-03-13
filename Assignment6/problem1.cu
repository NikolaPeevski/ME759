#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <../randoms/randoms.h>


void applyStencil1D(const int sIdx, const int eIdx, const double *weights, const double *in, double *out, const int radius) {

    for(int i = sIdx; i < eIdx; i++) { // si < eIdx ???
        out[i] = 0;

        // Loop over all elements in the stencil
        for(int j = -radius; j <= radius; j++) {
            out[i] += weights[j + radius] * in[i + j];
        }
        out[i] = out[i] / (2 * radius + 1);
    }
}

void initializeWeights(double *weights, int radius) {
    int R = radius;
    double val = sqrt( 2 / (M_PI* R*R) );
    for (int i = 0; i < 2 * R + 1; i++){
        weights[i] =  val *  exp( -2*(i-R)*(i-R)/(R*R) );
    }
}


__global__ void applyStencil1D_kernel(const int sIdx, const int eIdx, const double *weights, const double *in, double *out, const int radius){
    // Define index
    int i = sIdx + blockIdx.x * blockDim.x + threadIdx.x;

    if( i < eIdx){
        out[i] = 0;
        //loop over all elements in the stencil
        for(int j = -radius; j <= radius; j++){
            out[i] += weights[j + radius] * in[i + j];
        }
        out[i] = out[i] / (2 * radius + 1);
    }
}



int main(int argc, const char * argv[]) {
    // ------------- Initializing ----------------- //
    // Get inputs
    unsigned int N = 0, seed = 0, s = 2;
    int R = 0;
    sscanf(argv[1],"%u", &N);
    sscanf(argv[2],"%u", &R);
    sscanf(argv[3],"%u", &seed);
    sscanf(argv[4],"%u", &s);
    if ( N == 0 || R == 0 || seed == 0 || s == 2){
        printf("Error in getting parameters when running the program\n\n");
        return -1;
    }
    if ( N < 2 * R + 1){
        printf("N-1 is not larger than twice the radius: increase N or decrease R.\n\n");
        return -1;
    }


    // Define sizes and weights
    int size = N * sizeof(double);
    int wsize= (2 * R + 1) * sizeof(double);
    double *weights_h;
    cudaMallocHost(&weights_h, wsize);

    initializeWeights(weights_h, R);

    // Define interval for generating random values
    int amin = -1, amax =  1;

    // Define time variables
    struct timespec start, end;

    // ------------- On device ----------------- //
    // Allocate memory on host and device
    double *in_h;
    cudaMallocHost(&in_h, size);
    double *out_h;
    cudaMallocHost(&out_h, size);
    double *in_d = NULL;
    double *out_d = NULL;
    double *weights_d = NULL;
    cudaMalloc( &in_d, size);
    cudaMalloc( &out_d, size);
    cudaMalloc( &weights_d, size);

    // Generate random entries
    random_doubles(in_h, amin, amax, N, seed);

    // Copy context from host to device
    cudaMemset(in_d, 0, size);
    cudaMemset(out_d, 0, size);
    cudaMemset(weights_d, 0, size);
    cudaMemcpy(in_d, in_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(weights_d, weights_h, size, cudaMemcpyHostToDevice);

    // Invoke kernel to sum arrays
    unsigned int threads = N - 2 * R;
    unsigned int blocks = (N + threads -1) / threads;

    if (s == 0){
        // No shared memory
        applyStencil1D_kernel<<<blocks, threads>>>(R, N-R, weights_d, in_d, out_d, R);
    } else {
        // Shared memory
        //vectorAdd<<<blocks,threads, threads * sizeof(int)>>>(da, dc, threads);
    }


    // Synchronize host and device
    cudaDeviceSynchronize();

    // Copy c from device to host
    cudaMemcpy(out_h, out_d, size, cudaMemcpyDeviceToHost);


    // ------------- Compare to Stencil operation on host ----------------- //
    // Calculate on host
    double *out_href = (double*) calloc(N, sizeof(double));
    applyStencil1D(R, N-R, weights_h, in_h, out_href, R);

    // Compare
    double norm;
    for (int i = R; i < N-R; i++){
        //for (int i = 0; i < N; i++){
        norm += fabs(out_h[i] - out_href[i]);
        //printf("o:  %2.5lf\n", out_h[i]);
        //printf("oh: %2.5lf\n", out_href[i]);
    }


    // Print
    double norm2;
    for (int i = R; i < N-R; i++){
        norm2 += out_h[i] * out_h[i];
    }
    printf("%f\n", sqrt(norm2)); // Print the 2-norm

    // ------------- Free resources ----------------- //
    cudaFree(in_d);
    cudaFree(out_d);
    cudaFree(weights_d);
    cudaFree(in_h); cudaFree(out_h); cudaFree(weights_h);
    free(out_href);



    // ------------- TESTING ----------------- //

    printf("blablal");
    printf("Differnce: %lf\n\n", norm);

    return 0;
}