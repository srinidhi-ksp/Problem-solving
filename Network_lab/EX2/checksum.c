#include <stdio.h>
#include <string.h>

#define MAXBITS 1000
#define MAXBLOCKS 200

char input[MAXBITS];
char padded[MAXBITS];
char data[MAXBLOCKS][9];
char checksum[9];

int n;      // number of blocks
int pad;    // number of padded zeros

//--------------------------------------------------
// NEW: Convert a String to Binary (8 bits per char)
//--------------------------------------------------
void stringToBinary(char str[], char bits[])
{
    int len = strlen(str);
    int i,b,k = 0;

    printf("\n%-8s %-8s %-10s\n", "Char", "ASCII", "8-bit Binary");

    for (i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)str[i];
        char byteBits[9];

        for (b = 7; b >= 0; b--)
            byteBits[7 - b] = ((ch >> b) & 1) + '0';
        byteBits[8] = '\0';

        printf("%-8c %-8d %-10s\n", str[i], ch, byteBits);

        for (b = 0; b < 8; b++)
            bits[k++] = byteBits[b];
    }

    bits[k] = '\0';
}

//--------------------------------------------------
// Binary Addition with End Around Carry
//--------------------------------------------------
void binaryAdd(char a[], char b[], char sum[])
{
    int i,carry = 0;

    for(i=7;i>=0;i--)
    {
        int bit1 = a[i]-'0';
        int bit2 = b[i]-'0';

        int s = bit1 + bit2 + carry;

        sum[i]=(s%2)+'0';
        carry=s/2;
    }

    while(carry)
    {
        for(i=7;i>=0;i--)
        {
            int bit=sum[i]-'0';
            int s=bit+carry;

            sum[i]=(s%2)+'0';
            carry=s/2;
        }
    }

    sum[8]='\0';
}

//--------------------------------------------------
// 1's Complement
//--------------------------------------------------
void complement(char str[])
{
    int i;
    for(i=0;i<8;i++)
    {
        if(str[i]=='0')
            str[i]='1';
        else
            str[i]='0';
    }
}

//--------------------------------------------------
// Convert Input into 8-bit Blocks
//--------------------------------------------------
void divideBlocks()
{
    int len=strlen(input);

    pad=(8-(len%8))%8;

    int i,k=0;

    // add leading zeros
    for(i=0;i<pad;i++)
        padded[k++]='0';

    // copy original bits
    for(i=0;i<len;i++)
        padded[k++]=input[i];

    padded[k]='\0';

    printf("\nPadded Data : %s\n",padded);

    n=k/8;

    printf("\n8-bit Blocks\n");

    for(i=0;i<n;i++)
    {
        strncpy(data[i],padded+i*8,8);
        data[i][8]='\0';

        printf("Block %d : %s\n",i+1,data[i]);
    }
}

//--------------------------------------------------
// Generate Checksum
//--------------------------------------------------
void generateChecksum()
{
    char sum[9]="00000000";
    int i;
    printf("\nSender Side Addition\n");

    for(i=0;i<n;i++)
    {
        printf("%s\n",data[i]);
        binaryAdd(sum,data[i],sum);
    }

    printf("----------------\n");
    printf("Sum      : %s\n",sum);

    strcpy(checksum,sum);

    complement(checksum);

    printf("Checksum : %s\n",checksum);
}

//--------------------------------------------------
// Verify Receiver
//--------------------------------------------------
void verify(char recv[][9])
{
    char sum[9]="00000000";
    int i;
    printf("\nReceiver Side Addition\n");

    for(i=0;i<n;i++)
    {
        printf("%s\n",recv[i]);
        binaryAdd(sum,recv[i],sum);
    }

    printf("%s (Checksum)\n",checksum);

    binaryAdd(sum,checksum,sum);

    printf("----------------\n");
    printf("Final Sum             : %s\n",sum);

    complement(sum);

    printf("1's Complement        : %s\n",sum);

    if(strcmp(sum,"00000000")==0)
    {
        printf("\nNO ERROR DETECTED\n");
    }
    else
    {
        printf("\nERROR DETECTED\n");
        printf("MESSAGE DISCARDED\n");
    }
}

//--------------------------------------------------
// Main
//--------------------------------------------------
int main()
{
    char recv[MAXBLOCKS][9];
    char text[200];

    int i,choice;

    // ---------- ONLY CHANGE: read a STRING instead of raw binary ----------
    printf("Enter String : ");
    scanf("%s", text);

    stringToBinary(text, input);
    // ------------------------------------------------------------------

    divideBlocks();

    generateChecksum();

    printf("\n\nTransmitted Data\n");

    for(i=0;i<n;i++)
        printf("%s ",data[i]);

    printf("%s",checksum);

    while(1)
    {
        for(i=0;i<n;i++)
            strcpy(recv[i],data[i]);

        printf("\n\n------ MENU ------\n");
        printf("1. No Error\n");
        printf("2. Single Bit Error\n");
        printf("3. Multiple Bit Error\n");
        printf("4. Exit\n");

        printf("Enter Choice : ");
        scanf("%d",&choice);

        if(choice==1)
        {
            verify(recv);
        }

        else if(choice==2)
        {
            int block,pos;

            printf("Enter Block Number : ");
            scanf("%d",&block);

            printf("Enter Bit Position (1-8) : ");
            scanf("%d",&pos);

            recv[block-1][pos-1]=(recv[block-1][pos-1]=='0')?'1':'0';

            verify(recv);
        }

        else if(choice==3)
        {
            int block1,pos1,block2,pos2;

            printf("Enter First Block Number : ");
            scanf("%d",&block1);

            printf("Enter First Bit Position : ");
            scanf("%d",&pos1);

            printf("Enter Second Block Number : ");
            scanf("%d",&block2);

            printf("Enter Second Bit Position : ");
            scanf("%d",&pos2);

            recv[block1-1][pos1-1]=(recv[block1-1][pos1-1]=='0')?'1':'0';
            recv[block2-1][pos2-1]=(recv[block2-1][pos2-1]=='0')?'1':'0';

            verify(recv);
        }

        else if(choice==4)
        {
            break;
        }

        else
        {
            printf("Invalid Choice\n");
        }
    }

    return 0;
}
