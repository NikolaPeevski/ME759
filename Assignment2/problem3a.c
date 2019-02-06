#include <printf.h>

void generateFeature(int size) {
    printf("%d", size);
}
void generateMatrix(int size) {
    printf("%d", size);
}

int main(int argc, char *argv[]) {
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Wrong input %c, %c", *argv[1], *argv[2]);
        return 0;
    }
    printf("%c\n", *argv[1]);
    generateMatrix((*argv[1] - '0'));

    return 0;
}