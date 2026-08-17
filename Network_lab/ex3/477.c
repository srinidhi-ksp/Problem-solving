#include <stdio.h>

int totalHammingDistance(int* nums, int numsSize) {

    int total = 0;

    for (int bit = 0; bit < 32; bit++) {

        int ones = 0;

        for (int i = 0; i < numsSize; i++) {

            if ((nums[i] >> bit) & 1)
                ones++;
        }

        int zeroes = numsSize - ones;

        total += ones * zeroes;
    }

    return total;
}

int main() {

    int nums[] = {4,14,2};

    int size = sizeof(nums)/sizeof(nums[0]);

    printf("%d\n", totalHammingDistance(nums,size));

    return 0;
}
