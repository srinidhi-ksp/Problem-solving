#include <stdio.h>
#include <string.h>

// Global variables to transfer generated data from Sender to Receiver automatically
char global_codewords[100][10];
int global_num_chars = 0;
int global_sender_choice = 0;

void sender()
{
    char text[100];
    int choice, i, j;

    printf("\n========== SENDER SIDE ==========\n");
    printf("Enter String : ");
    scanf(" %[^\n]s", text);

    printf("\nChoose Parity Type\n");
    printf("1. Even Parity\n");
    printf("2. Odd Parity\n");
    printf("Enter Choice : ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2)
    {
        printf("Invalid Choice\n");
        return;
    }

    // Save metadata for the receiver
    global_sender_choice = choice;
    global_num_chars = strlen(text);

    printf("\n--- Character-wise Processing ---\n");
    printf("%-6s %-6s %-10s %-8s %-12s\n", "Char", "ASCII", "7-Bit Bin", "Parity", "Code Word");

    for (i = 0; text[i] != '\0'; i++)
    {
        int ascii = (int)text[i];
        int binary[7];
        int ones = 0;
        int temp = ascii;

        // Convert ASCII to 7-bit binary (MSB to LSB)
        for (j = 6; j >= 0; j--)
        {
            binary[j] = temp % 2;
            if (binary[j] == 1)
            {
                ones++;
            }
            temp /= 2;
        }

        // Determine Parity Bit
        int parity = 0;
        if (choice == 1) // Even Parity
        {
            parity = (ones % 2 == 0) ? 0 : 1;
        }
        else // Odd Parity
        {
            parity = (ones % 2 == 0) ? 1 : 0;
        }

        // Save generated 8-bit codeword globally for simulated transmission
        for (j = 0; j < 7; j++)
        {
            global_codewords[i][j] = binary[j] + '0';
        }
        global_codewords[i][7] = parity + '0';
        global_codewords[i][8] = '\0';

        // Print character details
        printf("%-6c %-6d ", text[i], ascii);
        for (j = 0; j < 7; j++) printf("%d", binary[j]);
        printf("    %-8d ", parity);
        printf("%s\n", global_codewords[i]);
    }
}

void receiver()
{
    int i, j, parity_choice, error_choice;
    char local_codewords[100][10];
    char decoded_text[100];
    int error_detected = 0;

    printf("\n========== RECEIVER SIDE ==========\n");

    // Check if sender data exists
    if (global_num_chars == 0)
    {
        printf("Error: No data available from sender side yet.\n");
        return;
    }

    // Copy original codewords to a local buffer to safely induce errors
    for (i = 0; i < global_num_chars; i++)
    {
        strcpy(local_codewords[i], global_codewords[i]);
    }

    // Ask user for the error injection scenario
    printf("Choose Error Simulation Scenario:\n");
    printf("1. No Error\n");
    printf("2. Single-Bit Error\n");
    printf("3. 2-Bit Error\n");
    printf("Enter Choice : ");
    scanf("%d", &error_choice);

    if (error_choice < 1 || error_choice > 3)
    {
        printf("Invalid Choice\n");
        return;
    }

    // Handle Error Injections
    if (error_choice == 2) // Single-Bit Error
    {
        int block, pos;
        printf("\nTotal Blocks available: %d (1 to %d)\n", global_num_chars, global_num_chars);
        printf("Enter Block Number to induce error: ");
        scanf("%d", &block);
        printf("Enter Bit Position to flip (1 to 8, where 8 is parity bit): ");
        scanf("%d", &pos);

        if (block >= 1 && block <= global_num_chars && pos >= 1 && pos <= 8)
        {
            // Flip the bit (invert '0' to '1' or '1' to '0')
            local_codewords[block - 1][pos - 1] = (local_codewords[block - 1][pos - 1] == '0') ? '1' : '0';
            printf("\n[INFO] Single-bit error successfully induced in Block %d at Position %d.\n", block, pos);
        }
        else
        {
            printf("Invalid Block or Bit position values!\n");
            return;
        }
    }
    else if (error_choice == 3) // 2-Bit Error
    {
        int block, pos1, pos2;
        printf("\nTotal Blocks available: %d (1 to %d)\n", global_num_chars, global_num_chars);
        printf("Enter Block Number to induce 2-bit error: ");
        scanf("%d", &block);
        printf("Enter First Bit Position to flip (1 to 8): ");
        scanf("%d", &pos1);
        printf("Enter Second Bit Position to flip (1 to 8): ");
        scanf("%d", &pos2);

        if (block >= 1 && block <= global_num_chars && pos1 >= 1 && pos1 <= 8 && pos2 >= 1 && pos2 <= 8)
        {
            if (pos1 == pos2)
            {
                printf("Error: Bit positions must be distinct to simulate a 2-bit error!\n");
                return;
            }
            // Flip both bits
            local_codewords[block - 1][pos1 - 1] = (local_codewords[block - 1][pos1 - 1] == '0') ? '1' : '0';
            local_codewords[block - 1][pos2 - 1] = (local_codewords[block - 1][pos2 - 1] == '0') ? '1' : '0';
        }
        else
        {
            printf("Invalid Block or Bit position values!\n");
            return;
        }
    }

    // Ask for receiver side parity preference verification
    printf("\nChoose Parity Type for Verification\n");
    printf("1. Even Parity\n");
    printf("2. Odd Parity\n");
    printf("Enter Choice : ");
    scanf("%d", &parity_choice);

    if (parity_choice != 1 && parity_choice != 2)
    {
        printf("Invalid Choice\n");
        return;
    }

    // Print Received Code Words Layout
    printf("\n--- Received Code Words ---\n");
    for (i = 0; i < global_num_chars; i++)
    {
        printf("Block %d: %s\n", i + 1, local_codewords[i]);
    }

    // Process and validate local codewords
    for (i = 0; i < global_num_chars; i++)
    {
        int ones = 0;

        // Count 1s in the entire 8-bit stream
        for (j = 0; j < 8; j++)
        {
            if (local_codewords[i][j] == '1')
                ones++;
        }

        // Validate parity
        int is_valid = 0;
        if (parity_choice == 1 && ones % 2 == 0) is_valid = 1;
        if (parity_choice == 2 && ones % 2 != 0) is_valid = 1;

        if (!is_valid)
        {
            error_detected = 1;
            // We do not 'break' here anymore, so we can decode what's left and observe the corrupted translation output
        }

        // Convert the first 7 bits back to ASCII decimal
        int ascii_val = 0;
        for (j = 0; j < 7; j++)
        {
            ascii_val = (ascii_val * 2) + (local_codewords[i][j] - '0');
        }
        decoded_text[i] = (char)ascii_val;
    }

    // Terminate the decoded string
    decoded_text[global_num_chars] = '\0';

    // Final Output Evaluation
    if (error_detected)
    {
        printf("\nError Detected in Transmission! Data discarded\n");
        printf("Retrieved Data (Corrupted): %s\n", decoded_text);
    }
    else
    {
        printf("\nNo Error Detected by Parity Checker.\n");
        printf("Retrieved Data: %s\n", decoded_text);

        // Additional conceptual notification explaining the limitation
        if (error_choice == 3)
        {
            printf("The retrieved data may be incorrect/corrupted because 1D parity cannot detect even-numbered bit errors.\n");
        }
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n==============================\n");
        printf(" STRING PARITY ERROR DETECTION\n");
        printf("==============================\n");
        printf("1. Sender Side\n");
        printf("2. Receiver Side\n");
        printf("3. Exit\n");
        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: sender(); break;
            case 2: receiver(); break;
            case 3: return 0;
            default: printf("Invalid Choice\n");
        }
    }
    return 0;
}
