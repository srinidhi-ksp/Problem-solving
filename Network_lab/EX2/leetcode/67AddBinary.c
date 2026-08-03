#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* addBinary(char* a, char* b) {
    int n = strlen(a);
    int m = strlen(b);

    int maxLen = (n > m ? n : m) + 2;
    char *temp = (char *)malloc(maxLen);

    int i = n - 1;
    int j = m - 1;
    int k = 0;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {

        int sum = carry;

        if (i >= 0)
            sum += a[i--] - '0';

        if (j >= 0)
            sum += b[j--] - '0';

        temp[k++] = (sum % 2) + '0';
        carry = sum / 2;
    }

    temp[k] = '\0';

    char *ans = (char *)malloc(k + 1);

    for (int x = 0; x < k; x++)
        ans[x] = temp[k - x - 1];

    ans[k] = '\0';

    free(temp);

    return ans;
}

int main() {

    char a[] = "1010";
    char b[] = "1011";

    char *ans = addBinary(a,b);

    printf("%s\n",ans);

    free(ans);

    return 0;
}
