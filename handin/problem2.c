#include <stdio.h>

int printCount(char* input) {
    int i = 0;
    while(*(input + i)) {
        i++;
    }

    return i;
}

int main(int argc, char** argv) {
    int count = printCount(argv[1]);
    printf("%d\n", count);
    return 0;
}