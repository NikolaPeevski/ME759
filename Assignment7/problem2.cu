
/* Matrix Convoluion.
 * Host code.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fstream>
// includes, project
#include "2Dconvolution.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// declarations, forward

extern "C"
void computeGold(float*, const float*, const float*, unsigned int, unsigned int);

Matrix AllocateDeviceMatrix(const Matrix M);
Matrix AllocateMatrix(int height, int width,int init);
void CopyToDeviceMatrix(Matrix Mdevice, const Matrix Mhost);
void CopyFromDeviceMatrix(Matrix Mhost, const Matrix Mdevice);
bool CompareResults(float* A, float* B, int elements, float eps);
void FreeDeviceMatrix(Matrix* M);
void FreeMatrix(Matrix* M);

void ConvolutionOnDevice(const Matrix M, const Matrix N, Matrix P);

////////////////////////////////////////////////////////////////////////////////
// Matrix convolution
////////////////////////////////////////////////////////////////////////////////
__global__ void ConvolutionKernel(Matrix M, Matrix N, Matrix P)
{

	// Your code comes here...

}


////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

	Matrix  M;
	Matrix  N;
	Matrix  P;


	if(argc != 2) 
	{
		printf("Usage %s Size\n",argv[0]);
		return 1;

	}

	int size = atoi(argv[1]);
	M  = AllocateMatrix(KERNEL_SIZE, KERNEL_SIZE,1);
	N  = AllocateMatrix(size, size,1);		
	P  = AllocateMatrix(size, size,0);
	float cpuTime = 0.f,gpuTime=0.f;

	// M * N on the device
//	ConvolutionOnDevice(M, N, P);

	// compute the matrix convolution on the CPU for comparison
	Matrix reference = AllocateMatrix(P.height, P.width,0);
	computeGold(reference.elements, M.elements, N.elements, N.height, N.width);

	// in this case check if the result is equivalent to the expected soluion

//	bool res = CompareResults(reference.elements, P.elements, P.width * P.height, 0.01f);;
//	if(res==0)printf("Test Failed\n"); // This shouldnt pront for correct implementation
	printf("%f\n%f\n%f\n",reference.elements[size*size-1],cpuTime,gpuTime);

	// Free matrices
	FreeMatrix(&M);
	FreeMatrix(&N);
	FreeMatrix(&P);
	return 0;
}


////////////////////////////////////////////////////////////////////////////////
//! Run a simple test for CUDA
////////////////////////////////////////////////////////////////////////////////
void ConvolutionOnDevice(const Matrix M, const Matrix N, Matrix P)
{
	// Load M and N to the device
	Matrix Md = AllocateDeviceMatrix(M);
	CopyToDeviceMatrix(Md, M);
	Matrix Nd = AllocateDeviceMatrix(N);
	CopyToDeviceMatrix(Nd, N);

	// Allocate P on the device
	Matrix Pd = AllocateDeviceMatrix(P);
	CopyToDeviceMatrix(Pd, P);

	// Setup the execution configuration



	// Launch the device computation threads!

	// Read P from the device
	CopyFromDeviceMatrix(P, Pd); 

	// Free device matrices
	FreeDeviceMatrix(&Md);
	FreeDeviceMatrix(&Nd);
	FreeDeviceMatrix(&Pd);

}

// Allocate a device matrix of same size as M.
Matrix AllocateDeviceMatrix(const Matrix M)
{
	Matrix Mdevice = M;
	int size = M.width * M.height * sizeof(float);
	cudaMalloc((void**)&Mdevice.elements, size);
	return Mdevice;
}

Matrix AllocateMatrix(int height, int width,int init) // 1 is file read/ 0 is just allocation
{
	Matrix M;
	M.width = M.pitch = width;
	M.height = height;
	int size = M.width * M.height;
	M.elements = NULL;
	FILE *fp;
	fp = fopen("problem1.inp","r");
	// don't allocate memory on option 2

	M.elements = (float*) malloc(size*sizeof(float));
	if(init)
	{
		for(unsigned int i = 0; i < M.height * M.width; i++)
		{
			fscanf(fp,"%f",&M.elements[i]);
		}
	}
	return M;
}	

// Copy a host matrix to a device matrix.
void CopyToDeviceMatrix(Matrix Mdevice, const Matrix Mhost)
{
	int size = Mhost.width * Mhost.height * sizeof(float);
	Mdevice.height = Mhost.height;
	Mdevice.width = Mhost.width;
	Mdevice.pitch = Mhost.pitch;
	cudaMemcpy(Mdevice.elements, Mhost.elements, size, 
			cudaMemcpyHostToDevice);
}

// Copy a device matrix to a host matrix.
void CopyFromDeviceMatrix(Matrix Mhost, const Matrix Mdevice)
{
	int size = Mdevice.width * Mdevice.height * sizeof(float);
	cudaMemcpy(Mhost.elements, Mdevice.elements, size, 
			cudaMemcpyDeviceToHost);
}

// Free a device matrix.
void FreeDeviceMatrix(Matrix* M)
{
	cudaFree(M->elements);
	M->elements = NULL;
}

// Free a host Matrix
void FreeMatrix(Matrix* M)
{
	free(M->elements);
	M->elements = NULL;
}

//compare the data stored in two arrays on the host
bool CompareResults(float* A, float* B, int elements, float eps)
{
	for(unsigned int i = 0; i < elements; i++){
		float error = A[i]-B[i];
		if(error>eps){
			return false;
		} 
	}
	return true;
}



