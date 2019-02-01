#include <stdio.h>

int printCount(char* input) {
    int i = 0;
    while(*(input + i)) {
        i++;
    }

    return i;
}

int main(int argc, char** argv) {
	if(argv[1] == NULL) {
		printf("Invalid string.\n");
	} else {
		int count = printCount(argv[1]);
		printf("%d\n", count);
	}
	return 0;
}
