FILE *getFile(char *fileName) {
    FILE *_file = fopen(fileName, "r");

    return _file;
}

void leastFour() {
    char fileName[13] = "problem1.txt";
    char *result = malloc(4);
    int resultIterator = 0;
    FILE *file = getFile(fileName);

    if (file == NULL) {
        printf("File %s not found!", fileName);
    } else {

        int i = 0;
        char *content = malloc(10);

        char ch = '-';

        while (ch != EOF) {
            if (ch != '-' && ch != '\n') {
                *(content + i) = ch;
                i++;
            }
            ch = (char) fgetc(file);
        }

        printf("Hello! I’m student ");
        for(int k = i - 4; k < i; k++) {
            printf("%c",*(content + k));
        }
        printf(".");
    }
}

int main() {
    leastFour();
    return 0;
}
