#include <stdio.h>

int hammingDistance(int x, int y) {

    int xorValue = x ^ y;

    int count = 0;

    while (xorValue > 0) {

        if (xorValue & 1)
            count++;

        xorValue >>= 1;
    }

    return count;
}

int main() {

    printf("%d\n", hammingDistance(1,4));
    printf("%d\n", hammingDistance(3,1));
    printf("%d\n", hammingDistance(7,10));

    return 0;
}
