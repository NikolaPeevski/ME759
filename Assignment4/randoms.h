// Guard for multiple includes
#ifndef ME759_RANDOMS
#define ME759_RANDOMS

// Define size_t
#include <stddef.h>

// Force C-style function linkage for C++ applications
#ifdef __cplusplus
extern "C" {
#endif

void random_floats(float* a, float amin, float amax, size_t n, unsigned int seed);
void random_doubles(double* a, double amin, double amax, size_t n, unsigned int seed);
void random_ints(int* a, int amin, int amax, size_t n, unsigned int seed);

// END C-style function linkage
#ifdef __cplusplus
}
#endif

// END guard for multiple includes
#endif
