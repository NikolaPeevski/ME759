#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 *
 * @param fileName
 * @return
 */
FILE *getFile(char *fileName) {
    FILE *_file = fopen(fileName, "r");

    return _file;
}
/**
 *
 * @param fileName
 * @param arrSize
 * @return
 */
int *parseFile(char *fileName, int *arrSize) {
    FILE *_file = getFile(fileName);
    if (_file == NULL) {
        int *res = malloc(1);
        res[0] = -1;
        return res;
    }

    int elementCount = 1;
    fscanf(_file, "%d", &elementCount);

    int *res = malloc(elementCount * sizeof(int));
    int ch = -1;
    int i = 0;
    while (elementCount > 0 && fscanf(_file, "%d", &ch) == 1) {
        if (ch != -1) {
            *(res + i) = ch;
            elementCount--;

            i++;
        }
    }
    *arrSize = i;
    return res;
}

int comparator (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}


/**
 *
 */
void sort() {
    char *input = "problem1.in";
    int arrSize = 0;
    int *arr = parseFile(input, &arrSize);

    if (arr[0] == -1) {
        printf("File %s not found.", input);

    } else {
        int n = sizeof(arr)/sizeof(arr[0]);
        int low = 0;
        int high = arrSize - 1;
	printf("%d\n", arrSize);
        qsort(arr, arrSize, sizeof(int), comparator);
    }

}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    sort();
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%lf", cpu_time_used);
    return 0;
}
