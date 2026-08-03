#include <stdio.h>
#include <stdbool.h>

bool hasAlternatingBits(int n) {

    int previous = n & 1;

    n >>= 1;

    while (n > 0) {

        int current = n & 1;

        if (current == previous)
            return false;

        previous = current;

        n >>= 1;
    }

    return true;
}

int main() {

    printf("%d\n", hasAlternatingBits(5));
    printf("%d\n", hasAlternatingBits(7));
    printf("%d\n", hasAlternatingBits(10));
    printf("%d\n", hasAlternatingBits(11));

    return 0;
}
