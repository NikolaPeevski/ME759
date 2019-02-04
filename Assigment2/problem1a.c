#include <stdio.h>
#include <stdlib.h>
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

/**
 *
 * @param arr
 * @param a
 * @param b
 */
void swap(int arr[], int a, int b)
{
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}
/**
 *
 * @param arr
 * @param low
 * @param high
 */
void quickSort(int arr[], int low, int high) {

    if (low >= high){
        return;
    }
    //Focus key
    int key = arr[low];
    //Far most left
    int left = low + 1;
    //Far most right
    int right = high;


    while (right > left) {
        while (right > left && arr[right] >= key) {
            --right;
        }
        while (right > left && key >= arr[left]) {
            ++left;
        }
        if (right > left) {
            swap(arr, left, right);
        }
    }
    if (arr[low] > arr[left]) {
        swap(arr, low, left);
        quickSort(arr, low, left - 1);
        quickSort(arr, left + 1, high);
    } else {
        quickSort(arr, low + 1, high);
    }

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
        printf("%d\n",arrSize);

        for(int i = 0; i <= high; i++) {
            printf ("Element %d at pos %d\n", arr[i], i);
        }
        printf("\n");
        quickSort(arr, low, high);
        for(int i = 0; i <= high; i++) {
            printf ("Element %d at pos %d\n", arr[i], i);
        }
    }

}

int main() {
    sort();
    return 0;
}