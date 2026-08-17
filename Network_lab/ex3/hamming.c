#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int data[100], hamming[100], received[100];
    int m = 8, r = 0, totalBits;
    int i, j, parity, errorPos = 0;
    char inputChar;

    printf("HAMMING CODE - SINGLE BIT ERROR CORRECTION\n");

    printf("\nEnter a data string: ");
    if (scanf(" %c", &inputChar) != 1) return 1;

    for(i = 1; i <= m; i++)
    {
        data[i] = (inputChar >> (m - i)) & 1;
    }

    printf("Extracted Binary Data for '%c': ", inputChar);
    for(i = 1; i <= m; i++)
        printf("%d ", data[i]);
    printf("\n");

    while((1 << r) < (m + r + 1))
        r++;

    totalBits = m + r;

    printf("\nNumber of parity bits = %d", r);
    printf("\nTotal bits = %d\n", totalBits);

    j = 1;
    for(i = 1; i <= totalBits; i++)
    {
        int bitPos = totalBits - i + 1;
        if((bitPos & (bitPos - 1)) == 0)
            hamming[i] = 0;
        else
            hamming[i] = data[j++];
    }

    printf("\nCalculating Parity Bits:\n");
    for(i = 0; i < r; i++)
    {
        int pos = (1 << i);
        parity = 0;

        for(j = 1; j <= totalBits; j++)
        {
            int bitPos = totalBits - j + 1;
            if(bitPos & pos)
                parity ^= hamming[j];
        }

        hamming[totalBits - pos + 1] = parity;
        printf("P%d = %d\n", pos, parity);
    }

    printf("\nGenerated Hamming Code:\n");
    for(i = 1; i <= totalBits; i++)
        printf("%d ", hamming[i]);
    printf("\n");

    printf("\n----------------------------------------\n");
    printf("Enter the Received Code bits (%d bits total):\n", totalBits);
    for(i = 1; i <= totalBits; i++)
        if (scanf("%d", &received[i]) != 1) return 1;

    printf("\nSyndrome Calculation:");
    errorPos = 0;

    for(i = 0; i < r; i++)
    {
        int pos = (1 << i);
        parity = 0;

        for(j = 1; j <= totalBits; j++)
        {
            int bitPos = totalBits - j + 1;
            if(bitPos & pos)
                parity ^= received[j];
        }

        printf("\nP%d Check = %d", pos, parity);

        if(parity)
            errorPos += pos;
    }

    printf("\n\nSyndrome Value = %d", errorPos);

    if(errorPos == 0)
    {
        printf("\nNo Error Detected.\n");
    }
    else
    {
        int errorIndex = totalBits - errorPos + 1;

        printf("\nError detected at bit position %d (Index %d from left)", errorPos, errorIndex);

        received[errorIndex] ^= 1;

        printf("\nCorrected Hamming Code:\n");
        for(i = 1; i <= totalBits; i++)
            printf("%d ", received[i]);
    }

    printf("\n\nRecovered Data:\n");
    for(i = 1; i <= totalBits; i++)
    {
        int bitPos = totalBits - i + 1;
        if((bitPos & (bitPos - 1)) != 0)
            printf("%d ", received[i]);
    }
    printf("\n");

    return 0;
}
