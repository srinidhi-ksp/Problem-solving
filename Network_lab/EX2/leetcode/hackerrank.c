#include <stdio.h>

void calculate_the_maximum(int n, int k) {

    int maxAND = 0;
    int maxOR = 0;
    int maxXOR = 0;

    for(int a = 1; a <= n; a++) {

        for(int b = a + 1; b <= n; b++) {

            int andValue = a & b;
            int orValue = a | b;
            int xorValue = a ^ b;

            if(andValue < k && andValue > maxAND)
                maxAND = andValue;

            if(orValue < k && orValue > maxOR)
                maxOR = orValue;

            if(xorValue < k && xorValue > maxXOR)
                maxXOR = xorValue;
        }
    }

    printf("%d\n", maxAND);
    printf("%d\n", maxOR);
    printf("%d\n", maxXOR);
}

int main() {

    int n, k;

    scanf("%d %d", &n, &k);

    calculate_the_maximum(n, k);

    return 0;
}
