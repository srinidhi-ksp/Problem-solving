#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int data[100], hamming[100], received[100];
    int m, r = 0, totalBits, extendedBits;
    int i, j, parity, errorPos = 0;
    int globalParity = 0;

    printf("EXTENDED HAMMING CODE - SINGLE ERROR CORRECTION & DOUBLE ERROR DETECTION\n");

    // Read number of data bits
    printf("\nEnter number of data bits: ");
    if(scanf("%d", &m) != 1) return 1;

    printf("Enter the data bits (from left to right):\n");
    for(i = 1; i <= m; i++)
        if(scanf("%d", &data[i]) != 1) return 1;


    while((1 << r) < (m + r + 1))
        r++;

    totalBits = m + r;
    extendedBits = totalBits + 1; // +1 bit for the global parity bit

    printf("\nNumber of parity bits = %d (plus 1 global parity bit)", r);
    printf("\nTotal bits = %d\n", extendedBits);


    j = 1;
    for(i = 1; i <= totalBits; i++)
    {
        int bitPos = totalBits - i + 1;
        if((bitPos & (bitPos - 1)) == 0)
            hamming[i] = 0; // Placeholder for standard parity
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

    globalParity = 0;
    for(i = 1; i <= totalBits; i++)
    {
        globalParity ^= hamming[i];
    }
    hamming[extendedBits] = globalParity; // Appended at the far right index
    printf("Global Parity (P_global) = %d\n", globalParity);

    // Print generated string
    printf("\nGenerated Extended Hamming Code:\n");
    for(i = 1; i <= extendedBits; i++)
        printf("%d ", hamming[i]);
    printf("\n");

    printf("\n----------------------------------------\n");
    printf("Enter the Received Code bits (%d bits total):\n", extendedBits);
    for(i = 1; i <= extendedBits; i++)
        if(scanf("%d", &received[i]) != 1) return 1;

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


    int receivedGlobalParityCheck = 0;
    for(i = 1; i <= extendedBits; i++)
    {
        receivedGlobalParityCheck ^= received[i];
    }

    printf("\n\nSyndrome Value = %d", errorPos);
    printf("\nGlobal Parity Check = %d", receivedGlobalParityCheck);

    printf("\n\n--- Result ---");
    if(errorPos == 0 && receivedGlobalParityCheck == 0)
    {
        printf("\nNo Error Detected.\n");
    }
    else if(errorPos != 0 && receivedGlobalParityCheck != 0)
    {
        // 1-Bit Error: Safe to correct
        int errorIndex = totalBits - errorPos + 1;
        printf("\n1-Bit Error detected at bit position %d (Index %d from left)", errorPos, errorIndex);

        received[errorIndex] ^= 1; // Flip the broken bit back

        printf("\nCorrected Hamming Code:\n");
        for(i = 1; i <= extendedBits; i++)
            printf("%d ", received[i]);
    }
    else if(errorPos != 0 && receivedGlobalParityCheck == 0)
    {
        printf("\nCRITICAL: 2-Bit Error Detected! (Data cannot be recovered reliably)\n");
        return 0;
    }
    else if(errorPos == 0 && receivedGlobalParityCheck != 0)
    {

        printf("\n1-Bit Error detected in the Global Parity bit itself.");
        received[extendedBits] ^= 1; // Fix global parity bit
        printf("\nCorrected Hamming Code:\n");
        for(i = 1; i <= extendedBits; i++)
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
