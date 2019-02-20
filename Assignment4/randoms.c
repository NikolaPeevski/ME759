#include <stddef.h>
#include <stdlib.h>
#include <time.h>

// Force C-style function linkage for C++ applications
#ifdef __cplusplus
extern "C" {
#endif

void random_floats(
	float* a, float amin, float amax, size_t n, unsigned int seed
) {
	
	// If seed is -1, use the system time instead
	if ((signed)seed == -1) {
		seed = time(NULL);
	}
	
	srand(seed);
	
	float range = amax - amin;
	
	for (size_t i = 0; i < n; i++) {
		a[i] = amin + (rand() / (RAND_MAX / range));
	}
}

void random_doubles(
	double* a, double amin, double amax, size_t n, unsigned int seed
) {
	// If seed is -1, use the system time instead
	if ((signed)seed == -1) {
		seed = time(NULL);
	}
	
	srand(seed);
	
	double range = amax - amin;
	
	for (size_t i = 0; i < n; i++) {
		a[i] = amin + (rand() / (RAND_MAX / range));
	}
}

void random_ints(
	int* a, int amin, int amax, size_t n, unsigned int seed
) {
	
	// If seed is -1, use the system time instead
	if ((signed)seed == -1) {
		seed = time(NULL);
	}
	
	srand(seed);
	
	int range = amax - amin;
	
	for (size_t i = 0; i < n; i++) {
		a[i] = amin + (rand() / (RAND_MAX / range));
	}
}

// END C-style function linkage
#ifdef __cplusplus
}
#endif