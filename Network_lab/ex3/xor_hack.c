#include <stdio.h>

int maximizingXor(int l, int r) {

    int xorValue = l ^ r;
    int result = 1;

    while (xorValue > 0) {
        result <<= 1;
        xorValue >>= 1;
    }

    return result - 1;
}

int main() {

    int l, r;

    scanf("%d", &l);
    scanf("%d", &r);

    printf("%d\n", maximizingXor(l, r));

    return 0;
}
