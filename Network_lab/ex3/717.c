#include <stdio.h>
#include <stdbool.h>

bool isOneBitCharacter(int* bits, int bitsSize) {

    int i = 0;

    while(i < bitsSize - 1) {

        if(bits[i] == 0)
            i++;

        else
            i += 2;
    }

    return i == bitsSize - 1;
}

int main() {

    int bits1[] = {1,0,0};
    int size1 = sizeof(bits1) / sizeof(bits1[0]);

    printf("%s\n",
        isOneBitCharacter(bits1, size1) ? "true" : "false");

    int bits2[] = {1,1,1,0};
    int size2 = sizeof(bits2) / sizeof(bits2[0]);

    printf("%s\n",
        isOneBitCharacter(bits2, size2) ? "true" : "false");

    return 0;
}
