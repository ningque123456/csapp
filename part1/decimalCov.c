#include <stdio.h>
#include <string.h>
void bin2hex(char *bin);
void hex2bin(char *hex);
char hexArr[100];
char ans_bin2hex[1000];
char ans_hex2bin[1000];
int main(int argc, char const *argv[])
{
    /* code */
    char *case_1 = "0X6E";
    hex2bin(case_1);
    char *case_2 = "1101110";
    bin2hex(case_2);

    // printf(" %s ", ans_hex2bin);
    for (int i = 0; i < 10; i++)
    {
        if (ans_bin2hex[i] == ' ')
            break;
        printf("%c", ans_bin2hex[i]);
    }
    printf("\n");

    printf("%s",ans_hex2bin);

    return 0;
}
void bin2hex(char *bin)
{
    /**
     * 二进制 -> 十进制 -> 十六进制 
     * 字符串数组比字符串指针方便 
     * 由于需要逆序遍历，从后往前处理每一个数字，所以需要rev数组存储输入的逆序
     * 注意类型转换
     */
    char rev[1000];
    int rem = 0, dec = 0, pow = 1, i = 0;

    ans_bin2hex[0] = '0';
    ans_bin2hex[1] = 'X';
    int idx = 2;
    int len = strlen(bin);
    int endPos = len - 1;

    for (int i = 0; i < len; i++)
    {
        rev[i] = *(bin + endPos);
        endPos--;
    }

    for (int i = 0; rev[i] != '\0'; i++)
    {
        char cur = rev[i];
        int num = cur - '0';
        rem = num % 2;
        dec += (rem * pow);
        pow *= 2;
    }
    while (dec != 0)
    {
        hexArr[i++] = dec % 16;
        dec /= 16;
    }
    for (int j = i - 1; j >= 0; j--)
    {
        if (hexArr[j] > 9)
        {
            ans_bin2hex[idx++] = (hexArr[j] + 55);
        }
        else
        {
            ans_bin2hex[idx++] = hexArr[j] + '0';
        }
    }

}
void hex2bin(char *hex)
{
    /**
     * 打表遍历即可
     */
    int p = 2;
    int idx;
    while (*(hex+p) != '\0')
    {
        // printf(" %c ", *(hex + p));
        switch (*(hex + p))
        {
        case '0':
            /* code */
            strcat(ans_hex2bin, "0000");
            break;
        case '1':
            strcat(ans_hex2bin, "0001");
            break;
        case '2':
            strcat(ans_hex2bin, "0010");
            break;
        case '3':
            strcat(ans_hex2bin, "0011");
            break;
        case '4':
            strcat(ans_hex2bin, "0100");
            break;
        case '5':
            strcat(ans_hex2bin, "0101");
            break;
        case '6':
            strcat(ans_hex2bin, "0110");
            break;
        case '7':
            strcat(ans_hex2bin, "0111");
            break;
        case '8':
            strcat(ans_hex2bin, "1000");
            break;
        case '9':
            strcat(ans_hex2bin, "1001");
            break;
        case 'a':
        case 'A':
            strcat(ans_hex2bin, "1010");
            break;
        case 'b':
        case 'B':
            strcat(ans_hex2bin, "1011");
            break;
        case 'c':
        case 'C':
            strcat(ans_hex2bin, "1100");
            break;
        case 'd':
        case 'D':
            strcat(ans_hex2bin, "1101");
            break;
        case 'e':
        case 'E':
            strcat(ans_hex2bin, "1110");
            // 
            break;
        case 'f':
        case 'F':
            strcat(ans_hex2bin, "1111");
            break;
        default:
            break;
        }
        p++;
    }

}
