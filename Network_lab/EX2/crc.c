#include <stdio.h>
#include <string.h>

char message[100];
char binary[1000];
char gen[30];
char code[1200];
char rem[30];

void stringToBinary(char str[], char bin[])
{
    int k = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
        unsigned char ch = str[i];

        for(int j = 7; j >= 0; j--)
        {
            if(ch & (1 << j))
                bin[k++] = '1';
            else
                bin[k++] = '0';
        }
    }

    bin[k] = '\0';
}

int validBinary(char str[])
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] != '0' && str[i] != '1')
            return 0;
    }

    return 1;
}

int validGenerator()
{
    int len = strlen(gen);
    int count = 0;

    if(!validBinary(gen))
        return 0;

    if(gen[0] != '1')
        return 0;

    if(gen[len-1] != '1')
        return 0;

    for(int i = 0; i < len; i++)
    {
        if(gen[i] == '1')
            count++;
    }

    if(count < 2)
        return 0;

    return 1;
}

void crc(char input[])
{
    char temp[1200];

    strcpy(temp, input);

    int dlen = strlen(input);
    int glen = strlen(gen);

    for(int i = 0; i <= dlen - glen; i++)
    {
        if(temp[i] == '1')
        {
            for(int j = 0; j < glen; j++)
            {
                if(temp[i+j] == gen[j])
                    temp[i+j] = '0';
                else
                    temp[i+j] = '1';
            }
        }
    }

    strncpy(rem, temp + dlen - glen + 1, glen - 1);
    rem[glen - 1] = '\0';
}
void binaryToString(char bin[], char str[])
{
    int len = strlen(bin);
    int k = 0;

    for(int i = 0; i < len; i += 8)
    {
        int value = 0;

        for(int j = 0; j < 8; j++)
        {
            value = value * 2 + (bin[i + j] - '0');
        }

        str[k++] = (char)value;
    }

    str[k] = '\0';
}
int main()
{
    int choice, pos1, pos2;
    char received[1200];
    char output[100];
    char original[1200];

    printf("\n******** CRC ERROR DETECTION ********\n");

    printf("\nEnter Message : ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    stringToBinary(message, binary);

    printf("\nBinary Representation :\n%s\n", binary);

    printf("\nEnter Generator Polynomial : ");
    scanf("%s", gen);

    if(!validGenerator())
    {
        printf("\nInvalid Generator Polynomial!\n");
        printf("Generator Polynomial must:\n");
        printf("1. Contain only 0's and 1's\n");
        printf("2. Start with 1\n");
        printf("3. End with 1\n");
        printf("4. Have at least two 1's\n");
        return 0;
    }

    strcpy(code, binary);

    for(int i=0;i<strlen(gen)-1;i++)
        strcat(code,"0");

    printf("\nBinary after appending zeros :\n%s\n",code);

    crc(code);

    strcpy(code,binary);
    strcat(code,rem);

    printf("\nCRC Bits : %s\n",rem);
    printf("Generated Codeword :\n%s\n",code);

    while(1)
    {
        printf("\n-------------------------");
        printf("\n1. No Error");
        printf("\n2. Single Bit Error");
        printf("\n3. Multiple Bit Error");
        printf("\n4. Exit");
        printf("\n-------------------------");
        printf("\nEnter Choice : ");
        scanf("%d",&choice);

        strcpy(received,code);

        switch(choice)
        {
            case 1:

                printf("\nReceived Codeword :\n%s\n",received);

                crc(received);

                printf("Remainder : %s\n",rem);

                if(strspn(rem,"0")==strlen(rem))
                {
                    printf("Status : Message Accepted\n");

                    strcpy(original,received);

                    original[strlen(original)-(strlen(gen)-1)]='\0';

                    binaryToString(original,output);

                    printf("Recovered Message : %s\n",output);
                }
                else
                {
                    printf("Status : Message Discarded\n");
                }

                break;

            case 2:

                printf("Enter Bit Position : ");
                scanf("%d",&pos1);

                if(pos1>=1 && pos1<=strlen(received))
                    received[pos1-1]=(received[pos1-1]=='0')?'1':'0';

                printf("\nReceived Codeword :\n%s\n",received);

                crc(received);

                printf("Remainder : %s\n",rem);

                if(strspn(rem,"0")==strlen(rem))
                {
                    printf("Status : Message Accepted\n");

                    strcpy(original,received);

                    original[strlen(original)-(strlen(gen)-1)]='\0';

                    binaryToString(original,output);

                    printf("Recovered Message : %s\n",output);
                }
                else
                {
                    printf("Status : Single Bit Error Detected\n");
                    printf("Message Discarded\n");
                }

                break;

            case 3:

                printf("Enter First Bit Position : ");
                scanf("%d",&pos1);

                printf("Enter Second Bit Position : ");
                scanf("%d",&pos2);

                if(pos1>=1 && pos1<=strlen(received))
                    received[pos1-1]=(received[pos1-1]=='0')?'1':'0';

                if(pos2>=1 && pos2<=strlen(received))
                    received[pos2-1]=(received[pos2-1]=='0')?'1':'0';

                printf("\nReceived Codeword :\n%s\n",received);

                crc(received);

                printf("Remainder : %s\n",rem);

                if(strspn(rem,"0")==strlen(rem))
                {
                    printf("Status : Message Accepted\n");

                    strcpy(original,received);

                    original[strlen(original)-(strlen(gen)-1)]='\0';

                    binaryToString(original,output);

                    printf("Recovered Message : %s\n",output);
                }
                else
                {
                    printf("Status : Multiple Bit Error Detected\n");
                    printf("Message Discarded\n");
                }

                break;

            case 4:

                printf("\nProgram Terminated.\n");
                return 0;

            default:

                printf("\nInvalid Choice!\n");
        }
    }
}
