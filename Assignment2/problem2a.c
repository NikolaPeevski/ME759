#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *getFile(char *fileName) {
    FILE *_file = fopen(fileName, "r");

    return _file;
}

int *parseFile(char *fileName, int *arrSize) {
    FILE *_file = getFile(fileName);
    if (_file == NULL) {
        int *res = malloc(1);
        res[0] = -1;
        return res;
    }

    int elementCount = 1;
    fscanf(_file, "%d", &elementCount);
    printf("%d Elements to add \n", elementCount);
    int *res = malloc(elementCount);
    int ch = -1;
    int i = 0;
    while (elementCount > 0 && fscanf(_file, "%d", &ch) == 1) {
        if (ch != -1) {
            *(res + i) = ch;
            elementCount--;
            printf("%d element added at %d \n",ch, i);
            i++;
        }
    }
    *arrSize = i;
    return res;
}

int *exclusiveScan(int *arr, int arraySize) {
    int* newArray = malloc(arraySize + 1);
    newArray[0] = 0;
    int newArraySize = arraySize + 1;
    int k = 1;
    int i = 0;

    while (k < newArraySize) {
        int j = 0;
            newArray[k] = 0;
        while(j <= i) {
            newArray[k] += arr[j];
            j++;
        }
        printf("Sum of %d entry is %d\n", k, newArray[k]);
        i++;
        k++;
    }

    int *payload = malloc(3);
    payload[0] = arraySize;
    payload[1] = newArray[newArraySize -1];

//    free(arr);
//    free(newArray);
    return payload;

}

int main() {
    int arraySize = 0;
    int *arr = parseFile("problem1.in", &arraySize);
    clock_t begin = clock();

    int *payload = exclusiveScan(arr, arraySize);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

//    printf("%d\n", payload[]);
    return 0;
}